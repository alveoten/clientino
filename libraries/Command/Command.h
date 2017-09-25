/*
 * Command.h
 *
 *  Created on: 25 set 2017
 *      Author: marco
 */

#ifndef LIBRARIES_COMMAND_COMMAND_H_
#define LIBRARIES_COMMAND_COMMAND_H_

#include <string.h>

#define CS_TO_INITIALIZE 0
#define CS_OK 1
#define CS_KO 2

class Command{
	char *method = NULL;
	char *url = NULL;
	char *query = NULL;
	char status = CS_TO_INITIALIZE;
public:
	Command(char * command);
	char* getMethod() const;
	char* getQuery() const;
	char getStatus() const;
	char* getUrl() const;
};


#endif /* LIBRARIES_COMMAND_COMMAND_H_ */
