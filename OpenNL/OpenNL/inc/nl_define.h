#include "nl_pre.h"


#ifndef NL_DEFINE_H
#define NL_DEFINE_H


/*
*	i-p  address
*/
typedef	struct in_addr		NLIp,	*PNLIp;
typedef struct in_addr6		NLIp6,	*PNLIp6;

/*
*	socket address
*/
typedef struct sockaddr		NLSockAddr,		*PNLSockAddr;
typedef struct sockaddr_in	NLSockAddr4,	*PNLSockAddr4;
typedef struct sockaddr_in6 NLSockAddr6,	*PNLSockAddr6;

typedef struct hostent		NLHost,			*PNLHost;



// socket 
#ifdef WIN32
typedef	SOCKET				NLSocket;
#elif __linux__
typedef int					NLSocket;
#define SOCKET_ERROR		(-1)
#define Sleep		sleep
#define scanf_s		scanf
#endif // WIN32

#ifndef _In_
#define _In_
#define _Out_
#define _Inout_
#endif


typedef enum _NL_Status
{
	NL_Success = 0,

	NL_Socket_Init_Failed,	
	NL_Socket_Create_Failed,
	NL_Bind_Failed,
	NL_Listen_Failed
}NL_Status, *PNL_Status;
#endif