/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "...." // Your Ubidots TOKEN
#define WIFINAME "...." //Your SSID
#define WIFIPASS "...." // Your Wifi Pass
#define MQTTCLIENTNAME "...." // Your MQTT Client Name, it must be unique so we recommend to choose a random ASCCI name

int nMuestras = 100;

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
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      }
  float instVoltage, Vpp, Irms, consumo;
  float minVoltage=5.0, maxVoltage=0.0;
  for(int i=0; i<nMuestras; i++)
  {
    instVoltage = 5.0/1023*analogRead(A0);
    if(instVoltage <= minVoltage) minVoltage = instVoltage;
    if(instVoltage >= maxVoltage) maxVoltage = instVoltage;
  }
  
  Vpp = maxVoltage - minVoltage;
  Irms = abs(1.9111*Vpp - 0.1);
  consumo = 117*Irms;
  Serial.print("Irms = ");
  Serial.print(Irms);
  Serial.println(" [A]");
  Serial.print("Consumo: ");
  Serial.print(consumo);
  Serial.println(" [VA]");
  Serial.println();
  delay (5000);
  
  client.add("Irms", Irms); //Insert your variable Labels and the value to be sent
  client.add("consumo", consumo);
  client.ubidotsPublish("Medidor");
  client.loop();
  }
