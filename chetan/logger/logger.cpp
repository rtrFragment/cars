#include <cstdarg>

#include "logger.h"
#include "utils.h"

Logger* Logger::logger = nullptr;

Logger::Logger() {}
Logger::Logger(const Logger&) {};

void Logger::initialize(const char *fileName)
{
    if(logger == nullptr)
    {
        char dateTime[100] = {0};
        size_t size = currentDateTime(dateTime, sizeof(dateTime));

        logger = new Logger();
        logger->logfile = fopen(fileName, "w");

        if(logger->logfile == NULL)
        {
            printf("Cannot open log file '%s'\n", fileName);
        }
        else
        {
            fprintf(logger->logfile, "-----------------------------------\n");
            fprintf(logger->logfile, "| Logs start: %s |\n", dateTime);
            fprintf(logger->logfile, "-----------------------------------\n");
            fflush(logger->logfile);
        }
    }
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
    va_list args;
    va_start(args, message);
    logger->log(file, function, line, "[Info]", message, args);
    va_end(args);
}

void Logger::error(const char *file, const char *function, int line, const char *message, ...)
{
    va_list args;
    va_start(args, message);
    logger->log(file, function, line, "[Error]", message, args);
    va_end(args);
}

void Logger::log(const char *file, const char *function, int line, const char *tag, const char *message, va_list args)
{
    if(logger->logfile == NULL)
    {
        return;
    }

    char dateTime[100] = {0};
    size_t size = currentDateTime(dateTime, sizeof(dateTime));

    fprintf(logger->logfile, "%s | %s:%04d | %s | %s | ", dateTime, file, line, function, tag);
    vfprintf(logger->logfile, message, args);

    fflush(logger->logfile);
}
