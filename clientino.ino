#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "config.h"

ESP8266WiFiMulti wifiMulti;
String connectedTo = "";

//The setup function is called once at startup of the sketch
void setup()
{


	  Serial.begin(9600);
	  delay(10);

	  //define a config.h to set the multi ssid connection
	  //see config.example.h
	  Serial.println("Connecting ...");
	  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
		  delay(500);
		  Serial.print('.');
	  }

	  for(unsigned int i=0; i<(sizeof(ssidList)/sizeof(Ssid)); i++ ){
		  wifiMulti.addAP(ssidList[i].ssid, ssidList[i].password);
	  }

	  Serial.print("Connected to ");
	  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
	  Serial.print("IP address:\t");
	  Serial.println(WiFi.localIP());
	  Serial.println("Waiting for command..");
}

// The loop function is called in an endless loop
void loop()
{

	if( Serial.available() > 0){
		String command = Serial.readString();
		HTTPClient http;

		if(WiFi.status() != WL_CONNECTED){
			Serial.println("Connecting ...");
			while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
				  delay(500);
				  Serial.print('.');
			}
		}

		http.begin(command);
		int httpCode = http.GET();

		// httpCode will be negative on error
		if(httpCode > 0) {
			Serial.print("[HTTP-CODE: ");
			Serial.print(httpCode);
			Serial.println("]");

			// file found at server
			if(httpCode == HTTP_CODE_OK) {
				Serial.println("[HTTP-RESPONSE]");
				String payload = http.getString();
				Serial.println(payload);
			}
		} else {
			Serial.print("[HTTP] GET... failed, error: ");
			Serial.println(http.errorToString(httpCode).c_str());
		}

		http.end();

	}

}

