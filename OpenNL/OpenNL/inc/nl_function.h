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
bool	nlInit(_In_	int  v_maj, _In_	int  v_sub);

#ifdef WIN32
#define nlUnInit		WSACleanup
#define nlClose(sock)			if(sock != SOCKET_ERROR) closesocket(sock),sock=SOCKET_ERROR
#else
#define nlUnInit()
#define nlClose(sock)			if(sock != SOCKET_ERROR) close(sock),sock=SOCKET_ERROR
#endif // WIN32

#define nlSocket(name,af,type,proto)							\
			NLSocket	name = socket(af, type, proto);			\
			if (name == SOCKET_ERROR)							\
			{													\
				_NL_Current_Status = NL_Socket_Create_Failed;	\
				return false;									\
			}
#define nlSockAddrex4(name,af,ip,port)				\
			NLSockAddr4 name = { 0 };				\
			name.sin_family = af;				\
			name.sin_addr.s_addr = ip;			\
			name.sin_port = htons(port);

#define nlSockAddr4(name,af,ip,port)				\
			NLSockAddr4 name = { 0 };				\
			name.sin_family = af;				\
			name.sin_port = htons(port);		\
			inet_pton(af,ip,&name.sin_addr);

/*
 *	see nl_error.c
 */
void		nlShowError();
NL_Status	nlGetError();


/*
 *	see nl_server.c
 */
NLSocket	nlServerTcp(_In_	int		_af, _In_	int		_type, _In_	int		_proto, _In_	short	_port, _In_	int		_backlog);
void		nlServerLoop();
NLSocket	nlServerUdp(_In_	int		_af,_In_	int		_type,_In_	int		_proto,_In_	short	_port);

/*
 *	see nl_client.c
 */
NLSocket	nlClientTcp(_In_	int		_af, _In_	int		_type, _In_	int		_proto, _In_	char*		_ip, _In_	short	_port);
void		nlClientLoop();

/*
 *	see nl_callback.c
 */
void	nlFuncAcceptSuccess(_In_	bool(*callback)(NLSocket sock, PNLSockAddr addr));
void	nlFuncConnectSuccess(_In_	bool(*callback)(NLSocket sock, PNLSockAddr addr));
void	nlFuncConnectFail(_In_	bool(*callback)(NLSocket sock, PNLSockAddr addr));

/*
 *	io
 */
void	nlFdInit(_Inout_	PNLIO	nlfd);
void	nlFdUninit(_Inout_	PNLIO	nlfd);
void	nlFdAdd(_Inout_	PNLIO	nlfd, NLSocket fd, bool(*callback)(pvoid), pvoid param);
void	nlFdRemove(_Inout_		PNLIO		nlfd, _In_		NLSocket	fd);
void	nlFdLoop(_In_	PNLIO	nlfd);

/*
 *	get host information see nl_dns.c
 */
PNLHost nlHsName(char * name);
#endif