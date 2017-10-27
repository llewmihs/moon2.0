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

int initColour //this is the colour of the moon set on ThingSpeak
int currentColour //the moons current colour
int comparisonColour //the colour of the moon on ThingSpeak

// and something for the NeoPixel
#include <Adafruit_NeoPixel.h> 
#define pixelPin D5 //which pin is the neopixel on? define pixelNum 1 //how many neopixels am I using?
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, pixelPin,NEO_GRB + NEO_KHZ800);

// and something here for the vibration sensor
const int x = A0;
int xVal;

void setup(){
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    wifiManager.autoConnect("AutoConnectAP");
    Serial.print("Connection successful");
    ThingSpeak.begin(client);

    // pull state data from ThingSpeak to set the initial globe colour
    initColour = ThingSpeak.readFloatField(myChannelNumber, 1, myReadAPIKey);
    strip.setPixelColor(0, Wheel(initColour));
    strip.show();
}

void loop() {
    // check for a shake

    // if there is a shake, set a new colour

    //upload that colours to ThingSpeak

    // if a mintue has passed check for an updated colour in ThingSpeak

    // compare this with the moons current colour

    //change if needed

    for (int i = 0; i<10; i++){
    ThingSpeak.writeField(myChannelNumber, 1, i, myWriteAPIKey);
    Serial.print("Data sent");
    delay(10000);
    }
  }

  uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if(WheelPos < 85) {
     return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else if(WheelPos < 170) {
      WheelPos -= 85;
     return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    } else {
     WheelPos -= 170;
     return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
  }