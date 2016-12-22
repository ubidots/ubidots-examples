/****************************************
 * Descripcion de valores del sensor
 * 0   - 50    Joyero cerrado
 * 50  - 700   Joyero abierto

 ****************************************/


/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "....." // Your Ubidots TOKEN
#define WIFINAME "...." //Your SSID
#define WIFIPASS "...." // Your Wifi Pass
#define MQTTCLIENTNAME "...." // Your MQTT Client Name, it must be unique so we recommend to choose a random ASCCI name

int Valor;

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

      Serial.println ("Valor dectectado del sensor:");
      Valor = analogRead(A0);
      Serial.println (Valor);
      
      if (Valor <= 50)
        Serial.println("Joyero Cerrado");
      if (Valor > 50) 
        Serial.println("Joyero Abierto");
      delay(1000);
  
  client.add("sensor", Valor); //Insert your variable Labels and the value to be sent
  client.ubidotsPublish("joyero");
  client.loop();
  }
