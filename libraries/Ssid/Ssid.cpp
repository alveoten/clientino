#include "Ssid.h"
#include "WString.h"

const String& Ssid::getPassword() const {
	return password;
}

void Ssid::setPassword(const String& password) {
	this->password = password;
}

const String& Ssid::getSsid() const {
	return ssid;
}

void Ssid::setSsid(const String& ssid) {
	this->ssid = ssid;
}

Ssid SSIDlist[MAX_NUM_SSID];

/*
 * Ssid.cpp
 *
 *  Created on: 25 set 2017
 *      Author: marco
 */




