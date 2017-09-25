#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "libraries/Command/Command.h"
#include "config.h"

ESP8266WiFiMulti wifiMulti;
String connectedTo = "";

//The setup function is called once at startup of the sketch
void setup()
{


	  Serial.begin(9600);
	  delay(10);

	  for(unsigned int i=0; i<(sizeof(ssidList)/sizeof(Ssid)); i++ ){
		  wifiMulti.addAP(ssidList[i].ssid, ssidList[i].password);
	  }

	  //define a config.h to set the multi ssid connection
	  //see config.example.h
	  Serial.println("Connecting ...");
	  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
		  delay(500);
		  Serial.print('.');
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
		String from_serial = Serial.readString();
		HTTPClient http;

		if(WiFi.status() != WL_CONNECTED){
			Serial.println("Connecting ...");
			while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
				  delay(500);
				  Serial.print('.');
			}
		}

		Command command( (char*) from_serial.c_str() );
		if(command.getStatus() == CS_KO){
			Serial.print("invalid command: ");
			Serial.println(from_serial);
			return;
		}

		int httpCode;

		if( strcmp("GET", command.getMethod() ) == 0  ){
			String destination(command.getUrl());
			destination += '?';
			destination + command.getQuery();

			http.begin(destination);
			httpCode = http.GET();
		}
		else if( strcmp("POST", command.getMethod() ) == 0  ){
			String destination(command.getUrl());
			String query(command.getQuery());
			http.begin(destination);
			httpCode = http.POST(query);
		}
		else{
			Serial.print("invalid method: ");
			Serial.println(command.getMethod());
			return;
		}

		Serial.print("method: ");
		Serial.println(command.getMethod());

		Serial.print("url: ");
		Serial.println(command.getUrl());

		Serial.print("query: ");
		Serial.println(command.getQuery());



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

