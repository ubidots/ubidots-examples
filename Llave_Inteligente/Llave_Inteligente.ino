/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"
#include <MFRC522.h> // Descargar e incluir la librería
#include <Servo.h>
#include <SPI.h>

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "9DriKmYujfdfdOJZ2x637376xbFtaSLvq0" // Your Ubidots TOKEN
#define WIFINAME "ubidots" //Your SSID
#define WIFIPASS "123456789ubi" // Your Wifi Pass
#define MQTTCLIENTNAME "asdkjasdasd" // Your MQTT Client Name, it must be unique so we recommend to choose a random ASCCI name

#define ledPinAbierto D0
#define SAD 4
#define RST 5

MFRC522 nfc(SAD, RST);
Servo myservo;

Ubidots client(TOKEN, MQTTCLIENTNAME);

#define AUTHORIZED_COUNT 2 // Para autoriazar más tarjetas ponemos el número aqui y la añadimos abajo
byte Authorized[AUTHORIZED_COUNT][6] = {

                            {0xD0, 0xD0, 0x17, 0x2B, 0x3C,}//,{0x39, 0x79, 0x7C, 0x9E, 0xA2,}// ejemplo de como autorizar más tarjetas  0x83,.....
                            
                          };
                          
void printSerial(byte *serial);
boolean isSame(byte *key, byte *serial);
boolean isAuthorized(byte *serial);

byte status;
byte data[MAX_LEN];
byte serial[5];
boolean Abierto = false;

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
  
  if ((char)payload[0]=='1'){
    digitalWrite(ledPinAbierto, HIGH);
  }
  else if ((char)payload[0] ==  '0')
  {
  digitalWrite(ledPinAbierto, !Abierto);
  myservo.write(0);
  status = nfc.requestTag(MF1_REQIDL, data);

  if (status == MI_OK) {
    status = nfc.antiCollision(data);
    memcpy(serial, data, 5);
    
    if(isAuthorized(serial))
    { 
      Serial.println("Autorizado");
      Abierto = true;
      myservo.write(90);
      delay(5000);
      myservo.write(0);
    }
    else
    { 
      printSerial(serial);
      Serial.println("NO autorizado");
      Abierto = false;
    }
    
    nfc.haltTag();
    digitalWrite(ledPinAbierto, Abierto);
    delay(2000);
  }//if (status == MI_OK)

  delay(500);
  }
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPinAbierto  , OUTPUT);   
  myservo.attach(D3);
  SPI.begin();
  Serial.begin(115200);
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  client.ubidotsSubscribe("control","acceso"); //Insert the dataSource and Variable's Labels
  Serial.println("Buscando RC522");
  nfc.begin();
  
  byte version = nfc.getFirmwareVersion();
  if (! version) {//Entra si no encuentra el módulo.
    Serial.print("No ha encontrado RC522");
    while(1); //detener
  }

  Serial.print("Ha encontrado RC522");
  Serial.print("Firmware version 0x");
  Serial.print(version, HEX);
  Serial.println(".");
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      client.ubidotsSubscribe("control","acceso"); //Insert the dataSource and Variable's Labels
      }
  client.loop();
  }

boolean isSame(byte *key, byte *serial)
{
    for (int i = 0; i < 4; i++) {
      if (key[i] != serial[i])
      { 
        return false; 
      }
    }
    
    return true;

}

boolean isAuthorized(byte *serial)
{
    for(int i = 0; i<AUTHORIZED_COUNT; i++)
    {
      if(isSame(serial, Authorized[i]))
        return true;
    }
   return false;
}

void printSerial(byte *serial)
{
        Serial.print("Serial:");
    for (int i = 0; i < 5; i++) { // aumentar a 5 para leer el número de la tarjeta completo
      Serial.print(serial[i], HEX);
      Serial.print(" ");
    }
}

