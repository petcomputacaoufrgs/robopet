///RoboPET Referee
/**
 *  Simple class to communicate with the standard
 *  RoboCUP referee socket
 */

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

using RP::Referee;

class Referee {

	public:

	Referee();

	/**
	 Queries the referee for the next command. This method won't block
	 and thus will return an error value if no data was available

	 @return Returns the current referee command or -1 if not available
	 */
	char receive();

	private:

	int _socket;
	struct sockaddr_in addr;

};

#endif
