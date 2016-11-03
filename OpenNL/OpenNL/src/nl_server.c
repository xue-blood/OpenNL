#include "../inc/nl.h"

static	NLSocket	_NL_Socket_Server;
static	NLSocket	_NL_Socket_To_Client;
static	NLSockAddr	_NL_Addr_To_Client;

/*
 *	create socket, then set address and binding for server
 */
// create [9/22/2016 blue]
NLSocket
nlServerTcp(
_In_	int		_af,
_In_	int		_type,
_In_	int		_proto,
_In_	short	_port,
_In_	int		_backlog)
{
	/*
	 *	create a socket
	 */
	nlSocket(sock, _af, _type, _proto);

	/*
	 *	set sock address
	 */
	nlSockAddrex4(addr, _af, INADDR_ANY, _port);


	/*
	 *	set socket option
	 *	 only on linux
	 */
#ifdef __linux__
	int opt =1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif // __linux__

	/*
	*	binding the socket
	*/
	if (bind(sock, (PNLSockAddr)&addr, sizeof(addr)) == -1)
	{
		_NL_Current_Status = NL_Bind_Failed;
		return false;
	}

	
	/*
	 *	listen
	 */
	if (listen(sock, _backlog) == -1)
	{
		_NL_Current_Status = NL_Listen_Failed;
		return false;
	}

	_NL_Socket_Server = sock;

	// now we return the socket
	return sock;
}

/*
 *	loop for server
 */
// create [9/23/2016 blue]
void 
nlServerLoop()
{
	if (_NL_Socket_Server == SOCKET_ERROR)
		return;

	while (true)
	{
		/*
		 *	wait for client
		 */
		int len = sizeof(_NL_Addr_To_Client);
		_NL_Socket_To_Client = accept(_NL_Socket_Server, &_NL_Addr_To_Client, &len);

		if (_NL_Socket_Server == SOCKET_ERROR)
			continue;

		/*
		 *	then call the function
		 */
		if (_NL_Function_Accept_Success)	// exist callback
			if (!_NL_Function_Accept_Success(_NL_Socket_To_Client, &_NL_Addr_To_Client))	// callback return true is ok
				break;

	}
}

/*
 *	create a udp-server
 */
// create [9/23/2016 blue]
NLSocket
nlServerUdp(
_In_	int		_af,
_In_	int		_type,
_In_	int		_proto,
_In_	short	_port)
{
	/*
	*	create a socket
	*/
	nlSocket(sock, _af, _type, _proto);

	/*
	*	set sock address
	*/
	nlSockAddrex4(addr, _af, INADDR_ANY, _port);


	/*
	*	set socket option
	*	 only on linux
	*/
#ifdef __linux__
	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif // __linux__

	/*
	*	binding the socket
	*/
	if (bind(sock, (PNLSockAddr)&addr, sizeof(addr)) == -1)
	{
		_NL_Current_Status = NL_Bind_Failed;
		return false;
	}

	// now we return the socket
	return sock;
}