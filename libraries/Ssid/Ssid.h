/*
 * Ssid.h
 *
 *  Created on: 25 set 2017
 *      Author: marco
 */

#ifndef LIBRARIES_SSID_SSID_H_
#define LIBRARIES_SSID_SSID_H_

#include "WString.h"

class Ssid{
	String ssid;
	String password;
public:
	Ssid() {
	}
	const String& getPassword() const;
	void setPassword(const String& password);
	const String& getSsid() const;
	void setSsid(const String& ssid);
};


#endif /* LIBRARIES_SSID_SSID_H_ */
