#include "../OpenNL/inc/nl.h"
#pragma comment(lib,"../Debug/OpenNL.lib")

#include <stdio.h>


#define PORT 9000

NLFd   _FD;

void convert(char *msg, char * t_msg, int len)
{
	id i = 0;
	for (; i < len; i++)
	{
		t_msg[i] = msg[len - i - 1];
	}
	t_msg[i] = 0;
}

bool handle(pvoid a)
{
	NLSocket sock= (NLSocket)a;


	char	msg[100], t_msg[100];
	int		status;

	/*
	 *	receive message
	 */
	memzero(msg, sizeof(msg));
	status = recv(sock, msg, sizeof(msg), 0);
	if (status <= 0) goto _client_end_;


	printf("%d : receive : ", sock); 
	printf("%s\n", msg);
	if (strcmp(msg, "exit") == 0)
		goto _client_end_;

	/*
	*	send
	*/
	memzero(t_msg, sizeof(t_msg));
	convert(msg, t_msg, strlen(msg));

	printf("%d : send : ", sock); 
	printf("%s\n", t_msg);

	send(sock, t_msg, strlen(t_msg), 0);
	if (status <= 0)   goto _client_end_;


	return true;

_client_end_:

	printf("%d : client end\n", sock);
	return false;

}

bool acce(pvoid param)
{

	NLSocket sk_ls = (NLSocket)param;

	/*
	 *	accept a client
	 */
	NLSockAddr4 ad_client;
	int l_addr = sizeof(ad_client);
	NLSocket	sock = accept(sk_ls, (PNLSockAddr)&ad_client, &l_addr);

	char		ip_client[18];
	inet_ntop(AF_INET, &ad_client.sin_addr, ip_client, sizeof(ip_client));
	printf("client in.(%s : %d)\n", ip_client, ad_client.sin_port);

	send(sock, "welcome to server.", strlen("welcome to server."), 0);

	/*
	 *	add a new fd_data to fd-set 
	 */
	nlFdAdd(&_FD, sock, handle, (pvoid)sock);
	printf("add a new fd %d .\n", sock);

	return true;
}

void main()
{

#ifdef WIN32
	if (!nlInit(2, 0))	{ nlShowError();	return; }	// init win-sock for windows
#endif

	NLSocket sk_server = nlServerTcp(AF_INET, SOCK_STREAM, 0, 9000, 3);
	if (!sk_server)
	{
		nlShowError();
		return;
	}

	/*
	 *	prepare fd-set
	 */
	nlFdInit(&_FD);	// init nl-fd

	nlFdAdd(&_FD, sk_server, acce, (pvoid)sk_server); // the listen socket

	printf("server online.\n");
	
	nlFdLoop(&_FD);

	nlFdUninit(&_FD);

	nlClose(sk_server);

	nlUnInit();
}