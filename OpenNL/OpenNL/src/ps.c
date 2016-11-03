#include "../inc/ps.h"

/*
 *	linux
 *	create new thread
 */
// create [10/8/2016 blue]
#ifdef __linux__
id l_psNew(
	void(*p_callback)(pvoid,id),
	pvoid p_data,
	void(*s_callback)(pvoid),
	pvoid s_data)
{
	//assert(p_callback && s_callback);

	pid_t	pid = fork();

	if (pid == -1) return 0;	// create new process failed

	if (pid == 0 )
	{
		if(s_callback)
			s_callback(s_data);			// for sub-process
	}
	else
	{
		if(p_callback)
			p_callback(p_data,pid);			// for parent-process
	}

	return pid;
}
#endif // !__linux__

