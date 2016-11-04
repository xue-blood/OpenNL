#include "../inc/nl.h"

PNLHost nlHsName(char * name)
{
	PNLHost host;
	NLSockAddr4 addr;

	if (inet_pton(AF_INET,name, &addr.sin_addr) != 0)
	{
		host = gethostbyaddr((char *)&addr, sizeof(addr), AF_INET);
	}
	else
	{
		host = gethostbyname(name);
	}

	return host;
}