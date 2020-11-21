#include<ESP8266WiFi.h>
#include<BlynkSimpleEsp8266.h>

int laser1 = 6, laser2 = 4;
int sens1 =7, sens2 = 5;
int pirsensor=2;
unsigned int count;
unsigned int capacity;

char auth[]="rRd51633mKgEyVhW43BOWlyTTBosqjs1";
char ssid[]="NetworkName";
char pass[]="password";

BLYNK_WRITE(V0)
{
  int capacity = param.asInt();
  
}

void setup() 
{
  Serial.begin(9600);
  pinMode(laser1,OUTPUT);
  pinMode(laser2,OUTPUT);
  pinMode(sens1,INPUT); 
  pinMode(sens2,INPUT);
  pinMode(pirsensor,INPUT);
  Blynk.begin(auth,ssid,pass);
}

int temp()
{
  
}

int pir()
{
  int val=digitalRead(pirsensor);
  return val;
}

int laser()
{
  
 int time1,time2;
 digitalWrite(laser1,HIGH);
 digitalWrite(laser2,HIGH);
 int val1 = digitalRead(sens1);
 int val2 = digitalRead(sens2);

 if(val1==0)
 {
  time1=millis();
 }
 if(val2==0)
 {
  time2=millis();
 }
 int interval=time2-time1;

 if(interval>0)
 {
  count++;
 }
 else if(interval<0)
 {
  count--;
 }
 

 return count;
 
}

void loop()
{
 Blynk.run();
 
 if(pir()==1)
 {
  laser();
 }

 if(count>(capacity/2))
 {
  Blynk.notify("Overcrowding, bahar nikalo salo ko");
 }

}
