/*
  Duscha Nu e-ink display

  V1.0 - September 2022
  David Sjunnesson
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "EEPROM.h"
#include "HTML.h"
#include "DEV_Config.h"
#include "EPD.h"
#include "GUI_Paint.h"

#include <WebServer.h>
WebServer server(80);
//String for storing server response
String response = "";
//Provide your own WiFi credentials
const char* ssid = "<Your WiFi SSID>";
const char* password = "<Your WiFi Password>";
const char* hostname = "Duscha Nu";

//JSON document
DynamicJsonDocument doc(2048);

//current electric price
int currentPrice = 1;

#include "powerManagement.h"
#include "WiFiManager.h"
#include "API.h"
#include "display.h"

void setup(void) {
  //For troubleshooting
  Serial.begin(115200);

  pinMode(2, OUTPUT); // feedback LED
  pinMode(15, INPUT); //for resetting WiFi creds
  checkForWiFiReset(); // check to see if button is pressed during boot

  print_wakeup_reason();  // see why we woke up, it should be for timer expired


  EEPROM.begin(400);    // configure the EEProm for storage of Wifi credentials

  if (!CheckWIFICreds()) {
    Serial.println("No WIFI credentials stored in memory. Loading form...");
    digitalWrite(2, HIGH);
    while (loadWIFICredsForm());
  }
  connectToWiFi();
  setupScreen();
  prepareSleep();
}

void loop(void) {
  while (currentPrice < 0) {
    checkAPI();
  }
  updateScreen(currentPrice);
  goToSleep();
}
