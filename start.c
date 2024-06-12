#include <gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

char buf[128];

struct datum{
    int Jahr;
    int Monat;
    int Tag;
};

typedef struct angestellt{
    char name[20];
    char vorname[20];
    struct datum alter;
    struct datum eingestellt;
    int gehalt;
    struct angestellt *next;
}angestellt;

void on_button_clicked(GtkWidget *widget, gpointer data) {
    angestellt *zeiger =malloc(sizeof(angestellt));
    zeiger->gehalt=50;
    int abzug;
    g_print("Button clicked! Message: %s\n", (char *)data);
    printf("Gehalt:%d\n",zeiger->gehalt);
    printf("Abzug eingeben:\n");
    fgets(buf,128,stdin);
    abzug=atoi(buf);
    printf("Gehalt mit Abzug:%d\n",zeiger->gehalt-abzug);
}


int main( int argc, char *argv[] ){

    GtkWidget *window;
    GtkWidget *button;

    gtk_init(&argc, &argv);


//  Neues Toplevel Fenster
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
//  Titel des Toplevel Fensters
    gtk_window_set_title(GTK_WINDOW (window),"Materialverwaltung");
    gtk_container_set_border_width (GTK_CONTAINER (window), 80);
//  Neuer Button
    button = gtk_button_new_with_label("Click Me");
// Das Signal "clicked" des Buttons mit der Callback-Funktion verbinden
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), "Gehaltabzugrechner xD");

    // Das Signal "destroy" des Fensters mit gtk_main_quit verbinden, um die Anwendung zu beenden
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Button zum Fenster hinzufügen
    gtk_container_add(GTK_CONTAINER(window), button);

    // Fenster und Button anzeigen
    gtk_widget_show_all(window);

    gtk_main();


    return 0;
}
