//needed for WIFI Manager library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          	//https://github.com/tzapu/WiFiManager
									//https://github.com/kentaylor/WiFiManager

//for LED status - ONLY FOR ESP8266 Devices
#include <Ticker.h>
Ticker ticker;

void tick(){
        //toggle state
        int state = digitalRead(BUILTIN_LED); 	// get the current state of GPIO1 pin
        digitalWrite(BUILTIN_LED, !state); 		// set pin to the opposite state
}

//gets called when WiFiManager enters configuration mode
void configModeCallback (WiFiManager *myWiFiManager) {
        //Serial.println("Entered config mode");
        WiFi.softAPIP();
        //if you used auto generated SSID, print it
        myWiFiManager->getConfigPortalSSID();
        //entered config mode, make led toggle faster
        ticker.attach(0.2, tick);
}
