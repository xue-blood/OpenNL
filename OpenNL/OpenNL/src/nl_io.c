#include <stdio.h>
#include "../inc/nl.h"

void 
nlFdInit(
_Inout_	PNLIO	nlfd)
{
	FD_ZERO(&nlfd->FdSet_In);
	linkInit(&nlfd->Data);
	nlfd->MaxFd = 1;
}

void
nlFdUninit(
_Inout_	PNLIO	nlfd)
{
	linkClear(&nlfd->Data);

}

void 
nlFdAdd(PNLIO nlfd,NLSocket fd, bool(*callback)(pvoid),pvoid param)
{
	/*
	 *	store callback
	 */
	PNLIOData f = (PNLIOData)malloc(sizeof(NLIOData));
	f->Callback = callback;
	f->Fd = fd;
	f->param = param;
	linkInsertTail(&nlfd->Data, f);
	
	FD_SET(fd, &nlfd->FdSet_In);

	nlfd->MaxFd += fd;
}

void
nlFdRemove(
_Inout_		PNLIO		nlfd, 
_In_		NLSocket	fd)
{
	PNLIOData p = (PNLIOData)nlfd->Data.BLink;
	while (!linkIsHead(p,&nlfd->Data))
	{
		if (p->Fd == fd)
		{
			linkRemoveEntry(p);
			free(p); p = NULL;
			return;
		}

		p = (PNLIOData)p->_link.BLink;
	}
}

void nlFdReload(PNLIO nlfd)
{
	FD_ZERO(&nlfd->FdSet_In);

	int max = 0;
	PNLIOData p = (PNLIOData)nlfd->Data.BLink;
	while (!linkIsHead(p, &nlfd->Data))
	{
		if (p->Fd > max) max = p->Fd;
		FD_SET(p->Fd, &nlfd->FdSet_In);

		p = (PNLIOData)p->_link.BLink;
	}

	nlfd->MaxFd = max + 1;
}

void 
nlFdLoop(_In_ PNLIO nlfd)
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

		PNLIOData p = (PNLIOData)nlfd->Data.BLink;
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
						PNLIOData next = (PNLIOData)p->_link.BLink;
						nlFdRemove(nlfd, p->Fd);
						p = next;
						continue;
					}
				}
			}
			
			p=(PNLIOData)p->_link.BLink;
		}

		//printf("one loop end.\n");
	}
}