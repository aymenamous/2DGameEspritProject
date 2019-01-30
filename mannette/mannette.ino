const int bouton1= 2 ;
const int bouton2= 3 ;
const int bouton3= 4 ;
const int bouton4= 5 ;

int etatbouton1, etatbouton2, etatbouton3, etatbouton4;
char i;

void setup()
{
  pinMode(bouton1, INPUT);
  pinMode(bouton2, INPUT);
  pinMode(bouton3, INPUT);
  pinMode(bouton4, INPUT);
  
  etatbouton1 = HIGH ;
  etatbouton2 = HIGH ;
  etatbouton3 = HIGH ;
  etatbouton4 = HIGH ;
  
  Serial.begin(9600);
}

void loop()
{
  etatbouton1 = digitalRead(bouton1);
  etatbouton2 = digitalRead(bouton2);
  etatbouton3 = digitalRead(bouton3);
  etatbouton4 = digitalRead(bouton4);
  
if(Serial.available()>0)
{
  if(etatbouton1 == LOW )
  {
   i='a';
   etatbouton1=HIGH;
  } else
if(etatbouton2 == LOW )
  {
   i='b';
   etatbouton2=HIGH;
  } else
if(etatbouton3 == LOW )
  {
   i='c';
   etatbouton3=HIGH;
  } else
if(etatbouton4 == LOW )
  {
   i='d';
   etatbouton4=HIGH;
  }
  Serial.println(i);
}
}
