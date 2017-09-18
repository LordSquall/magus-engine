/* System Includes */
#include <stdio.h>
#include <cstring>

/* Local Project Includes */
#include "magusversion.h"
#include "framework.h"
#include "subsystems/logging/logger.h"

/* Global variables */
char	g_configLocation[255];		/* Configuration file location */

/* Main support functions - Forward Declarations */
int		MAIN_ProcessArguments(int argc, char *argv[]);
void	MAIN_DisplayVersionInfo();
void	MAIN_DisplayUsage();


/* Program Entry Point */
int main(int argc, char *argv[])
{
	/* Local variables */
	bool running = true;		/* termination flag */
	unsigned int result = 0;	/* process arguments result */

	/* Process arguments */
	result = MAIN_ProcessArguments(argc, argv);
	if (result < 0)
	{
		/* Failure to process args, display program usage */
		MAIN_DisplayUsage();
		return 0;
	}
	else if (result > 0)
	{
		/* No error, but args configuration means we terminate the application */
		MAIN_DisplayUsage();
		return 0;
	}

	/* Create Framework */
	MagusEngine::Framework* framework = new MagusEngine::Framework();

	/* Initialise the framework */
	if (framework->Initialise(g_configLocation))
	{
		while (running == true)
		{
			/* Update framework timings */
			running = framework->Frame();
			
			//running = false;
		}
	}
	else
	{
		LOGERROR("Unabled to Initialise Framework");
	}

	framework->Shutdown();
	
	/* close logger log file */
	MagusEngine::Logger::FinaliseLogFile();

	return 0;
}

int MAIN_ProcessArguments(int argc, char *argv[])
{
	/* Flow variables */
	int i = 0;
	int result = -1;

	/* Process Arguments */
	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-version") == 0)
		{
			MAIN_DisplayVersionInfo();
			return 1;
		}
		else if (strcmp(argv[i], "-h") == 0)
		{
			MAIN_DisplayUsage();
			return 1;
		}
		if (strcmp(argv[i], "-v") == 0)
		{
			if (i + 1 == argc)
			{
				LOGERROR("Unable to process '-v' level");
				return -1;
			}
			MagusEngine::Logger::VerboseLevel = atoi(argv[i+1]);
			i++;
		}
		if (strcmp(argv[i], "-f") == 0)
		{
			MagusEngine::Logger::LogToFileMode = true;
		}
		else if (strcmp(argv[i], "-i") == 0)
		{
			/* Make sure there is enought args to continue */
			if (i+1 == argc)
			{
				LOGERROR("Unable to process '-i' file");
				return -1;
			}

			/* Copy arg to directory variable */
			strcpy(g_configLocation, argv[i + 1]);
			i++;

			/* Mark result */
			result = 0;
		}
	}

	return result;
}

void MAIN_DisplayVersionInfo()
{
	/* Print version information to screen */
	printf("Magus Engine - Version %d.%d\n", MagusEngine_VERSION_MAJOR, MagusEngine_VERSION_MINOR);
}

void MAIN_DisplayUsage()
{
	printf("Usage:\n");
	printf("\t-h\t\t:Show usage page\n");
	printf("\t-version\t\t:Show version info\n");
	printf("\t-v\t\t:Switch on verbose level\n");
	printf("\t\t\t\t: 0 - Errors\n");
	printf("\t\t\t\t: 1 - Errors + Warnings\n");
	printf("\t\t\t\t: 2 - Errors + Warning + Info\n");
	printf("\t\t\t\t: 3 - Same as Level 2 but includes function and line numbers\n");
	printf("\t\t\t\t: 4 - Same as Level 3 but include memory allocation (a lot of information)\n");
	printf("\t-f\t\t:Switch on log to file (logfile.log)\n");
	printf("\t-i <path>\t\t:Engine configuration .conf file (Required)\n");
}