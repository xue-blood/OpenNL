#ifdef WIN32
#include <windows.h>
#include <stdbool.h>
#include <assert.h>
#elif __linux__
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#endif // WIN32

#ifndef _In_
#define _In_
#define _Out_
#define _Inout_
#endif

#ifndef bool
typedef unsigned char bool;
#define true	1
#define false	0
#endif

typedef	void *		pvoid;
typedef long long	id;
typedef	size_t		num, size;
/*
*	link list
*/
typedef	struct _Link
{
	struct _Link * BLink;
	struct _Link * FLink;
}Link, *PLink;

#define assertp		assert
/*
*	memory
*/
#define	memzero(ptr,size)	memset((ptr),0,size)
#define memfree(ptr)		if(ptr) free(ptr),(ptr)=NULL;

/*
*	see link.c
*/
#define link(Name)	Link Name={.FLink = &Name,.BLink = &Name}
#define links(Name)	Links Name={.Data.FLink = &Name.Data,.Data.BLink = &Name.Data}
void	linkInit(_Inout_ void* LinkHead);
#define linkIsEmpty(LinkHead) ((LinkHead)->FLink == (LinkHead))	// update [9/13/2016 blue] : fix bug for leave one
#define linkIsHead(point,head) ((PLink)(point) == (PLink)(head))
#define linkNext(head,current,next)	((pvoid)next)=((PLink)current)->BLink;if(linkIsHead((next),(head))) ((pvoid)next)=((PLink)head)->BLink
num		linkLength(_In_	PLink	_linkHead);
void	linkInsertHead(_Inout_ pvoid LinkHead, _Inout_ pvoid LinkNode);
void	linkInsertTail(_Inout_ void* _linkHead, _Inout_ void* _linkNode);
pvoid	linkRemoveHead(_Inout_ pvoid _linkHead);
pvoid	linkRemoveTail(_Inout_ pvoid _linkHead);
bool	linkRemoveEntry(_Inout_ pvoid _linkEntry);
void	linkClear(_Inout_	PLink	_link_head);
#define linkData(pointer)	(char*)((char*)pointer+sizeof(Link))						// get the date field pointer 
#define linkEntry(link_pointer,type,member) ((type*)((char*)pointer)-&((type*)0)->member))	// get the struct pointer from a member
