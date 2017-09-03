/* System Includes */
#include <stdio.h>

/* Local Project Includes */
#include "magusversion.h"
#include "framework.h"

unsigned int ProcessArguments(int argc, char *argv[]);

void DisplayVersionInfo();

void DisplayUsage();

/* Program Entry Point */
void main(int argc, char *argv[])
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
		return;
	}
	else if (result > 0)
	{
		/* No error, but args configuration means we terminate the application */
		return;
	}

	/* Create Framework */
	MagusEngine::Framework* framework = new MagusEngine::Framework();

	/* Initialise the framework */
	framework->Initialise();

	while (running == true)
	{
		/* Update framework timings */
		running = framework->Frame();
	}

	framework->Shutdown();
	return;
}

unsigned int ProcessArguments(int argc, char *argv[])
{
	/* Flow variables */
	int i = 0;

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
	}

	return 0;
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
}