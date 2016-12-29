/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"
#include "DHT.h" //cargamos la librería DHT
#define DHTPIN D3 //Seleccionamos el pin en el que se //conectará el sensor
#define DHTTYPE DHT11 //Se selecciona el DHT11 (hay //otros DHT)

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "...." // Your Ubidots TOKEN
#define WIFINAME "...." //Your SSID
#define WIFIPASS "....." // Your Wifi Pass
#define MQTTCLIENTNAME "....." // Your MQTT Client Name, it must be unique so we recommend to choose a random ASCCI name


#define motor D6

DHT dht(DHTPIN, DHTTYPE);

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
  dht.begin();
  pinMode(motor, OUTPUT);
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      }
      
  float t = dht.readTemperature();

 
  Serial.println("Temperatura: ");
  Serial.println(t);

 
  if (t > 27){
    digitalWrite(motor, HIGH);
    Serial.println("Ventilador encendido");
    Serial.println(digitalRead(motor));
  }
  else
  {
    digitalWrite(motor, LOW);
    Serial.println("Ventilador apagado");
    Serial.println(digitalRead(motor));
  }

  delay(2000);
  
  client.add("temperature", t); //Insert your variable Labels and the value to be sent
  client.ubidotsPublish("control");
  client.loop();
  }
