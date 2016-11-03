#ifndef _define_h_
#define _define_h_


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
typedef	size_t		num;
#ifdef WIN32
typedef size_t		size;
#else
typedef int			size;
#endif




#endif // !_define_h_
