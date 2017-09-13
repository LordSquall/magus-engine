/* System Includes */
#include <stdio.h>
#include <cstring>

/* Local Project Includes */
#include "magusversion.h"
#include "framework.h"

char configLocation[255];

int ProcessArguments(int argc, char *argv[]);

void DisplayVersionInfo();

void DisplayUsage();


/* Program Entry Point */
int main(int argc, char *argv[])
{
	/* Local variables */
	bool running = true;		/* termination flag */
	unsigned int result = 0;	/* process arguments result */

	/* Process arguments */
	result = ProcessArguments(argc, argv);
	if (result < 0)
	{
		/* Failure to process args, display program usage */
		DisplayUsage();
		return 0;
	}
	else if (result > 0)
	{
		/* No error, but args configuration means we terminate the application */
		return 0;
	}

	/* Create Framework */
	MagusEngine::Framework* framework = new MagusEngine::Framework();

	/* Initialise the framework */
	if (framework->Initialise(configLocation))
	{
		while (running == true)
		{
			/* Update framework timings */
			running = framework->Frame();
		}
	}
	else
	{
		printf("Unable to initialise framework\n");
	}

	framework->Shutdown();
	return 0;
}

int ProcessArguments(int argc, char *argv[])
{
	/* Flow variables */
	int i = 0;
	int result = -1;

	/* Process Arguments */
	for (i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-v") == 0)
		{
			DisplayVersionInfo();
			return 1;
		}
		else if (strcmp(argv[i], "-h") == 0)
		{
			DisplayUsage();
			return 1;
		}
		else if (strcmp(argv[i], "-i") == 0)
		{
			/* Make sure there is enought args to continue */
			if (i+1 == argc)
			{
				printf("Unable to process '-i' file\n");
				return -1;
			}

			/* Copy arg to directory variable */
			strcpy_s(configLocation, argv[i + 1]);
			i++;

			/* Mark result */
			result = 0;
		}
	}

	return result;
}

void DisplayVersionInfo()
{
	/* Print version information to screen */
	printf("Magus Engine - Version %d.%d\n", MagusEngine_VERSION_MAJOR, MagusEngine_VERSION_MINOR);
}

void DisplayUsage()
{
	printf("Usage:\n");
	printf("\t-h\t\t:Show usage page\n");
	printf("\t-v\t\t:Show version info\n");
	printf("\t-i <path>\t\t:Engine configuration .conf file (Required)\n");
}