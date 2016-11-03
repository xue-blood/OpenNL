#include "define.h"


int	tdNew(_In_	pvoid(*_func)(pvoid), _In_	pvoid	_param);

#if WIN32
#include <process.h>
#define tdExit	_endthread
#define tdID	GetCurrentThreadId		// get curent thread id

#else
#include <pthread.h>

#define tdExit()	pthread_exit(NULL)
#define	tdID		pthread_self
#define tdDel		pthread_join

#define tdDetach	pthread_detach


#define tdOnce		pthread_once
#endif