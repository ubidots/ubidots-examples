/****************************************
 * Descripcion de valores del sensor
 * 0   - 300    Seco
 * 300 - 700    Humedo
 * 700 - 950    En agua
 ****************************************/


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
#define MQTTCLIENTNAME "....." // Your MQTT Client Name, it must be unique so we recommend to choose a random ASCCI name

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

      Serial.print("Sensor de Humedad valor:");
      Valor = analogRead(A0);
      Serial.print(Valor);
      if (Valor <= 300)
        Serial.println(" Seco, necesitas regar");
      if ((Valor > 300) and (Valor <= 700))
        Serial.println(" Humedo, no regar");
      if (Valor > 700)
        Serial.println(" Encharcado");
      delay(1000);
  
  client.add("sensor", Valor); //Insert your variable Labels and the value to be sent
  client.ubidotsPublish("jardin");
  client.loop();
  }