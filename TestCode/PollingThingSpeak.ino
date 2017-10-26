// WiFi Manager details
#include <ESP8266WiFi.h>    
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> 

// ThingSpeak details
#include "ThingSpeak.h"



void setup(){
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);

    WiFiManager wifiManager;

    //reset saved settings
    //wifiManager.resetSettings();

    wifiManager.autoConnect("AutoConnectAP");

    Serial.print("Connection successful");
}

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);     
    // read the input on analog pin 0:
    //int sensorValue = analogRead(A0);

    // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
    // pieces of information in a channel.  Here, we write to field 1.
    //ThingSpeak.writeField(myChannelNumber, 1, voltage, myWriteAPIKey);
    //delay(20000); // ThingSpeak will only accept updates every 15 seconds.
  }