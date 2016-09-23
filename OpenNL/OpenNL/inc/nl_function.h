#include "nl_struct.h"

#ifndef NL_FUNCTION_H
#define NL_FUNCTION_H


/*
 *	print error
 */
#ifdef _DEBUG
#define nlError		perror
#else
#define nlError
#endif // _DEBUG

/*
 *	for NL_Status
 */
#define nlSuccess(status)	((status)== NL_Success)
#define nlFail(status)		((status)!= NL_Success)

/*
 *	see nl.c
 */
#ifdef WIN32
bool	nlInit(_In_	int  v_maj, _In_	int  v_sub);
#define nlUnInit		WSACleanup
#define nlClose(sock)			if(sock != SOCKET_ERROR) closesocket(sock),sock=SOCKET_ERROR
#else
#define nlInit(a,b)		true
#define nlUnInit
#define nlClose(sock)			if(sock != SOCKET_ERROR) close(sock),sock=SOCKET_ERROR
#endif // WIN32

#define nlSocket(name,af,type,proto)							\
			NLSocket	name = socket(af, type, proto);			\
			if (name == SOCKET_ERROR)							\
			{													\
				_NL_Current_Status = NL_Socket_Create_Failed;	\
				return false;									\
			}
#define nlSock4(name,af,ip,port)				\
			NLSockAddr4 name = { 0 };				\
			name.sin_family = af;				\
			name.sin_addr.s_addr = ip;			\
			name.sin_port = htons(port);

/*
 *	see nl_error.c
 */
void		nlShowError();
NL_Status	nlGetError();


/*
 *	see nl_server.c
 */
NLSocket	nlServerCreate(_In_	int		_af, _In_	int		_type, _In_	int		_proto, _In_	short	_port, _In_	int		_backlog);
void		nlServerLoop();
/*
 *	see nl_client.c
 */
NLSocket	nlClientCreate(_In_	int		_af, _In_	int		_type, _In_	int		_proto, _In_	char*		_ip, _In_	short	_port);
void		nlClientLoop();

/*
 *	see nl_callback.c
 */
void	nlFuncAcceptSuccess(_In_	bool(*callback)(NLSocket sock, PNLSockAddr addr));
void	nlFuncConnectSuccess(_In_	bool(*callback)(NLSocket sock, PNLSockAddr addr));
void	nlFuncConnectFail(_In_	bool(*callback)(NLSocket sock, PNLSockAddr addr));

#endif