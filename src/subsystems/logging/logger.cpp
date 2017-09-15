#include "logger.h"

namespace MagusEngine
{
	void Logger::LogWarning(const char* arglist, ...)
	{
		va_list ap;
		va_start(ap, arglist);
		vfprintf(stderr, arglist, ap);
		vfprintf(stderr, "\n", NULL);
		va_end(ap);
	}
		
	void Logger::LogError(const char* arglist, ...)
	{
		va_list ap;
		va_start(ap, arglist);
		vfprintf(stdout, arglist, ap);
		vfprintf(stderr, "\n", NULL);
		va_end(ap);
	}
}