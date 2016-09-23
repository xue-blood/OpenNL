#include "../inc/nl.h"


/*
 *	start the win-socket 
 */
// create [9/22/2016 blue]
bool
nlInit(
_In_	int  v_maj,
_In_	int  v_sub)
{
#ifdef WIN32
	WORD version = MAKEWORD(v_maj, v_sub);	// version

	WSADATA wsdata;

	if (WSAStartup(version, &wsdata))
	{
		_NL_Current_Status = NL_Socket_Init_Failed;
		return false;
	}
#endif


	return true;
}



