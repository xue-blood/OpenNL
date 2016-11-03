#include "../inc/nl_fdset.h"
#include <stdio.h>


void 
nlFdInit(
_Inout_	PNLFd	nlfd)
{
	FD_ZERO(&nlfd->FdSet_In);
	linkInit(&nlfd->Data);
	nlfd->MaxFd = 1;
}

void
nlFdUninit(
_Inout_	PNLFd	nlfd)
{
	linkClear(&nlfd->Data);

}

void 
nlFdAdd(PNLFd nlfd,NLSocket fd, bool(*callback)(pvoid),pvoid param)
{
	/*
	 *	store callback
	 */
	PNLFdData f = (PNLFdData)malloc(sizeof(NlFdData));
	f->Callback = callback;
	f->Fd = fd;
	f->param = param;
	linkInsertTail(&nlfd->Data, f);
	
	FD_SET(fd, &nlfd->FdSet_In);

	nlfd->MaxFd += fd;
}

void
nlFdRemove(
_Inout_		PNLFd		nlfd, 
_In_		NLSocket	fd)
{
	PNLFdData p = (PNLFdData)nlfd->Data.BLink;
	while (!linkIsHead(p,&nlfd->Data))
	{
		if (p->Fd == fd)
		{
			linkRemoveEntry(p);
			free(p); p = NULL;
			return;
		}

		p = (PNLFdData)p->_link.BLink;
	}
}

void nlFdReload(PNLFd nlfd)
{
	FD_ZERO(&nlfd->FdSet_In);

	int max = 0;
	PNLFdData p = (PNLFdData)nlfd->Data.BLink;
	while (!linkIsHead(p, &nlfd->Data))
	{
		if (p->Fd > max) max = p->Fd;
		FD_SET(p->Fd, &nlfd->FdSet_In);

		p = (PNLFdData)p->_link.BLink;
	}

	nlfd->MaxFd = max + 1;
}

void 
nlFdLoop(_In_ PNLFd nlfd)
{

	while (true)
	{
		nlFdReload(nlfd);

		int status=select(nlfd->MaxFd, &nlfd->FdSet_In, NULL, NULL, NULL);

		if (status == -1)
		{
			printf("select failed.\n");
			break;
		}
		if (status == 0)
			printf("no fd ready.\n");

		//printf("select [ %d ]ok.\n",status);

		PNLFdData p = (PNLFdData)nlfd->Data.BLink;
		while (!linkIsHead(p, &nlfd->Data))
		{
			if (FD_ISSET(p->Fd, &nlfd->FdSet_In))
			{
				//printf("%d ready.\n", p->Fd);
				if (p->Callback)
				{
					bool ret = p->Callback(p->param);

					if (!ret)
					{
						PNLFdData next = (PNLFdData)p->_link.BLink;
						nlFdRemove(nlfd, p->Fd);
						p = next;
						continue;
					}
				}
			}
			
			p=(PNLFdData)p->_link.BLink;
		}

		//printf("one loop end.\n");
	}

_select_end:
	printf("select end.\n");
}