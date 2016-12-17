/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"
#include <map>

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "p4uuT2OIIFJwv7ncTVfoVqcfImwRQW" // Your Ubidots TOKEN
#define WIFINAME "UBIWIFI" //Your SSID
#define WIFIPASS "clave123456789ubi" // Your Wifi Pass
#define MQTTCLIENTNAME "sdfcvdhjnbvxw" // Your MQTT Client Name, it must be unique so we recommend to choose a random ASCCI name
#define MQTTCLIENTNAME2 "sdfcvdhjnbvxw2"
#define MQTTCLIENTNAME3 "sdfcvdhjnbvxw3"
#define MQTTCLIENTNAME4 "sdfcvdhjnbvxw4"
#define MQTTCLIENTNAME5 "sdfcvdhjnbvxw5"
#define MQTTCLIENTNAME6 "sdfcvdhjnbvxw6"
#define MQTTCLIENTNAME7 "sdfcvdhjnbvxw7"

//Piano constants
#define BUZZER D1 //Buzzer pin
const int DO  = 262;
const int RE  = 294;
const int MI  = 330;
const int FA  = 349;
const int SOL = 392;
const int LA  = 440;
const int SI  = 494;

int basic_notes[ ] = {DO, RE, MI, FA, SOL, LA, SI};
String ubi_switch[ ] = {"do", "re", "mi", "fa", "sol", "la", "si"};

Ubidots client(TOKEN, MQTTCLIENTNAME);
Ubidots client2(TOKEN, MQTTCLIENTNAME2);
Ubidots client3(TOKEN, MQTTCLIENTNAME3);
Ubidots client4(TOKEN, MQTTCLIENTNAME4);
Ubidots client5(TOKEN, MQTTCLIENTNAME5);
Ubidots client6(TOKEN, MQTTCLIENTNAME6);
Ubidots client7(TOKEN, MQTTCLIENTNAME7);

/****************************************
 * Define Initial Values
 ****************************************/

/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  int flag = 0;
    
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  if ((char)payload[0]=='1'){
    digitalWrite(16, HIGH);
    tone(BUZZER, basic_notes[note(topic)]);
    delay((1000/4)*1.30);
    noTone(BUZZER);
  }
  else{
    digitalWrite(16, LOW);
    noTone(BUZZER);
  }
  Serial.println();
  
}

int note(char* topic){
  char * pch;
  char * token = strtok(topic, "/");
  
  while (token != NULL){
      for (int i=0; i<8; i++){
        if(String(token)==ubi_switch[i]){
          Serial.println("");
          Serial.println(ubi_switch[i]);
          Serial.println(basic_notes[i]);
          return i;
          //tone(BUZZER, basic_notes[i]);
          break;
        }
      }
  token = strtok(NULL, "/");
  }
  
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  client2.begin(callback);
  client3.begin(callback);
  client4.begin(callback);
  client5.begin(callback);
  client6.begin(callback);
  client7.begin(callback);
  client.ubidotsSubscribe("piano", "do");
  client2.ubidotsSubscribe("piano", "re");
  client3.ubidotsSubscribe("piano", "mi");
  client4.ubidotsSubscribe("piano", "fa");
  client5.ubidotsSubscribe("piano", "sol");
  //client6.ubidotsSubscribe("piano", "la");
  //client7.ubidotsSubscribe("piano", "si");
  pinMode(16, OUTPUT);
  }

void loop() {
  //Send to Ubidots Routine
  if(!client.connected()){
      client.reconnect();
      client.ubidotsSubscribe("piano", "do");
      client2.ubidotsSubscribe("piano", "re");
      client3.ubidotsSubscribe("piano", "mi");
      client4.ubidotsSubscribe("piano", "fa");
      client5.ubidotsSubscribe("piano", "sol");
      //client6.ubidotsSubscribe("piano", "la");
      //client7.ubidotsSubscribe("piano", "si");
     }
  client.loop();
  client2.loop();
  client3.loop();
  client4.loop();
  client5.loop();
  client6.loop();
  client7.loop();
  }
