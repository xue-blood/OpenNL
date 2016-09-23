#include"../inc/nl.h"

typedef bool(*loop_callback)(NLSocket sock, PNLSockAddr addr);

// create [9/23/2016 blue]


/*
 *	store the call back function
 */
loop_callback	_NL_Function_Accept_Success,
				_NL_Function_Connect_Success,
				_NL_Function_Connect_Fail;


/*
 *	set the function for call back
 */
void
nlFuncAcceptSuccess(
_In_	bool(*callback)(NLSocket sock, PNLSockAddr addr))
{
	assertp(callback);
	_NL_Function_Accept_Success		= callback;
}
void
nlFuncConnectSuccess(
_In_	bool(*callback)(NLSocket sock, PNLSockAddr addr))
{
	assertp(callback);
	_NL_Function_Connect_Success	= callback;
}
void
nlFuncConnectFail(
_In_	bool(*callback)(NLSocket sock, PNLSockAddr addr))
{
	assertp(callback);
	_NL_Function_Connect_Fail = callback;
}
