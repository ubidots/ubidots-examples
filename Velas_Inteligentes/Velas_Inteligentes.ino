#include "UbidotsMicroESP8266.h"
#include <ChainableLED.h>

#define ID_Rojo  "58d323c8762542548df8fd96"  // Put here your Ubidots variable ID
#define ID_Azul  "58d323c8762542549de6f586"  // Put here your Ubidots variable ID
#define ID_Verde  "58d323cb762542548e371644"  // Put here your Ubidots variable ID
#define TOKEN  "9DriKmYujOJZ2x637376xbFtaSLvq0"  // Put here your Ubidots TOKEN
#define WIFISSID "FLIA. REVILLA"
#define PASSWORD "$apMaster123"

#define NUM_LEDS  5

ChainableLED leds(D1, D2, NUM_LEDS);

Ubidots client(TOKEN);


void setup() {
    Serial.begin(115200);
    delay(10);
    client.wifiConnection(WIFISSID, PASSWORD);
}

void loop() {
    float rojo = client.getValue(ID_Rojo);
    float azul = client.getValue(ID_Azul);
    float verde = client.getValue(ID_Verde);

    if (rojo ==  1){
      Serial.println("Led rojo encendido");
      leds.setColorRGB(0, 255, 0, 0);
    }else{
      Serial.println("Led rojo apagado");
      leds.setColorRGB(0, 0, 0, 0);      
    }
    
    if (azul == 1){
      Serial.println("Led azul encedido");
      leds.setColorRGB(0, 0, 0, 255);      
    }else{
      Serial.println("Led azul apagado");
      leds.setColorRGB(0, 0, 0, 0);      
    }
    
    if (verde == 1){
      Serial.println("Led verde encendido");
      leds.setColorRGB(0, 0, 255, 0);      
    }else{
      Serial.println("Led verde apagado");
      leds.setColorRGB(0, 0, 0, 0);      
    }

    delay(5000);
}
