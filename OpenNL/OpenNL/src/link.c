#include "../inc/link.h"



void
linkInit(
_Out_	void*	_linkHead)
{
	assertp(_linkHead);
	PLink	h = _linkHead;

	h->FLink = h;
	h->BLink = h;
}


num
linkLength(
_In_	PLink	_linkHead)
{
	assertp(_linkHead);

	num	l = 0;
	PLink	p = _linkHead->BLink;
	while (p != _linkHead)
	{
		p = p->BLink;
		l++;
	}
	return l;
}

void
linkInsertHead(
_Inout_ void*	_linkHead,
_Inout_ void*	_linkNode)
{
	assertp(_linkHead && _linkNode);

	PLink	h = _linkHead;
	PLink	n = _linkNode;

	n->FLink = h;
	n->BLink = h->BLink;

	h->BLink = n;
	if (h->FLink == h)
		h->FLink = n;
}

void
linkInsertTail(
_Inout_ void*	_linkHead,
_Inout_ void*	_linkNode)
{
	assertp(_linkHead && _linkNode);

	PLink	h = _linkHead;
	PLink	n = _linkNode;

	n->FLink = h->FLink;
	n->BLink = h;

	n->FLink->BLink = n;
	h->FLink = n;
}

pvoid
linkRemoveHead(
_Inout_	pvoid	_linkHead)
{
	assertp(_linkHead);

	PLink	h = _linkHead,
		n = h->BLink;

	h->BLink = n->BLink;

	n->BLink->FLink = h;

	return	n;
}
pvoid
linkRemoveTail(
_Inout_	pvoid	_linkHead)
{
	assertp(_linkHead);

	PLink	h = _linkHead,
		n = h->FLink;

	h->FLink = n->FLink;
	n->FLink->BLink = h;

	return	n;
}
bool
linkRemoveEntry(
_Inout_ pvoid	_linkEntry)
{
	assertp(_linkEntry);

	PLink	n = _linkEntry;

	n->BLink->FLink = n->FLink;
	n->FLink->BLink = n->BLink;

	//
	// is the link list is empty
	//
	if (n->FLink == n)
		return true;
	else
		return false;
}

//
// clear the memory for the link list
//
// add [8/22/2016 tld]
void
linkClear(
_Inout_	PLink	_link_head)
{
	assertp(_link_head);

	while (!linkIsEmpty(_link_head))
	{
		PLink p = linkRemoveHead(_link_head);
		memfree(p);
	}
	//glusFree(_link_head);  // we needn't free head
}
