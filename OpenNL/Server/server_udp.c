#include "../OpenNL/inc/nl.h"
#pragma comment(lib,"../Debug/OpenNL.lib")

#include <stdio.h>

#define PORT 9000





void main()
{
	nlInit(2, 0);

	// create a udp server
	NLSocket sk_server = nlServerUdp(AF_INET, SOCK_DGRAM, 0, PORT);

	NLSocket	sk_client;
	NLSockAddr4 addr_client;
	size		l_addr_client = sizeof(addr_client);
	num			n_recv;
	char		r_buff[100];
	char		ip_client[18];

	while (true)
	{
		n_recv = recvfrom(sk_server, r_buff, sizeof(r_buff), 0, (PNLSockAddr)&addr_client, &l_addr_client);
		if (n_recv < 0)
		{
			printf("recv fail.\n");
			break;
		}

		inet_ntop(AF_INET, (PNLSockAddr)&addr_client.sin_addr, ip_client, sizeof(ip_client));
		printf("client: (%s : %d) :\t", ip_client, addr_client.sin_port);

		r_buff[n_recv] = 0;

		printf("%s\n", r_buff);
	}

	nlClose(sk_server);
	nlUnInit();
}