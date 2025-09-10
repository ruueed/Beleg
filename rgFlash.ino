void setup() {
pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
}

void loop() {
digitalWrite(4,HIGH);
delay(20);
digitalWrite(4,LOW);
delay(20);
digitalWrite(5,HIGH);
delay(20);
digitalWrite(5,LOW);
delay(20);
}
