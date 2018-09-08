#pragma once

#include <stdlib.h>
#include <stdio.h>

#define logInfo(x_message, ...) Logger::info(__FILE__, __FUNCTION__, __LINE__, x_message, __VA_ARGS__)
#define logError(x_message, ...) Logger::error(__FILE__, __FUNCTION__, __LINE__, x_message, __VA_ARGS__)

class Logger
{

public:
    static bool initialize(const char *fileName);
    static void info(const char *file, const char *function, int line, const char *message, ...);
    static void error(const char *file, const char *function, int line, const char *message, ...);
    static void close();

private:
    Logger();
    ~Logger();
    Logger(const Logger&);

    void log(const char *file, const char *function, int line, const char *tag, const char *message, va_list args);

    static Logger* logger;

    FILE *logfile = nullptr;
};
