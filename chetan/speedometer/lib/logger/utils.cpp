#include <sstream>
#include <time.h>

size_t currentDateTime(char *dateTimeString, size_t size)
{
    time_t now = time(NULL);
    struct tm tmStruct;

    #if defined (_WIN32) // check for Windows

    _localtime64_s(&tmStruct, &now);

    #elif defined (__linux) // check for Linux

    localtime_r(&now, &tmStruct);

    #endif

    return strftime(dateTimeString, size, "%d-%m-%Y %H:%M:%S", &tmStruct);
}
