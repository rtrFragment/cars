#include <stdlib.h>

#include "logger.h"

int main()
{
    bool logFileCreated = Logger::initialize("debug.log");

    if(logFileCreated)
    {
        logInfo("This is a log with parameter %d.\n", 1);
        logInfo("This is simple log.\n");
        logError("This is an error with message: %s.\n", "Sample error");

        Logger::close();
    }

    return 0;
}
