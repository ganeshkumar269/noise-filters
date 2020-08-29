#include "misc.hpp"
#ifdef _WIN32
#include <windows.h>
#else // assuming linux
#include <unistd.h>
#endif

int getCoreCount() {
#ifdef WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    return sysinfo.dwNumberOfProcessors;
#else //assuming linux
    return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}