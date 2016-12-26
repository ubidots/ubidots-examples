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
#define MQTTCLIENTNAME ".... // Your MQTT Client Name, it must be unique so we recommend to choose a random ASCCI name

#define RELAY D1
#define LED D5

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

  if ((char)payload[0] == '1') {
      digitalWrite(RELAY, HIGH); //On relay
      digitalWrite(LED, LOW); //On led
  }
  if ((char)payload[0] == '0') {
      digitalWrite(RELAY, LOW); //Off relay
      digitalWrite(LED, HIGH); //Off led
  }
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  client.wifiConnection(WIFINAME, WIFIPASS);
  pinMode(RELAY, OUTPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  client.begin(callback);
  client.ubidotsSubscribe("relay","sonoff"); //Insert the dataSource and Variable's Labels
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      Serial.println(RELAY);
      client.ubidotsSubscribe("relay","sonoff"); //Insert the dataSource and Variable's Labels
      }
  client.loop();
  }
