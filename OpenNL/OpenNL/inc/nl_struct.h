#include "nl_define.h"

#ifndef NL_STRUCT_H
#define NL_STRUCT_H


/*
 *	io
 */
typedef bool(*FdCallback)(pvoid);

typedef struct _NLIOData
{
	Link		_link;
	NLSocket	Fd;
	FdCallback	Callback;
	pvoid		param;
}NLIOData, *PNLIOData;

typedef struct _NLIO
{
	fd_set	FdSet_In;
	int		MaxFd;
	Link	Data;
}NLIO, *PNLIO;


#endif