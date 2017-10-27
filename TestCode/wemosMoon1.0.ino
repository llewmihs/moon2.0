
#include <Adafruit_NeoPixel.h> 
#include <ESP8266WiFi.h> // Include the ESP8266Library
#include "ThingSpeak.h"

#define pixelPin D5 //which pin is the neopixel on? define pixelNum 1 //how many neopixels am I using?
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, pixelPin,NEO_GRB + NEO_KHZ800);

WiFiClient  client;

const char* ssid     = "Christmas"; // Enter your WiFi network name
const char* password = "Christmas"; // Enter your WiFi password

const char* host = "api.thingspeak.com";
unsigned long myChannelNumber = 205995; // The channel of Cheerlights
const char * myWriteAPIKey = "EVG568HW9O4PEOL2";
const char * myReadAPIKey = "CAHA4GNUL7EMRKEL";

const int tilt = D1;
int tiltState;

int initColour;
int currentColour;
int webColour;

int count = 0;

void setup() {
  strip.begin();
  strip.show();
  pinMode(tilt, INPUT_PULLUP);
  Serial.begin(19200);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to WiFi network -  ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  ThingSpeak.begin(client);
 
  initColour = ThingSpeak.readFloatField(myChannelNumber, 1, myReadAPIKey);
  
  Serial.println(initColour);
  strip.setPixelColor(0, Wheel(initColour));
  strip.show();
  
}

void loop() {

//    initColour = ThingSpeak.readFloatField(myChannelNumber, 1, myReadAPIKey);
 
  tiltState = digitalRead(tilt);

  if (tiltState == HIGH){
    for (int i = 0; i < 255; i++){
      currentColour = i;
      Serial.println(currentColour);
      strip.setPixelColor(0, Wheel(currentColour));
      strip.show();
      Serial.print("Current globe colour is: ");
      Serial.println(currentColour);
      
      tiltState = digitalRead(tilt);
      if (tiltState == LOW){
        Serial.println("Updating ThingSpeak");
        ThingSpeak.writeField(myChannelNumber, 1, currentColour, myWriteAPIKey); 
        break;
      }
      delay(50);
    }
  }

   if (count == 60){
   webColour = ThingSpeak.readFloatField(myChannelNumber, 1, myReadAPIKey);
   Serial.print("Current online colour is: ");
   Serial.println(webColour);
   
   if (webColour != currentColour){
      currentColour = webColour;
      strip.setPixelColor(0, Wheel(currentColour));
      strip.show();
   }
   count = 0;
   }
   delay(1000);
count ++;
Serial.print("Count is: ");
Serial.println(count);
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
