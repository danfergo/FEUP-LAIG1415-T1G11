#include "Connection.h"
#include <string>

Connection::Connection(int bufferMaxSize): connected(false), bufferMaxSize(bufferMaxSize) 
{
	if(!this->open()){
		throw ServerNotFound();
	}
}


Connection::~Connection(void)
{
	if(connected){
		this->close();
	} 
}


bool Connection::open(){
	WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != NO_ERROR)
		printf("Client: Error at WSAStartup().\n");
    else
        printf("Client: WSAStartup() is OK.\n");

	// Create a socket.
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET) {
        printf("Client: socket() - Error at socket(): %ld\n", WSAGetLastError());
        WSACleanup();
        return false;
    }
	else
       printf("Client: socket() is OK.\n");

    // Connect to a server.
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    // Just test using the localhost, you can try other IP address
    clientService.sin_addr.s_addr = inet_addr("127.0.0.1");
    clientService.sin_port = htons(60070);

    if (connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
        printf("Client: connect() - Failed to connect.\n");
        WSACleanup();
        return false;
    }
    else {
       printf("Client: connect() is OK.\n");
       printf("Client: Can start sending and receiving data...\n");
    }

    // Send and receive data.
	printf("Connected\n");
	connected = true;
	return true;
}

void Connection::send(const char * msg){
	
	std::cout << "--> "  << msg << std::endl;
	int bytesSent = ::send(m_socket, msg, strlen(msg), 0);
	if(bytesSent == SOCKET_ERROR)
		printf("Client: send() error %ld.\n", WSAGetLastError());
}

void Connection::receive(char * msg){
	int bytesRecv = SOCKET_ERROR;
	int i, pointi;
	for(i = 0 ; i < this->bufferMaxSize; i++) {
		recv(m_socket, &msg[i], 1, 0);
		if (i > 0 && msg[i] == '\n'){
			break;
		}else if(msg[i] == '.'){
			pointi = i;
		}
	}
	if(i  == this->bufferMaxSize){
		std::cout << "ERROR, max buffer reached" << std::endl;
		return;
	}

	msg[pointi] = '\0';

	std::cout << "<-- "  << msg << std::endl;
}

void Connection::close(){
	this->send("quit.\n");
	char buff[1024];
	this->receive(buff); 
	this->connected = false;
	closesocket(m_socket);
    WSACleanup();
}
