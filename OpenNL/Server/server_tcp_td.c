#include "../OpenNL/inc/nl.h"
#pragma comment(lib,"../Debug/OpenNL.lib")

#include <stdio.h>

#include "../OpenNL/inc/thread.h"

#define PORT 9000


void convert(char *msg, char * t_msg, int len)
{
	id i = 0;
	for (; i < len; i++)
	{
		t_msg[i] = msg[len - i - 1];
	}
	t_msg[i] = 0;
}

void handle(pvoid a)
{
	NLSocket sock= (NLSocket)a;

	id tid = tdID();
	
	printf("%d : child online.\n", tid);


	char		msg[100], t_msg[100];
	int		status;

	char name[100];
	//	recevie name
	memzero(name,sizeof(name));
	recv(sock,name,sizeof(name),0);

	while (true)
	{

		/*
		*	receive
		*/
		memzero(msg, sizeof(msg));
		status=recv(sock, msg, sizeof(msg), 0);
		if (status <= 0)
		{
			printf("%d : client error\n",tid); 
			break;
		}
		
		printf("%s : receive : ", name); printf("%s\n", msg);
		if (strcmp(msg, "exit") == 0)
			break;

		/*
		*	send
		*/
		memzero(t_msg, sizeof(t_msg));
		convert(msg, t_msg, strlen(msg));

		printf("%s : send : ", name); printf("%s\n", t_msg);

		send(sock, t_msg, strlen(t_msg), 0);
		if (status <= 0)
		{
			printf("%d : client error\n", tid);
			break;
		}
	}


	printf("%d : child  offline.\n", tid);
	tdExit();
}

bool acce(NLSocket sock, PNLSockAddr addr)
{
	static n_child;

	PNLSockAddr4 ad_client = (PNLSockAddr4)addr;
	char		ip_client[18];

	inet_ntop(AF_INET, &ad_client->sin_addr, ip_client, sizeof(ip_client));
	printf("client in.(%s : %d)\n", ip_client, ad_client->sin_port);

	send(sock, "welcome to server.", strlen("welcome to server."), 0);

	/*
	 *	create a new thread to handle client 
	 */
	printf("Create new thread : %d\n",tdNew(handle, (pvoid)sock));

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

	nlFuncAcceptSuccess(acce);

	printf("server online.\n");
	nlServerLoop();

	nlClose(sk_server);

	nlUnInit();
}