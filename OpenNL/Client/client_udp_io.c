#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "../OpenNL/inc/nl.h"
#pragma comment(lib,"../Debug/OpenNL.lib")


#include <stdio.h>
#include <string.h>
#include "../OpenNL/inc/nl_fdset.h"

NLSocket _sock;
NLSockAddr4 _Addr;

bool input(pvoid param)
{
	char buff[100]={0};

	scanf("%s", buff);

	//printf("input now.\n");

	sendto(_sock, buff, strlen(buff), 0, (PNLSockAddr)&_Addr, sizeof(_Addr));

	printf("send :%s\n", buff);

	return true;
}

bool msged(pvoid param)

{
	char buff[100]={0};

	NLSockAddr4 addr;
	socklen_t len = sizeof(addr);
	recvfrom(_sock, buff, sizeof(buff), 0, (PNLSockAddr)&addr, &len);


	printf("recv :%s\n", buff);

	return true;
}



bool main(int argc,char ** argv)
{
	nlInit(2, 0);

	nlSocket(sock, AF_INET, SOCK_DGRAM, 0);
	
	/*
	 *	my socket addr
	 */
	nlSockAddr4(myaddr, AF_INET, 0, atoi(argv[1]));
	inet_pton(AF_INET, "127.0.0.1", &myaddr.sin_addr);
	
	/*
	 *	peer socket addr
	 */
	nlSockAddr4(peeraddr, AF_INET, 0, atoi(argv[2]));
	inet_pton(AF_INET, "127.0.0.1", &peeraddr.sin_addr);


	/*
	 *	binding port and connect to peer
	 */
	if (bind(sock, (PNLSockAddr)&myaddr, sizeof(myaddr)) < 0)
	{
		printf("bind port failed.\n");
		exit(0);
	}
	connect(sock, (PNLSockAddr)&peeraddr, sizeof(peeraddr));
	_sock = sock;
	_Addr = peeraddr;

	NLFd nlfd;

	nlFdInit(&nlfd);

	nlFdAdd(&nlfd,fileno(stdin), input, NULL);// add send callback
	nlFdAdd(&nlfd,sock, msged, NULL);			// add receive callback
	nlFdAdd(&nlfd,fileno(stdin), input, NULL);// add send callback

	nlFdLoop(&nlfd);

	nlFdUninit(&nlfd);

	nlClose(sock);

	nlUnInit();
}