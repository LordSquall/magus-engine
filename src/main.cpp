/* System Includes */
#include <stdio.h>

/* Local Project Includes */
#include "magusversion.h"
#include "framework.h"

#include "subsystems/os/os_interface.h"

#ifdef _WIN32
#include "subsystems/os/os_windows.h"
#else
#include "subsystems/os/os_linux.h"
#endif

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

//	MagusEngine::OS_Interface* os;
//	bool result;
//
//	/* Print the verion number info the screeen */
//	printf("Magus Engine - Version %d.%d\n", MagusEngine_VERSION_MAJOR, MagusEngine_VERSION_MINOR);
//	printf("Operating System: %s\n", MagusEngine_OS_VERSION);
//
//
//#ifdef _WIN32
//	os = new MagusEngine::OS_Windows();
//#else
//	system = new MagusEngine::LinuxClass();
//#endif
//
//	if(!system)
//	{
//		return 0;
//	}
//	
//	/* Initialise the system */
//	result = os->Initialise();
//	if(result)
//	{
//		/* Enter the main game loop */
//		os->Run();
//	}
//	
//	/* Shutdown and clean up any allocated objects and memory */
//	os->Shutdown();
//	delete os;
//	os = 0;
	
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