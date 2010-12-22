#ifndef __ROBOPET_REFEREE__
#define __ROBOPET_REFEREE__

#include "robopet.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define REFEREE_PORT 10001
#define REFEREE_GROUP "224.5.23.1" // NUM DA PORTA MULTICAST
#define MSGBUFSIZE 6 // TAMANHO DO PACOTE EM BYTES

class RP::Referee {

	public:

	Referee();
	char receive();

	private:

	int _socket;
	struct sockaddr_in addr;

};

#endif
