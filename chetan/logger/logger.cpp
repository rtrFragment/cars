#include <cstdarg>

#include "logger.h"
#include "utils.h"

Logger* Logger::logger = nullptr;

Logger::Logger() {}
Logger::Logger(const Logger&) {};

void Logger::init(const char *fileName)
{
    if(logger == nullptr)
    {
        char dateTime[100] = {0};
        size_t size = currentDateTime(dateTime);

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
    if(logger->logfile != NULL)
    {
        char dateTime[100] = {0};
        size_t size = currentDateTime(dateTime);

        fprintf(logger->logfile, "-----------------------------------\n");
        fprintf(logger->logfile, "| Logs end: %s   |\n", dateTime);
        fprintf(logger->logfile, "-----------------------------------\n");
        fclose(logger->logfile);
    }
}

void Logger::close()
{
    delete logger;
    logger = nullptr;
}

void Logger::info(const char *file, const char *function, int line, const char *format, ...)
{
    if(logger->logfile == NULL)
    {
        return;
    }

    char dateTime[100] = {0};
    size_t size = currentDateTime(dateTime);

    fprintf(logger->logfile, "%s | %s | % s | %04d: ", dateTime, file, function, line);

    va_list args;
    va_start(args, format);
    vfprintf(logger->logfile, format, args);
    va_end(args);

    fflush(logger->logfile);
}
