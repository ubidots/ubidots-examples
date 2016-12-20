/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"

int _pin = D3;
long duration;
long distancia;

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "...." // Your Ubidots TOKEN
#define WIFINAME "...." //Your SSID
#define WIFIPASS "...." // Your Wifi Pass
#define MQTTCLIENTNAME "...." // Your MQTT Client Name, it must be unique so we recommend to choose a random ASCCI name


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
  
  // Publish the distance values 
  readCm();
  delay(5000);
  String value = String (distancia);
  client.add("volumen", distancia); //Insert your variable Labels and the value to be sent
  client.ubidotsPublish("reserva");
  client.loop();
  }

  long readCm(){
    
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(_pin,LOW);
  pinMode(_pin,INPUT);
  duration = pulseIn(_pin,HIGH);  
  distancia = duration/29/2;
  Serial.println(distancia);
  
  return distancia;
}
