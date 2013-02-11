#include <SoftwareSerial.h>
#include <URMSerial.h>

#include <Servo.h>

/*
Ardu serial simple protocol 
V1.0 
based on & credits to: ROBOTMAN 
source: http://forums.trossenrobotics.com/tutorials/how-to-diy-128/complete-control-of-an-arduino-via-serial-3300/ 

to do: 
Werken aan de preciese besturing bij het draaien.
werken aan een return message mechanisme. 
*/

unsigned long serialdata;
int inbyte;
int digitalState;
int pinNumber;
int analogRate;
URMSerial urm;
Servo head;
Servo left;
Servo right;
int value;
void setup()
{
  Serial.begin(9600);
  head.attach(9);
  left.attach(10);
  right.attach(11);
  
  left.write(90);
  right.write(90);
  urm.begin(6,7,9600);                 // RX Pin, TX Pin, Baud Rate
}

void loop()
{
  getSerial();
  switch(serialdata)
  {
  case 1:
    {
      //analog digital write
      getSerial();
      switch (serialdata)
      {
      case 1:
        {
          //analog write
          getSerial();
          pinNumber = serialdata;
          getSerial();
          analogRate = serialdata;
          pinMode(pinNumber, OUTPUT);
          analogWrite(pinNumber, analogRate);
          pinNumber = 0;
          break;
        }
      case 2:
        {
          //digital write
          getSerial();
          pinNumber = serialdata;
          getSerial();
          digitalState = serialdata;
          pinMode(pinNumber, OUTPUT);
          if (digitalState == 0)
          {
            digitalWrite(pinNumber, LOW);
          }
          if (digitalState == 1)
          {
            digitalWrite(pinNumber, HIGH);
          }
          pinNumber = 0;
          break;
          
        }
     }
     break; 
     case 3:
     {
        //movement or head servo;
       getSerial();
       switch(serialdata)
       {
        case 1: //movement
           movement();
        case 2: //head turn
          getSerial();
          head.write(serialdata);
          break;
       } 
     }
     case 4: // get sensor info
     {
        //movement or head servo;
       getSerial();
       switch(serialdata)
       {
        case 1: //sonar
          switch(urm.requestMeasurementOrTimeout(DISTANCE, value))
          {
           case 1: 
            Serial.print("/4/1/");
            Serial.print(value);
           Serial.print("/"); 
            break;
          }
          break; 
       } 
     }
   }
  }
}

long getSerial()
{
  serialdata = 0;
  while (inbyte != '/')
  {
    inbyte = Serial.read(); 
    if (inbyte > 0 && inbyte != '/')
    {
     
      serialdata = serialdata * 10 + inbyte - '0';
    }
  }
  inbyte = 0;
  return serialdata;
}

void movement()
{
  getSerial();
  switch(serialdata)
  {
     case 360: //foreward
          left.write(serialdata - 180);
          right.write(serialdata - 360);
          Serial.println("/3/1/"+serialdata);
          break;
     case 180: // backward
          left.write(serialdata - 180);
          right.write(serialdata);
          Serial.println("/3/1/"+serialdata);
          break;
     case 270: //rechts
         left.write(serialdata - 90);
         right.write(serialdata - 90);
         delay(1000);
         left.write(90);
         right.write(90);
         Serial.println("/3/1/"+serialdata);
         break;     
     case 90: //links 
         left.write(serialdata - 90);
         right.write(serialdata - 90);
         delay(1000);
         left.write(90);
         right.write(90);
         Serial.println("/3/1/"+serialdata);
         break;
         
     case 0:
          left.write(serialdata + 90);
          right.write(serialdata + 90);
          Serial.println("/3/1/"+serialdata);
          break;

  }
           
}

void returnMessage(int branch, int section, int data)
{
    
}

