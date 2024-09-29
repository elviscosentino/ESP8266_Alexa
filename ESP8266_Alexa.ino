#include <ESP8266WiFi.h>
#include <Espalexa.h>
boolean connectWifi();
void firstLightChanged(uint8_t brightness);
const char* ssid = "...";
const char* password = "...";
boolean wifiConnected = false;
Espalexa espalexa;
void setup(){
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output
  pinMode(0, OUTPUT);  // Initialize the pino do Rele
  digitalWrite(0, HIGH);
  wifiConnected = connectWifi();
  if(wifiConnected){
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
    espalexa.addDevice("NOME DO DISPOSITIVO PARA FALAR: LIGAR `DISPOSITIVO`", firstLightChanged); //simplest definition, default state off
    espalexa.begin();
  }else{
    while (1) {
      digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on (Note that LOW is the voltage level
      delay(2500);
    }
  }
}
void loop(){
  espalexa.loop();
  delay(1);
}
void firstLightChanged(uint8_t brightness) {
  if (brightness) {
    digitalWrite(0, LOW);
  }else{
    digitalWrite(0, HIGH);
  }
}
boolean connectWifi(){
  boolean state = true;
  int i = 0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on (Note that LOW is the voltage level
    delay(250);
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
    delay(250);
    if (i > 20){
      state = false; break;
    }
    i++;
  }
  return state;
}