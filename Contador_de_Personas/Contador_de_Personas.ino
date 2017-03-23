/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "....." // Your Ubidots TOKEN
#define WIFINAME "....." //Your SSID
#define WIFIPASS "....." // Your Wifi Pass
#define MQTTCLIENTNAME "....." // Your MQTT Client Name, it must be unique so we recommend to choose a random ASCCI name

#define PIR_MOTION_SENSOR 2//Use pin 2 to receive the signal from the module
#define LED 4//the Grove - LED is connected to D4 of Arduino

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
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(PIR_MOTION_SENSOR, INPUT);
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      }
      
  isPeopleDetected();
        
  client.add("personas", counter); //Insert your variable Labels and the value to be sent
  client.ubidotsPublish("contador");
  client.loop();
  delay(1000);
  }

long isPeopleDetected(){
  
  int sensorValue = digitalRead(PIR_MOTION_SENSOR);
  if(sensorValue == HIGH){
     counter++;
     return counter;
  }
}
