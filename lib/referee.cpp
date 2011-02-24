#include "referee.h"

Referee::Referee()
{

#if 0
	if ( ( _socket = (socket(AF_INET, SOCK_DGRAM, 0) ) ) < 0)
	{
		perror(__FILE__ "Error opening the socket");
		//exit(1);
	}

	u_int yes = 1;
	if ( setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0 ) {
		perror(__FILE__ "Error reusing addr" );
	}

	// setting a timeout for receiving
	// I don't know if it's a good value, but works for now
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 500;

	if ( setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO , (struct timeval *) &tv , sizeof tv ) < 0 ) {
		perror(__FILE__ "Error setting timeout" );
	}

	//PREPARANDO O SOCKET
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(REFEREE_PORT);
	addr.sin_addr.s_addr = ( strlen(REFEREE_GROUP) == 0 ?
					htonl(INADDR_ANY) :
					inet_addr(REFEREE_GROUP));


	if ( bind(_socket,(struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror(__FILE__ " Error binding the socket");
		//exit(1);
	}

	struct ip_mreq mreq;
	mreq.imr_multiaddr.s_addr = inet_addr(REFEREE_GROUP);

	mreq.imr_interface.s_addr = htonl(INADDR_ANY);

	if (setsockopt(_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
	{
		perror(__FILE__ " Error in setsockopt");
		//exit(1);
	}
#endif
}

char Referee::receive() {

#if 0 

	socklen_t addrlen;
	int nbytes;
	char msgbuf[MSGBUFSIZE];

	memset(&msgbuf, 0, MSGBUFSIZE);

	char cmd_tmp;

	//COLOCANDO O PACOTE EM msgbuf
	addrlen = sizeof(addr);
	if ((nbytes = recvfrom(_socket, msgbuf, MSGBUFSIZE, 0, (struct sockaddr *)&addr, &addrlen)) < 0)
	{
		 //perror(__FILE__ " in recvfrom");
		 //exit(1);
	}

	//DESEMPACOTANDO msgbuf
	cmd_tmp = (char)msgbuf[0];
	//cmd_counter = (int)((unsigned char)msgbuf[1]);
	//goals_blue = (int)((unsigned char)msgbuf[2]);
	//goals_yellow = (int)((unsigned char)msgbuf[3]);
	//time_remaining = ((int)(msgbuf[4])     * • Processador AMD Athlon II X2 255 3.1GHz
    * • Placa Mãe ASUS M4N68T-M LE AM3
    * • Memória Kingston Value 2GB 1333MHz
    * • HD Samsung SpinPoint F1 320GB 16MB 7200RPM SATA II
    * • Gabinete PcTop ATX com Fonte 200w
    * • Sem drive
    * • Teclado Genérico Preto USB
    * • Mouse Óptico Genérico Preto USB
    * • Software OEM Windows 7 Home Basic 64 bits<< 8)  + (int)(msgbuf[5]); //most significant byte

	//CONDIÇÃO QUANDO O COMANDO CMD ALTERADO PELO ÁRBITRO
	//	  if (cmd != cmd_tmp){
	//	     cmd_prev = cmd;
	//	     cmd = cmd_tmp;
	//	  }

	//RETORNANDO AS VARIÁVEIS
	return cmd_tmp;
#endif
}
