#include "NewPing.h"
#include <Stepper.h>

#define motorB2 4 
#define motorB1 5 
#define motorA2 6 
#define motorA1 7  
 
#define stepPin1 8
#define stepPin2 9
#define stepPin3 10
#define stepPin4 11

#define triggerPin 12
#define echoPin 13
 
NewPing sonar(triggerPin, echoPin, 500);

Stepper step(200, stepPin4, stepPin3, stepPin2, stepPin1);

#define orta 0
#define solCapraz -1
#define sagCapraz 1

int state;
int sensorYeniKonum = orta;
int sensorGuncelKonum = orta;
bool acikMi = true;

void setup() {

    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT); 

    pinMode(stepPin1, OUTPUT);
    pinMode(stepPin2, OUTPUT);
    pinMode(stepPin3, OUTPUT);
    pinMode(stepPin4, OUTPUT);
                  
    step.setSpeed(60);
    
    Serial.begin(9600);
}
 
void loop() {
  
    if(Serial.available() > 0){     
      state = Serial.read();   
    }
    acikMi=false;
    
    switch (state) {     
      case 'F':       
        sensorYeniKonum = orta;
        SensorKonumunuGuncelle();
       
        acikMi=EngelkontrolEt();
        
        if(acikMi)
        {
          ileri();
        }
        else
        {
          engelVar();
        }   
        break;
        
      case 'G':       
        sensorYeniKonum = solCapraz;
        SensorKonumunuGuncelle();
        
        acikMi=EngelkontrolEt();
        
        if(acikMi)
        {
          ileriSol();
        }
        else
        {
          engelVar();
        }  
        break;
        
      case 'I':
        sensorYeniKonum = sagCapraz;
        SensorKonumunuGuncelle();      
        
        acikMi=EngelkontrolEt();
        
        if(acikMi)
        {
          ileriSag();
        }
        else
        {
          engelVar();
        }   
        break;
        
      case 'B':
        geri();
        break;
        
      case 'H':
        geriSol();
        break;
        
      case 'J':
        geriSag();
        break;
        
      case 'L':
        sol();
        break;
        
      case 'R':
        sag();
        break;
        
      case 'S':
        dur();
        break;
    }
}

void SensorKonumunuGuncelle()
{
  if(sensorGuncelKonum!=sensorYeniKonum)
  { 
       dur();
       switch(sensorYeniKonum)
       {
          case orta:
            switch(sensorGuncelKonum)
            {
                case solCapraz:
                  SaatTersYonu(64);
                  delay(1000);
                  break;
                  
                case sagCapraz:
                  SaatYonu(64);
                  delay(1000);
                  break;
            }
            break;  
          
          case solCapraz:
            switch(sensorGuncelKonum)
            {
                case orta:
                  SaatYonu(64);
                  delay(1000);
                  break;
                  
                case sagCapraz:
                  SaatYonu(128);
                  delay(1000);
                  break;
            }
            break;
          
          case sagCapraz:
            switch(sensorGuncelKonum)
            {
                case orta:
                  SaatTersYonu(64);
                  delay(1000);
                  break;
                  
                case solCapraz:
                  SaatTersYonu(128);
                 delay(1000);
                  break;
            }
            break;
       }     
  }
  sensorGuncelKonum = sensorYeniKonum;
}

void SaatYonu(int adimSayisi) {
  for (int i = 0; i < adimSayisi; i++) 
  {
    digitalWrite(stepPin4, HIGH);
    delay(3);
    digitalWrite(stepPin4, LOW);
    digitalWrite(stepPin3, HIGH);
    delay(3);
    digitalWrite(stepPin3, LOW);
    digitalWrite(stepPin2, HIGH);
    delay(3);
    digitalWrite(stepPin2, LOW);
    digitalWrite(stepPin1, HIGH);
    delay(3);
    digitalWrite(stepPin1, LOW);
  }
}
void SaatTersYonu(int adimSayisi) {
  for (int i = 0; i < adimSayisi; i++) 
  {
    digitalWrite(stepPin1, HIGH);
    delay(3);
    digitalWrite(stepPin1, LOW);
    digitalWrite(stepPin2, HIGH);
    delay(3);
    digitalWrite(stepPin2, LOW);
    digitalWrite(stepPin3, HIGH);
    delay(3);
    digitalWrite(stepPin3, LOW);
    digitalWrite(stepPin4, HIGH);
    delay(3);
    digitalWrite(stepPin4, LOW);
  }
}

bool EngelkontrolEt()
{
  float distance = sonar.ping_cm();
  
  if (distance < 10 && distance != 0) 
  {
    return false;
  }
  else 
  {  
    return true; 
  }
}

void engelVar()
{
  dur();
  delay(400);
}

void ileri()
{ 
  analogWrite(motorA1, 255); analogWrite(motorA2, 0);
  analogWrite(motorB1, 255); analogWrite(motorB2, 0); 
}

void ileriSol()
{
  analogWrite(motorA1,255 ); analogWrite(motorA2, 0);  
  analogWrite(motorB1, 100); analogWrite(motorB2, 0);
}

void ileriSag()
{
  analogWrite(motorA1, 100); analogWrite(motorA2, 0); 
  analogWrite(motorB1, 255); analogWrite(motorB2, 0); 
}

void geri()
{
  analogWrite(motorA1, 0); analogWrite(motorA2, 255); 
  analogWrite(motorB1, 0); analogWrite(motorB2, 255); 
}

void geriSol()
{
  analogWrite(motorA1, 0); analogWrite(motorA2, 100); 
  analogWrite(motorB1, 0); analogWrite(motorB2, 255); 
}

void geriSag()
{
  analogWrite(motorA1, 0); analogWrite(motorA2, 255); 
  analogWrite(motorB1, 0); analogWrite(motorB2, 100); 
}

void sol()
{
  analogWrite(motorA1, 255); analogWrite(motorA2, 150); 
  analogWrite(motorB1, 0);   analogWrite(motorB2, 0); 
}

void sag()
{
  analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
  analogWrite(motorB1, 255); analogWrite(motorB2, 150);   
}

void dur()
{
  analogWrite(motorA1, 0); analogWrite(motorA2, 0); 
  analogWrite(motorB1, 0); analogWrite(motorB2, 0);
}
