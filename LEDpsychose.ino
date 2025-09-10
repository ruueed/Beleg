int AnsteigenWert(int Farbe, int &FarbAnteil)
  {
    int i;
    for (i=0;i<255; i++)
    {
      FarbAnteil=FarbAnteil+1;
      analogWrite(Farbe,FarbAnteil);
      delay(10);
      
    }
  }

int SenkenWert(int Farbe,int &FarbAnteil)
  {
    int i;
    for (i=0;i<255; i++)
    {
      FarbAnteil=FarbAnteil-1;
      analogWrite(Farbe,FarbAnteil);
      delay(10);
      
    }

  }
void setup() 
{

  #define Rot 4
  #define Gruen 5
  #define Blau 6
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
 
}

void loop() 
{
  int GruenAnteil=0;
  int RotAnteil=255;
  int BlauAnteil=0;
  int i;
  
  AnsteigenWert(Gruen,GruenAnteil);
  SenkenWert(Rot,RotAnteil);
  AnsteigenWert(Blau,BlauAnteil);
  SenkenWert(Gruen,GruenAnteil);
  AnsteigenWert(Rot,RotAnteil);
  SenkenWert(Blau,BlauAnteil);

 return 0;
  
}