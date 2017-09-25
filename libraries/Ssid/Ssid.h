/*
 * Ssid.h
 *
 *  Created on: 25 set 2017
 *      Author: marco
 */

#ifndef LIBRARIES_SSID_SSID_H_
#define LIBRARIES_SSID_SSID_H_

class Ssid{

public:
	char ssid[32] = {'\0'};
	char password[32] = {'\0'};
	Ssid(const char *,const char *);
};


#endif /* LIBRARIES_SSID_SSID_H_ */
