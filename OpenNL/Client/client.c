#include "../OpenNL/inc/nl.h"
#pragma comment(lib,"../Debug/OpenNL.lib")

#include <stdio.h>

#define PORT 9000

bool	con(NLSocket sock, PNLSockAddr addr)
{
	printf("connect fail, try again.\n");

	Sleep(30);

	return true;
}

bool	coned(NLSocket sock, PNLSockAddr addr)
{
	printf("connected to server.\n");

	char s_msg[100], r_msg[100];
	memzero(r_msg, sizeof(r_msg));

	recv(sock, r_msg, sizeof(r_msg), 0);

	printf("%s\n", r_msg);

	while (true)
	{
		memzero(s_msg, sizeof(s_msg));
		memzero(r_msg, sizeof(r_msg));

		printf("input:");
		scanf_s("%s", s_msg, sizeof(s_msg));

		send(sock, s_msg, strlen(s_msg), 0);

		recv(sock, r_msg, sizeof(r_msg), 0);

		printf("output:%s\n", r_msg);
	}

	nlClose(sock);

	return true;
}

void main()
{

	if (!nlInit(2, 0))	{ nlShowError();	return; }	// init win-sock for windows


	NLSocket sock = nlClientCreate(AF_INET, SOCK_STREAM, 0, "127.0.0.1", PORT);
	
	nlFuncConnectFail(con);
	nlFuncConnectSuccess(coned);

	nlClientLoop();
	
	nlUnInit();
}