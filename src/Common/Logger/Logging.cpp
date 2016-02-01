#include "Common/Logger/Logging.hpp"

namespace LOGGING
{
    Logger * Logger::_instance = NULL;

    Logger * LOGGING::Logger::GetInstance()
    {
        if (_instance == NULL)
        {
            _instance = new Logger();
        }
        return _instance;
    }

    void Logger::_CleanInstance()
    {
        if (_instance != NULL)
        {
            delete _instance;
            _instance = NULL;
        }
    }

    Logger::Logger() : _loggingFp(stdout)
    {
        std::atexit(Logger::_CleanInstance);
    }

    Logger::~Logger()
    {
    }

    void Logger::Log(LOGGING_LEVELS level, const char *msg, ...)
    {
        va_list argPointer;
        va_start(argPointer, msg);
        std::vfprintf(stdout, msg, argPointer);
        va_end(argPointer);
        std::fprintf(stdout, "\n");
    }

    void Logger::LogAndPrint(LOGGING_LEVELS level, const char * msg, ...)
    {
        va_list argPointer;
        va_start(argPointer, msg);
        std::vfprintf(stdout, msg, argPointer);
        va_end(argPointer);
        std::fprintf(stdout, "\n");

        if (_loggingFp != stdout)
        {
            va_start(argPointer, msg);
            std::vfprintf(stdout, msg, argPointer);
            va_end(argPointer);
            std::fprintf(stdout, "\n");
        }
    }
}//end namespace LOGGING
