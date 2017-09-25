# clientino
ESP8266 firmware to make HTTP request by serial. 

It's just a simple client to use with another board like an arduino or anyother one.
No need of AT commands, just sends the Clientino simples one. 
After connected to one of specified ssid it will accept an HTTP command.

If the ESP8266 lose the WiFi connection, it will retry to connect at the next HTTP request.

The command string is a terminated case sensitive line:

	COMMANDS
		HTTP REQUEST
*METHOD|URL|PAYLOAD*

*METHOD*
The http method. Clientino supports GET o POST.

*URL* 
The url to connect. You must provide http or https (not yet supported).
Without query string.

*PAYLOAD*
In GET method is the query string 

		ADD AN SSID //todo
*ADDSSID|SSID|PASSWORD*

*ADDSSID* is the command
*SSID* is the name of ssid
*PASSWORD* is the password

	//TODO
- ADDSID command 
- a simple Arduino API library 

