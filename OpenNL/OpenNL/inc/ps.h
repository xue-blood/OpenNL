#include"define.h"



#ifdef WIN32
id w_psNew(void(*p_callback)(pvoid,id), pvoid p_data, void(*c_callback)(pvoid), pvoid c_data);


#define psNew	w_psNew

#else 
#include <sys/types.h>
#include <unistd.h>

id l_psNew(void(*p_callback)(pvoid, id), pvoid p_data, void(*c_callback)(pvoid), pvoid c_data);

#define psNew	l_psNew
#endif // WIN32
