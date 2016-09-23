#include "nl_function.h"


#ifndef NL_H
#define NL_H

extern	NL_Status	_NL_Current_Status;	// extern from nl_error.c


typedef bool(*loop_callback)(NLSocket sock, PNLSockAddr addr);

// extern from nl_callback.c
extern loop_callback	_NL_Function_Accept_Success,
						_NL_Function_Connect_Success,
						_NL_Function_Connect_Fail;

#endif