#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "../OpenNL/inc/nl.h"
#pragma comment(lib,"../Debug/OpenNL.lib")

#include <stdio.h>


#define PORT 9000


void main()
{
	nlInit(2, 0);

	nlSocket(sock, AF_INET, SOCK_DGRAM, 0);

	nlSockAddr4(addr, AF_INET, "127.0.0.1", PORT);

	char	s_buff[100];
	while (true)
	{
		printf("input :");

		scanf_s("%s", s_buff, sizeof(s_buff));
		sendto(sock, s_buff, strlen(s_buff), 0, (PNLSockAddr)&addr, sizeof(addr));
	}

	nlClose(sock);

	nlUnInit();
}