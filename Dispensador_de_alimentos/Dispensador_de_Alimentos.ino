/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"
#include <Servo.h>

Servo myservo;

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "..." // Your Ubidots TOKEN
#define WIFINAME "..." //Your SSID
#define WIFIPASS "..." // Your Wifi Pass
#define MQTTCLIENTNAME "..." // Your MQTT Client Name, it must be unique so we recommend to choose a random ASCCI name

int pos = 0;

Ubidots client(TOKEN, MQTTCLIENTNAME);

/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if((char)payload[0] == '1')
  {
    if (pos==0)
    {
    for(pos = 0; pos <= 170; pos += 1)                          //el servo se mueve de 0 a 170 grados
   {            
     myservo.write(pos);
     delay(5);
    } 
     }
     else
     {
       myservo.write(170);
      }
     }
     else if ((char)payload[0] ==  '0')
     {
       if(pos==170)
       {
       for(pos = 170; pos>=0; pos-=1)       
        {                                
          myservo.write(pos);               
          delay(5);                         
         }
        }
       else
      {
        myservo.write(0);
       } 
       }
       else
       {
         myservo.write(170);
       }  
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  client.wifiConnection(WIFINAME, WIFIPASS);
  myservo.attach(5); // D1 pin 
  myservo.write(0);
  client.begin(callback);
  client.ubidotsSubscribe("pet","dispenser"); //Insert the dataSource and Variable's Labels
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      client.ubidotsSubscribe("pet","dispenser"); //Insert the dataSource and Variable's Labels
  }
             
  client.loop();
  }