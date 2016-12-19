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

#define boton D1

boolean estadoAnterior = LOW;
boolean estadoActual = LOW;

int cont = 0;

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
  pinMode(boton, INPUT);
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  }

boolean antiRebote(boolean eAnterior)
{
  boolean eActual = digitalRead(boton);
  if (eAnterior != eActual)
  {
    delay(5);
    eActual = digitalRead(boton);
  }
  return eActual;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      }
  estadoActual = antiRebote(estadoAnterior);
  if (estadoAnterior == LOW && estadoActual == HIGH){
    client.add("boton", estadoActual); //Insert your variable Labels and the value to be sent
    client.ubidotsPublish("emergencia");
    client.loop();
  } else if (estadoAnterior == LOW && estadoActual == LOW) {
    client.add("boton", estadoAnterior); //Insert your variable Labels and the value to be sent
    client.ubidotsPublish("emergencia");
    client.loop();
}
  estadoAnterior = estadoActual;
  }