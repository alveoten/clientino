#include "Command.h"
#include <string.h>
#include <stdint.h>
#include <WString.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

extern Ssid * SSIDlist;
extern ESP8266WiFiMulti wifiMulti;

String Command::GET(char** parameters) {
	if(numOfParams < 2){
		String ret = "invalid GET command: ";
		ret += command;
		return ret;
	}

	bool returnHeaders = false;
	if(numOfParams == 3){ //isset header request params
		if( parameters[2][0]=='1' ){
			returnHeaders = true;
		}
		else if(parameters[2][0]=='0'){
			returnHeaders = false;
		}
		else{
			String ret = "invalid GET command, error param num 3: ";
			ret += command;
			return ret;
		}
	}

	return returnHTTPResponse(parameters, METHOD_GET);

}

String Command::POST(char** parameters) {
	if(numOfParams < 3){
		String ret = "invalid POST command: ";
		ret += command;
		return ret;
	}

	bool returnHeaders = false;
	if(numOfParams == 4){ //isset header request params
		if( parameters[3][0]=='1' ){
			returnHeaders = true;
		}
		else if(parameters[3][0]=='0'){
			returnHeaders = false;
		}
		else{
			String ret = "invalid POST command, error param num 4: ";
			ret += command;
			return ret;
		}
	}

	return returnHTTPResponse(parameters, METHOD_POST);
}

String Command::addSSID(char** parameters) {
	if(numOfParams < 3){
		String ret = "KO|invalid POST command: ";
		ret += command;
		return ret;
	}

	if( *numberOfSSID >= MAX_NUM_SSID){
		String ret = "KO|max number of SSID reached: ";
		ret += MAX_NUM_SSID;
		return ret;
	}

	SSIDlist[*numberOfSSID].setSsid((String) parameters[1]);
	SSIDlist[*numberOfSSID].setPassword((String) parameters[2]);
	(*numberOfSSID)++;

	wifiMulti.addAP(parameters[1],parameters[2]);

	String ret;
	ret = "Added SSID: ";
	ret += parameters[1];
	return ret;
}

String Command::getConnectedSSID() {
	String ret;
	if(WiFi.status() == WL_CONNECTED){
		return WiFi.SSID();
	}
	return "KO|Not connected";
}

String Command::getSSIDList() {
	String ret = "";
	Serial.println((*numberOfSSID));
	for(uint8_t i = 0; i<(*numberOfSSID); i++){
		ret += SSIDlist[i].getSsid();
		if(i != ((*numberOfSSID)-1) ){
			ret += "|";
		}
	}
	return ret;
}

char Command::getStatus() const {
	return status;
}

Command::Command(char* c, uint8_t * numSSID) {
	command = c;
	numOfParams = countParameters(command);
	numberOfSSID = numSSID;

	char * parameters[numOfParams];
	parameters[0] = strtok(command, "|\n");

	for(uint8_t i = 1; i < numOfParams; i++){
		parameters[i] = strtok(NULL, "|");
	}

	for(uint8_t i = 0; i<strlen(parameters[0]); i++){
		if(parameters[0][i] == ' ' || parameters[0][i] == '\r' || parameters[0][i] == '\n'){
			parameters[0][i] = '\0';
		}
	}

	if(strcmp(parameters[0],"GET") == 0){
		returnMessage = GET(parameters);
	}
	else if(strcmp(parameters[0],"POST") == 0){
		returnMessage = POST(parameters);
	}
	else if(strcmp(parameters[0],"ADDSSID") == 0){
		returnMessage = addSSID(parameters);
	}
	else if(strcmp(parameters[0],"GETCONNECTEDSSID") == 0){
		returnMessage = getConnectedSSID();
	}
	else if(strcmp(parameters[0],"GETSSIDLIST") == 0){
		returnMessage = getSSIDList();
	}
	else{
		returnMessage = "KO|invalid command: ";
		returnMessage += parameters[0];
	}

}

uint8_t Command::countParameters(char * command) {
	int len = strlen(command);
	uint8_t num_results = 1;
	for(int i=0; i<len; i++ ){
		if(command[i] == '|'){
			num_results++;
		}
	}
	return num_results;
}

String Command::returnHTTPResponse(char ** parameters, uint8_t method) {
	if( *numberOfSSID == 0){
		return "you must specify a SSID before try to do an HTTP request";
	}

	unsigned long start= millis();
	if(wifiMulti.run() != WL_CONNECTED){
		Serial.println("Connecting ...");
		while (
				wifiMulti.run() != WL_CONNECTED // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
		) {
			if( millis() - start > 10000 ){
				break;
			}
			Serial.print(".");
			delay(500);
		}
	}

	if(WiFi.status() != WL_CONNECTED){
		return "can't connect to valid SSID";
	}

	HTTPClient http;
	int httpCode;

	http.begin(parameters[1]);

	if( method == METHOD_GET ){
		httpCode = http.GET();
	}
	else if( method == METHOD_POST ){
		httpCode = http.POST(parameters[2]);
	}
	else{
		return "invalid method assert";
	}

	String response;

	// httpCode will be negative on error
	if(httpCode > 0) {
		// file found at server
		response = "[HTTP-OK:";
		response += httpCode;
		response += "]\r\n";
		response += http.getString();
	} else {
		response = "[HTTP-ERROR] ";
		response += ( ( method==METHOD_GET)? "GET":"POST" );
		response += "... failed, error: ";
		response += http.errorToString(httpCode);
	}

	http.end();
	return response;
}

const String& Command::getReturnMessage() const {
	return returnMessage;
}
/*
 * Command.cpp
 *
 *  Created on: 25 set 2017
 *      Author: marco
 */




