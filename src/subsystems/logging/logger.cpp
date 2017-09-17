#include "logger.h"

namespace MagusEngine
{
	FILE* Logger::_logFile = 0;

	int	 Logger::VerboseLevel = 0;
	bool Logger::LogToFileMode = false;


	void Logger::LogHeader(const char* header)
	{
		fprintf(stdout, "********************************************************************************\n");
		fprintf(stdout, "%s\n", header);
		fprintf(stdout, "********************************************************************************\n");
	
		if (LogToFileMode == true)
		{
			fprintf(_GetLogFile(), "********************************************************************************\n");
			fprintf(_GetLogFile(), "%s\n", header);
			fprintf(_GetLogFile(), "********************************************************************************\n");
		}
	}

	void Logger::LogInfo(const char* file, const char* func, int line, const char* arglist, ...)
	{
		if (VerboseLevel >= 2)
		{
			va_list argptr;
			va_start(argptr, arglist);
			_Log(stdout, "INFO", file, func, line, arglist, argptr);

			if(LogToFileMode == true)
			{ 
				_Log(_GetLogFile(), "INFO", file, func, line, arglist, argptr);
			}
			va_end(argptr);
		}
	}


	void Logger::LogDInfo(const char* file, const char* func, int line, const char* arglist, ...)
	{
		if (VerboseLevel >= 3)
		{
			va_list argptr;
			va_start(argptr, arglist);
			_Log(stdout, "INFO", file, func, line, arglist, argptr);

			if (LogToFileMode == true)
			{
				_Log(_GetLogFile(), "INFO", file, func, line, arglist, argptr);
			}
			va_end(argptr);
		}
	}

	void Logger::LogWarning(const char* file, const char* func, int line, const char* arglist, ...)
	{
		if (VerboseLevel >= 1)
		{
			va_list argptr;
			va_start(argptr, arglist);
			_Log(stdout, "WARNING", file, func, line, arglist, argptr);

			if (LogToFileMode == true)
			{
				_Log(_GetLogFile(), "WARNING", file, func, line, arglist, argptr);
			}
			va_end(argptr);
		}
	}
		
	void Logger::LogError(const char* file, const char* func, int line, const char* arglist, ...)
	{
		va_list argptr;
		va_start(argptr, arglist);
		_Log(stdout, "ERROR", file, func, line, arglist, argptr);

		if (LogToFileMode == true)
		{
			_Log(_GetLogFile(), "ERROR", file, func, line, arglist, argptr);
		}
		va_end(argptr);
	}

	void Logger::FinaliseLogFile()
	{
		if (_logFile != 0)
		{
			fclose(_logFile);
			_logFile = 0;
		}
	}

	/* Private Functions */
	void Logger::_Log(FILE* f, const char* tag, const char* file, const char* func, int line, const char* msg, va_list args)
	{
		//va_list ap;
		//va_start(ap, args);
		fprintf(f, "[%s] ", tag);
		if (VerboseLevel >= 3)
		{
			fprintf(f, "%s : %s line %d: ", file, func, line);
		}
		vfprintf(f, msg, args);
		vfprintf(f, "\n", NULL);
		//va_end(ap);
	}

	FILE* Logger::_GetLogFile()
	{
		if (_logFile == 0)
		{
			_logFile = fopen("logfile.log", "w");
		}

		return _logFile;
	}
}