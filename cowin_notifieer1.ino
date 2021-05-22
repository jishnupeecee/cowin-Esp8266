#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define ARDUINOJSON_ENABLE_PROGMEM 0
#include <ArduinoJson.h>  // v6.18.0
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Fonts/FreeMono9pt7b.h>

const char* SSID = "kvbpc";                 // Your WiFi SSID
const char* PASSWORD = "kvbpc@457";  // Your WiFi Password

const int districtID = 80;          // District ID
const int minAge = 45;             // 45 or 18
const String date = "22-05-2021";  // Date for slot in DD-MM-YYYY format

const String baseURL = "http://arduino-cowin.centralindia.cloudapp.azure.com/?districtID=";
const String URL = baseURL + districtID + "&date=" + date + "&minAge=" + minAge;

int ledPin = LED_BUILTIN;

bool slotFound = false;
HTTPClient http;

void pingServer() 
{
  http.begin(URL);
  int httpCode = http.GET();

  if (httpCode == 200) 
  {
    slotFound = true;
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else 
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);                      
    digitalWrite(LED_BUILTIN, HIGH);
   }

  http.end();
}
void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  
}
   

void loop() {
  if (slotFound) 
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  pingServer();
  delay(3000);  // IP Address will be blocked if you call API more than onece per 5 minute
}
