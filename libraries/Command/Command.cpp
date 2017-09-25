#include "Command.h"
#include <string.h>

char* Command::getMethod() const {
	return method;
}

char* Command::getQuery() const {
	return query;
}

char Command::getStatus() const {
	return status;
}

char* Command::getUrl() const {
	return url;
}

Command::Command(char* command) {
	method = strtok(command, "|");
	url = strtok(NULL, "|");
	query = strtok(NULL, "|");

	if(method == NULL || url == NULL || query == NULL){
		status = CS_KO;
		return;
	}

	status = CS_OK;

}
/*
 * Command.cpp
 *
 *  Created on: 25 set 2017
 *      Author: marco
 */




