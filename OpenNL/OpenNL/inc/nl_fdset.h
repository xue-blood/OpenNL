#include "nl_define.h"


typedef bool(*FdCallback)(pvoid);

typedef struct _NlFdData
{
	Link		_link;
	NLSocket	Fd;
	FdCallback	Callback;
	pvoid		param;
}NlFdData,*PNLFdData;

typedef struct _NLFd
{
	fd_set	FdSet_In;
	int		MaxFd;
	Link	Data;
}NLFd,*PNLFd;
void	nlFdInit(_Inout_	PNLFd	nlfd);
void	nlFdUninit(_Inout_	PNLFd	nlfd);
void	nlFdAdd(_Inout_	PNLFd	nlfd,NLSocket fd, bool(*callback)(pvoid), pvoid param);
void	nlFdRemove(_Inout_		PNLFd		nlfd,_In_		NLSocket	fd);
void	nlFdLoop(_In_	PNLFd	nlfd);