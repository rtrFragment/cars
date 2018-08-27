#pragma once

#include <stdlib.h>
#include <stdio.h>

// #define logInfo(x) Logger::info(__FILE__, __FUNCTION__, __LINE__, x)
#define logInfo(x, ...) Logger::info(__FILE__, __FUNCTION__, __LINE__, x, __VA_ARGS__)

class Logger
{

public:
    static void init(const char *fileName);
    static void info(const char *file, const char *function, int line, const char *format, ...);
    static void close();

private:
    Logger();
    ~Logger();
    Logger(const Logger&);

    static Logger* logger;

    FILE *logfile;
};
