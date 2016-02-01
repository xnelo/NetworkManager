#ifndef ___NM_COMMON_LOGGING_HPP__2015___
#define ___NM_COMMON_LOGGING_HPP__2015___

#include <cstdlib>
#include <cstdarg>
#include <cstdio>
#include <string>

namespace LOGGING
{
    enum LOGGING_LEVELS
    {
        ALERT = 1,
        CRITICAL = 2,
        ERROR = 3,
        WARNING = 4,
        NOTICE = 5,
        INFO = 6,
        INFORMATIONAL = INFO,
        DEBUG = 7,
        DEBUG1 = DEBUG,
        TRACE = 8,
        DEBUG2 = 8,
        DEBUG3 = 9,
        DEBUG4 = 10,
    };

    class Logger
    {
    private:
        FILE * _loggingFp; ///< The file to log to. Default = stdout.
        static Logger * _instance; ///< The logger instance.
    public:
        /**
         * Get the pointer to the singleton instance of the logger.
         *
         * @return A pointer to the Logger singleton.
         */
        static Logger * GetInstance();

        /**
         * Destructor
         */
        ~Logger();

        /**
         *
         */
        void Log(LOGGING_LEVELS level, const char * msg, ...);
        void Log(LOGGING_LEVELS level, std::string & msg);

        void LogAndPrint(LOGGING_LEVELS level, const char * msg, ...);
        void LogAndPrint(LOGGING_LEVELS level, std::string & msg);

    private:
        /**
         * Constructor
         */
        Logger();

        /**
         * Copy Constructor.
         * @param other A reference to an existing Logger Object.
         */
        Logger(const Logger & other);

        /**
         * Equal operator
         * @param other A reference to an existing Logger Object.
         * @return A reference to this Logger object.
         */
        Logger & operator = (const Logger & other);

        /**
         * Clean up the static singleton for the logger.
         */
        static void _CleanInstance();
    };
} //end namespace LOGGING


inline void LOGGING::Logger::Log(LOGGING_LEVELS level, std::string & msg)
{
    Log(level, msg.c_str());
}

inline void LOGGING::Logger::LogAndPrint(LOGGING_LEVELS level, std::string & msg)
{
    LogAndPrint(level, msg.c_str());
}

#endif // ___NM_COMMON_LOGGING_HPP__2015___
