#include "nl_define.h"


typedef bool(*FdCallback)(pvoid);

typedef struct _NLIOData
{
	Link		_link;
	NLSocket	Fd;
	FdCallback	Callback;
	pvoid		param;
}NLIOData,*PNLIOData;

typedef struct _NLIO
{
	fd_set	FdSet_In;
	int		MaxFd;
	Link	Data;
}NLIO,*PNLIO;
void	nlFdInit(_Inout_	PNLIO	nlfd);
void	nlFdUninit(_Inout_	PNLIO	nlfd);
void	nlFdAdd(_Inout_	PNLIO	nlfd,NLSocket fd, bool(*callback)(pvoid), pvoid param);
void	nlFdRemove(_Inout_		PNLIO		nlfd,_In_		NLSocket	fd);
void	nlFdLoop(_In_	PNLIO	nlfd);