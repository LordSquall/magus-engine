#ifndef _LOGGER_H_
#define _LOGGER_H_

/* System Includes */
#include <stdio.h>
#include <stdarg.h>

namespace MagusEngine
{
	class Logger
	{
	public:
		static void LogWarning(const char* args, ...);
		
		static void LogError(const char* args, ...);
	};
}

#endif