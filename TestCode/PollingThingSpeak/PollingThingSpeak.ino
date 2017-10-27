// WiFi Manager details
#include <ESP8266WiFi.h>    
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 

WiFiManager wifiManager;
WiFiClient  client;

// ThingSpeak details
#include "ThingSpeak.h"
unsigned long myChannelNumber = 352618;
const char * myWriteAPIKey = "JSPGFKETLJEQ28PA";
const char * myReadAPIKey = "C76TLVC2HCO96CKX";
const char* host = "api.thingspeak.com";

void setup(){
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);

    //reset saved settings
    //wifiManager.resetSettings();

    wifiManager.autoConnect("AutoConnectAP");

    Serial.print("Connection successful");
    ThingSpeak.begin(client);
    
    
}

void loop() {
    for (int i = 0; i<10; i++){
    ThingSpeak.writeField(myChannelNumber, 1, i, myWriteAPIKey);
    Serial.print("Data sent");
    delay(10000);
    }
  }