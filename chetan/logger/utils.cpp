#include <sstream>
#include <time.h>

#if defined (_WIN32) // check for Windows

size_t currentDateTime(char *dateTimeString)
{
    time_t now = time(NULL);
    struct tm tmStruct;
    _localtime64_s(&tmStruct, &now);
    return strftime(dateTimeString, 100, "%d-%m-%Y %H:%M:%S", &tmStruct);
}

#elif defined (__linux) // check for Linux

size_t currentDateTime(char *dateTimeString)
{
    time_t now = time(NULL);
    struct tm tmStruct;
    localtime_r(&now, &tmStruct);
    return strftime(dateTimeString, sizeof(dateTimeString), "%d-%m-%Y.%H.%M.%S", &tmStruct);
}

#endif
