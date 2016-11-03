#include"../inc/thread.h"


/*
 *	create a new thread
 */
int
tdNew(
_In_	pvoid(*	_func)(pvoid),
_In_	pvoid	_param)
{
	assert(_func);

#if WIN32
	
	
	return GetThreadId(_beginthread(_func, 0, _param));

	
#else

	pthread_t	tid;
	pthread_create(&tid, NULL, _func, _param);


	return tid;
#endif
}
