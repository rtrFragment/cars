#include <cstdarg>

#include "logger.h"
#include "utils.h"

Logger* Logger::logger = nullptr;

Logger::Logger() {}
Logger::Logger(const Logger&) {};

bool Logger::initialize(const char *fileName)
{
    bool logFileCreated = true;

    if(logger == nullptr)
    {
        char dateTime[100] = {0};
        size_t size = currentDateTime(dateTime, sizeof(dateTime));

        logger = new Logger();
        fopen_s(&logger->logfile, fileName, "w");

        if(logger->logfile == NULL)
        {
            printf("Cannot open log file '%s'\n", fileName);
            logFileCreated = false;
        }
        else
        {
            fprintf(logger->logfile, "-----------------------------------\n");
            fprintf(logger->logfile, "| Logs start: %s |\n", dateTime);
            fprintf(logger->logfile, "-----------------------------------\n");
            fflush(logger->logfile);
        }
    }

    return logFileCreated;
}

Logger::~Logger()
{
    if(logger->logfile == NULL)
    {
        return;
    }

    char dateTime[100] = {0};
    size_t size = currentDateTime(dateTime, sizeof(dateTime));

    fprintf(logger->logfile, "-----------------------------------\n");
    fprintf(logger->logfile, "| Logs end: %s   |\n", dateTime);
    fprintf(logger->logfile, "-----------------------------------\n");
    fflush(logger->logfile);
    fclose(logger->logfile);
    logger->logfile = nullptr;
}

void Logger::close()
{
    delete logger;
    logger = nullptr;
}

void Logger::info(const char *file, const char *function, int line, const char *message, ...)
{
    if(logger->logfile == NULL)
    {
        return;
    }

    char dateTime[100] = {0};
    size_t size = currentDateTime(dateTime, sizeof(dateTime));
    fprintf(logger->logfile, "%s | [Info] | %s:%04d | %s | ", dateTime, file, line, function);

    va_list args;
    va_start(args, message);
    vfprintf(logger->logfile, message, args);
    va_end(args);

    fflush(logger->logfile);
}

void Logger::error(const char *file, const char *function, int line, const char *message, ...)
{
    if(logger->logfile == NULL)
    {
        return;
    }

    char dateTime[100] = {0};
    size_t size = currentDateTime(dateTime, sizeof(dateTime));
    fprintf(logger->logfile, "%s | [Error] | %s:%04d | %s | ", dateTime, file, line, function);

    va_list args;
    va_start(args, message);
    vfprintf(logger->logfile, message, args);
    va_end(args);

    fflush(logger->logfile);
}
