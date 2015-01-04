#pragma once

#include <winsock2.h>
#include <iostream>

#define IPADDRESS "127.0.0.1"
#define PORT 60070

class ServerNotFound {
};

class Connection
{
private:
	bool connected;
	SOCKET m_socket;
	int bufferMaxSize;
public:
	Connection(int bufferMaxSize);
	~Connection(void);
	bool open();
	void send(const char * msg);
	void receive(char * msg);
	void close();
	
};

