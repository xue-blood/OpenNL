#include "../inc/nl.h"

link(_Client_Function);	// store function for client loop

static	NLSocket	_NL_Socket_To_Server;
static	NLSockAddr	_NL_Addr_To_Server;

/*
 *	create a tcp-client and connect to a server
 */
// create [9/22/2016 blue]
NLSocket
nlClientTcp(
_In_	int		_af,
_In_	int		_type,
_In_	int		_proto,
_In_	char*	_ip,
_In_	short	_port)
{
	// create socket
	nlSocket(sock,_af,_type,_proto);

	// set addr
	nlSockAddr4(addr, _af, 0, _port);
	inet_pton(_af,_ip,&addr.sin_addr);


	

	_NL_Socket_To_Server	= sock;
	memcpy(&_NL_Addr_To_Server, &addr, sizeof(addr));

	return sock;
}

/*
 *	loop for client
 */
// create [9/22/2016 blue]
void
nlClientLoop()
{
	/*
	 *	is it a valid socket
	 */
	if (_NL_Socket_To_Server == SOCKET_ERROR)
		return;

	/*
	*	connect to server
	*/
	while (true)
	{
		if (connect(_NL_Socket_To_Server, &_NL_Addr_To_Server, sizeof(_NL_Addr_To_Server)) == SOCKET_ERROR)
		{
			// is there a function to handle connect fail
			if (!_NL_Function_Connect_Fail)
				break;

			// is it should connect again
			if (_NL_Function_Connect_Fail(_NL_Socket_To_Server, &_NL_Addr_To_Server))
				continue;
			else
				break;
		}
		break;	// connect successs
	}


		// call connect-success function
	if (_NL_Function_Connect_Success)
		_NL_Function_Connect_Success(_NL_Socket_To_Server, &_NL_Addr_To_Server);

}