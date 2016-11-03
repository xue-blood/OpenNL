#ifdef WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#include <WinSock2.h>
#include <ws2tcpip.h>	// for inet_pton
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")

#include <stdbool.h>
#ifdef WIN64
//define something for Windows (64-bit only)
#endif
#elif __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#elif TARGET_OS_IPHONE
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
#   error "Unknown Apple platform"
#endif
#elif __linux__
// linux
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#elif __unix__ // all unices not caught above
// Unix
#elif defined(_POSIX_VERSION)
// POSIX
#else

#   error "Unknown compiler"
#endif

#include "link.h"
#include "ps.h"
