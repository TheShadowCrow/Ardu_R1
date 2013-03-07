/*
 
 References  :
 http://binerry.de/post/27128825416/raspberry-pi-with-i2c-arduino-slave
 

================================================================================
*/
#include <SoftwareSerial.h>
#include <URMSerial.h>
#include <Servo.h>
#include <commander.h>
#include "Wire.h"

/*
  General Setup
*/
// define i2c commands
#define LED1_ON_COMMAND    "L11"

// define slave address (0x2A = 42 [the answer to the ultimate question of life, the universe, and everything ;)] )
#define SLAVE_ADDRESS 0x2A 

// instantiate i2cCommander
Commander commander = Commander();

// pin setup
int led1pin = 2;
int led2pin = 3;
int led3pin = 4;
int relaypin = 5;

// other vars
int answer = 0;

void setup() {                
  // initialize the digital pins for leds and relay as an output
  pinMode(led1pin, OUTPUT);
  pinMode(led2pin, OUTPUT);  
  pinMode(led3pin, OUTPUT);  
  pinMode(relaypin, OUTPUT);  
  
  // create commands for i2cCommander
  // led 1:
  Command_t cmdLed1On;
  cmdLed1On.execCommand = LED1_ON_COMMAND;
  cmdLed1On.callback = led1On;
  
  Command_t cmdMovement;
  cmdMovement.execCommand = "MOVE";
  cmdMovement.callback = setMove;
  
  Command_t cmdHead;
  cmdHead.execCommand = "HEAD";
  cmdHead.callback = setHead;
  
  // add commands to i2cCommander
  commander.addCommand(cmdLed1On);
 
  
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
   
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void loop() {
  
}

// callback for received data
void receiveData(int byteCount) 
{  //command is now "MOV/180;"
   boolean isData = false;
   char inByte = 0;
   String requestCommand = "";
   int data;
   while(Wire.available())
   { 
     inByte = (char)Wire.read();
     if(inByte != '/') // '/' = command data seperator
     {
       requestCommand = requestCommand + inByte;
     }
     else
     {
       isData = true;
     }
     if(isData && inByte != '/' && inByte != ';')
     {
       data = data + (int)inByte;
     }
     if(inByee = ';') // ';' = end of message token
     {
       isData= false;
     }
   }
   // ProcessCommand aanpassen en de struct dat het ook data parameters meeneemt.
   commander.processCommand(requestCommand, data);
}

// callback for sending data
void sendData()
{ 
  Wire.write(answer);  
  answer = 0;
}

void led1On(String command, int data )
{
  // switch led 1 on
  digitalWrite(led1pin, HIGH);
  
  // reply with command and success info
  answer = 1; 
}

void setMove(String command, int data)
{
  
}

void setHead(String command, int data)
{
  
}
