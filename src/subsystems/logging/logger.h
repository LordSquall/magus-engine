#ifndef _LOGGER_H_
#define _LOGGER_H_

/* Logging Utility Defines */

#ifdef __GNUC__

#define LOGHEADER(header) MagusEngine::Logger::LogHeader(header)
#define LOGERROR(formattedMsg, ...) MagusEngine::Logger::LogError(__FUNCTION__, __LINE__, formattedMsg, ##__VA_ARGS__)
#define LOGWARN(formattedMsg, ...) MagusEngine::Logger::LogWarning(__FUNCTION__, __LINE__, formattedMsg, ##__VA_ARGS__)
#define LOGINFO(formattedMsg, ...) MagusEngine::Logger::LogInfo(__FUNCTION__, __LINE__, formattedMsg, ##__VA_ARGS__)
#define LOGDINFO(formattedMsg, ...) MagusEngine::Logger::LogDInfo(__FUNCTION__, __LINE__, formattedMsg, ##__VA_ARGS__)

#endif

#ifdef _WIN32

#define _F_ __FUNCTION__
#define _L_	__LINE__
#define _VAARGS_ __VA_ARGS__

#define LOGHEADER(header) MagusEngine::Logger::LogHeader(header)
#define LOGERROR(formattedMsg, ...) MagusEngine::Logger::LogError(__FUNCTION__, __LINE__, formattedMsg, __VA_ARGS__)
#define LOGWARN(formattedMsg, ...) MagusEngine::Logger::LogWarning(__FUNCTION__, __LINE__, formattedMsg, __VA_ARGS__)
#define LOGINFO(formattedMsg, ...) MagusEngine::Logger::LogInfo(__FUNCTION__, __LINE__, formattedMsg, __VA_ARGS__)
#define LOGDINFO(formattedMsg, ...) MagusEngine::Logger::LogDInfo(__FUNCTION__, __LINE__, formattedMsg, __VA_ARGS__)

#endif

/* System Includes */
#include <stdio.h>
#include <stdarg.h>

namespace MagusEngine
{
	class Logger
	{
	public:
		static void LogHeader(const char* header);
		

		static void LogDInfo(const char* func, int line, const char* args, ...);

		static void LogInfo(const char* func, int line, const char* args, ...);

		static void LogWarning(const char* func, int line, const char* args, ...);
		
		static void LogError(const char* func, int line, const char* args, ...);

		static void FinaliseLogFile();

		/* 0 - Errors | 1 - Errors + Warnings | 2 - Errors + Warning + Info | 3 - Include function and line numbers */
		static int VerboseLevel;

		static bool LogToFileMode;


	private:
		static void _Log(FILE* file, const char* tag, const char* func, int line, const char* msg, va_list args);

		static FILE* _GetLogFile();

		static FILE* _logFile;
	};
}

#endif