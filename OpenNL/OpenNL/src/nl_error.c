#include "../inc/nl.h"

NL_Status	_NL_Current_Status;		// the status of function

char *		_NL_Status_Msg[] =
{
	"No Error.",
	"Init Socket failed",
	"Create Socket failed."
};


/*
 *	print the friendly-message for the current error
 */
// create [9/22/2016 blue]
void
nlShowError()
{
	// print the message for current status
	perror(_NL_Status_Msg[_NL_Current_Status]);
}

/*
 *	return the current status
 */
// create [9/22/2016 blue]
NL_Status
nlGetError()
{
	return _NL_Current_Status; // return it
}