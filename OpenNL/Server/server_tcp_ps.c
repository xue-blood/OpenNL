#include "../OpenNL/inc/nl.h"
#pragma comment(lib,"../Debug/OpenNL.lib")

#include <stdio.h>

#define PORT 9000

NLSocket	sk_server;

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
	id pid = getpid();

	printf("%d : child online.\n",pid);


	char		msg[100], t_msg[100];
	NLSocket sock = *((NLSocket*)a);

	nlClose(sk_server);

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
		recv(sock, msg, sizeof(msg), 0);

		printf("%s : receive : %s\n", name,msg);

		if (strcmp(msg, "exit") == 0)
			break;

		/*
		*	send
		*/
		memzero(t_msg, sizeof(t_msg));
		convert(msg, t_msg, strlen(msg));

		printf("%s : send : %s\n", name,t_msg);

		send(sock, t_msg, strlen(t_msg), 0);
	}

	printf("%d : child  offline.\n",pid);
	exit(0);
}



bool acce(NLSocket sock, PNLSockAddr addr)
{
	static n_child;

	PNLSockAddr4 ad_client = (PNLSockAddr4)addr;
	char		ip_client[18];
	
	inet_ntop(AF_INET, &ad_client->sin_addr, ip_client, sizeof(ip_client));
	printf("client in.(%s : %d)\n", ip_client, ad_client->sin_port);

	send(sock, "welcome to server.", strlen("welcome to server."), 0);

	printf("Create new process : %d\n", psNew(0, 0, handle, &sock));
	printf("child num : %d\n", n_child++);
	nlClose(sock);

	return true;
}

void main()
{



#ifdef WIN32
	if (!nlInit(2, 0))	{ nlShowError();	return; }	// init win-sock for windows
#endif

	sk_server = nlServerTcp(AF_INET, SOCK_STREAM, 0, 9000, 3);
	if (!sk_server)
	{
		nlShowError();
		return;
	}

	nlFuncAcceptSuccess(acce);

	printf("server online.\n");
	nlServerLoop();

	int status;
	waitpid(-1, &status, 0);

	nlClose(sk_server);

	nlUnInit();
}
