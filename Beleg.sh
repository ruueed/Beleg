#!/bin/bash

# exec 2>/dev/null

option=$1
title=$2
dump="movieDump.txt"
top100="top100.txt"

# Funktion: Größe der Dateien berechnen
size_func()
{
    if [ ! -f "$dump" ] || [ ! -r "$dump" ]; then
        echo "Die Datei '$dump' existiert nicht oder ist nicht lesbar."
        exit 1
    fi

    bytegroesse=$(awk '/^-rw/ {sum += $5} END {print sum}' "$dump")
    if [ -z "$bytegroesse" ]; then
        echo "Keine gültigen Dateieinträge in '$dump' gefunden."
        exit 1
    fi

    gibibytes=$(echo "scale=2; $bytegroesse / (1024^3)" | bc)
    echo "Summe aller Filmgroessen: $bytegroesse Bytes"
    echo "Summe in Gibibytes: $gibibytes GiB"
}

# Funktion: Dateierweiterungen analysieren
ext_func()
{
    if [ ! -f "$dump" ] || [ ! -r "$dump" ]; then
        echo "Die Datei '$dump' existiert nicht oder ist nicht lesbar."
        exit 1
    fi

    grep -Eo "\.[a-zA-Z0-9]+$" "$dump" | sort | uniq -c | awk '{print $2 ":" $1}' 
}

# Funktion: Jahrverteilung analysieren
hist_func()
{
    if [ ! -f "$dump" ] || [ ! -r "$dump" ]; then
        echo "Die Datei '$dump' existiert nicht oder ist nicht lesbar."
        exit 1
    fi

    awk '/^-rw-r--r--/ {print $NF}' "$dump" | grep -o '\b[0-9]\{4\}\b' | uniq -c | sort -nr | awk '{print $2 ":" $1}'
}

# Funktion: IMDB-Suche
imbd_func() {
    if [ -z "$title" ]; then
        echo "Der zweite Parameter (Titel) fehlt!"
        exit 1
    fi

    if [[ ! "$title" =~ ^title= ]]; then
        echo "Der zweite Parameter hat nicht das richtige Format (title=xxxx)."
        exit 1
    fi

    searchphrase=$(echo "$title" | cut -d '=' -f 2)
    if [ -z "$searchphrase" ]; then
        echo "Kein Suchbegriff gefunden. Bitte überprüfen Sie den Parameter 'title'."
        exit 1
    fi

    remote_file="/user/profile/active/robge/bs1-tools/title.akas.tsv"
    result=$(ssh s87481@ilux150.informatik.htw-dresden.de "grep -i -P '\t$searchphrase\t' '$remote_file'" 2>/dev/null)
    
    if [ $? -ne 0 ]; then
        echo "Fehler bei der SSH-Verbindung oder Zugriff auf die Datei '$remote_file'."
        exit 1
    fi

    if [ -z "$result" ]; then
        echo "Kein Eintrag für '$searchphrase' gefunden."
        exit 0
    fi

    imdb_id=$(echo "$result" | awk -F'\t' '{print $1}' | head -n 1)
    if [ -n "$imdb_id" ]; then
        echo "IMDB-ID für '$searchphrase': $imdb_id"
    else
        echo "Ein Eintrag wurde gefunden, aber die IMDB-ID konnte nicht extrahiert werden."
    fi
}

# Funktion: Syntaxprüfung
syntax_func()
{
    if [ ! -f "$dump" ] || [ ! -r "$dump" ]; then
        echo "Die Datei '$dump' existiert nicht oder ist nicht lesbar."
        exit 1
    fi

    grep -E "^-rw-r--r--|^drw-r--r--" "$dump" | while read -r line; do
        if [[ "$line" =~ ^[-d]rw-r--r--.*[[:space:]]+(.+\ \([1-2][0-9]{3}\)(-cd[1-3])?(\.[a-zA-Z0-9]+)?)$ ]]; then
            filename="${BASH_REMATCH[1]}"
            if [[ ! "$filename" =~ ^.+\ \([1-2][0-9]{3}\)\.([a-zA-Z0-9]+)$ && \
                  ! "$filename" =~ ^.+\ \([1-2][0-9]{3}\)-cd[1-3]\.([a-zA-Z0-9]+)$ && \
                  ! "$filename" =~ ^.+\ \([1-2][0-9]{3}\)$ ]]; then
                echo "Ungültiger Eintrag: $line"
            fi
        else
            echo "Ungültiger Eintrag: $line"
        fi
    done
}

# Funktion: Fehlende Titel analysieren
missing_func()
{
    if [ ! -f "$top100" ] || [ ! -r "$top100" ]; then
        echo "Die Datei '$top100' existiert nicht oder ist nicht lesbar."
        exit 1
    fi

    if [ ! -f "$dump" ] || [ ! -r "$dump" ]; then
        echo "Die Datei '$dump' existiert nicht oder ist nicht lesbar."
        exit 1
    fi

    mapfile -t top100_titles < "$top100"
    movie_titles=$(awk '/^-rw-r--r--/ {print $9}' "$dump" | sed -E 's/ \([0-9]{4}\)//')

    for title in "${top100_titles[@]}"; do
        clean_title=$(echo "$title" | sed -E 's/^[[:space:]]+|[[:space:]]+$//')
        if ! grep -Fxiq -- "$clean_title" <<< "$movie_titles"; then
            echo "$title"
        fi
    done
}

# Funktion: Suchen
search_func()
{
    if [ -z "$title" ]; then
        echo "Der zweite Parameter (Titel) fehlt!"
        exit 1
    fi

    if [[ ! "$title" =~ ^title= ]]; then
        echo "Der zweite Parameter hat nicht das richtige Format (title=xxxx)."
        exit 1
    fi

    searchphrase=$(echo "$title" | cut -d '=' -f 2)
    if [ -z "$searchphrase" ]; then
        echo "Kein Suchbegriff gefunden. Bitte überprüfen Sie den Parameter 'title'."
        exit 1
    fi

    if [ ! -f "$dump" ] || [ ! -r "$dump" ]; then
        echo "Die Datei '$dump' existiert nicht oder ist nicht lesbar."
        exit 1
    fi

    grep -i -- "$searchphrase" "$dump" | while read -r line; do
        echo "$line"
    done
}

# Hauptteil
case "$option" in
    size)       size_func ;;
    hist)       hist_func ;;
    ext)        ext_func ;;
    imbd)       imbd_func ;;
    syntax)     syntax_func ;;
    missing)    missing_func ;;
    search)     search_func ;;
    *)          echo "Ungültiger Parameter! Erlaubte Optionen: size, hist, ext, imbd, syntax, missing, search title=xxxx" ;;
esac
exit 0