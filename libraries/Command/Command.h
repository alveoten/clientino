/*
 * Command.h
 *
 *  Created on: 25 set 2017
 *      Author: marco
 */

#ifndef LIBRARIES_COMMAND_COMMAND_H_
#define LIBRARIES_COMMAND_COMMAND_H_

#include <string.h>
#include <stdint.h>
#include <WString.h>
#include <ESP8266WiFiMulti.h>
#include "../Ssid/Ssid.h"

#define CS_TO_INITIALIZE 0
#define CS_OK 1
#define CS_KO 2

#define METHOD_POST 1
#define METHOD_GET 2
#define MAX_NUM_SSID 10

class Command{
	char status = CS_TO_INITIALIZE;
	String returnMessage;
	char * command;
	ESP8266WiFiMulti wifiMulti;
	Ssid SSIDlist[MAX_NUM_SSID];

	uint8_t numOfParams, numberOfSSID;

	uint8_t countParameters(char *);

	String returnHTTPResponse(char ** parameters, uint8_t method);

	//COMMANDS

	/**
	 * command:
	 * GET|url|return header(1 or 0) default 0
	 *
	 * Response:
	 * the http response with or without header
	 *
	 */
	String GET(char **);

	/**
	 * command:
	 * POST|url|payload|return header(1 or 0) default 0
	 *
	 * Response:
	 * the http response with or without header
	 *
	 */
	String POST(char **); //POST|url|payload

	/**
	 * command:
	 * ADDSSID|ssidname|ssidpassword
	 *
	 * Response:
	 * OK
	 * or
	 * KO|message
	 */
	String addSSID(char **);

	/**
	 * command:
	 * GETCONNECTEDSSID
	 *
	 * Response:
	 * NAMEofSSIDCOnnected
	 * or
	 * NOT_CONNECTED
	 *
	 */
	String getConnectedSSID();

	/**
	 * command:
	 * GETSSIDLIST
	 *
	 * Response:
	 * SSID1|SSID2|SSID3...
	 * or
	 * NO_SSID
	 *
	 */
	String getSSIDList();
public:
	Command(char * command, uint8 numberOfSSID);
	char getStatus() const;
	const String& getReturnMessage() const;
};


#endif /* LIBRARIES_COMMAND_COMMAND_H_ */
