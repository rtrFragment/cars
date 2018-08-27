#include <stdlib.h>

#include "logger.h"

int main()
{
    Logger::init("debug.log");

    logInfo("This is a log with parameter %d.\n", 1);
    logInfo("This is simple log\n");

    Logger::close();

    return 0;
}
