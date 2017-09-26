#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "libraries/Command/Command.h"

String connectedTo = "";
uint8_t numberOfSSID = 0;

//The setup function is called once at startup of the sketch
void setup()
{
	  Serial.begin(9600);
	  delay(10);

	  Serial.println("waiting for commands");
}

// The loop function is called in an endless loop
void loop()
{

	if( Serial.available() > 0){
		String from_serial = Serial.readString();

		Command command( (char *) from_serial.c_str(), & numberOfSSID );
		Serial.println(command.getReturnMessage());

	}

}


