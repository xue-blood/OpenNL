#include "../OpenNL/inc/nl.h"
#pragma comment(lib,"../Debug/OpenNL.lib")

#include <stdio.h>

#define PORT 9000


void convert(char *msg, char * t_msg, int len)
{
	id i = 0;
	for (; i < len;i++)
	{
		t_msg[i] = msg[len - i - 1];
	}
	t_msg[i] = 0;
}

bool acce(NLSocket sock, PNLSockAddr addr)
{
	PNLSockAddr4 ad_client = (PNLSockAddr4)addr;
	char		ip_client[18];
	char		msg[100], t_msg[100];

	inet_ntop(AF_INET, &ad_client->sin_addr, ip_client, sizeof(ip_client));
	printf("client in.(%s : %d)\n", ip_client, ad_client->sin_port);

	send(sock, "welcome to server.", strlen("welcome to server."), 0);

	while (true)
	{
		/*
		 *	receive
		 */
		memzero(msg, sizeof(msg));
		recv(sock, msg, sizeof(msg), 0);
		
		printf("receive : %s\n", msg);

		/*
		 *	send
		 */
		memzero(t_msg, sizeof(t_msg));
		convert(msg, t_msg, strlen(msg));

		printf("send : %s\n", t_msg);

		send(sock, t_msg, strlen(t_msg), 0);
	}
}
void main()
{

#ifdef WIN32
	if (!nlInit(2, 0))	{	nlShowError();	return;}	// init win-sock for windows
#endif

	NLSocket	sk_server = nlServerTcp(AF_INET, SOCK_STREAM, 0, 9000,1);
	if (!sk_server)
	{
		nlShowError();
		return;
	}

	nlFuncAcceptSuccess(acce);

	printf("wait...\n");
	nlServerLoop();


	nlClose(sk_server);

	nlUnInit();
}

