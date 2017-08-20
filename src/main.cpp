/* Local Project Includes */
#include "magusversion.h"
#include "subsystems/systems/systemclass.h"

#ifdef _WIN32
#include "subsystems/systems/windowsclass.h"
#else
#include "subsystems/systems/linuxclass.h"
#endif


/* Program Entry Point */
int main()
{
	MagusEngine::SystemClass* system;
	bool result;

	/* Print the verion number info the screeen */
	printf("Magus Engine - Version %d.%d\n", MagusEngine_VERSION_MAJOR, MagusEngine_VERSION_MINOR);
	printf("Operating System: %s\n", MagusEngine_OS_VERSION);


#ifdef _WIN32
	system = new MagusEngine::WindowsClass();
#else
	system = new MagusEngine::LinuxClass();
#endif

	if(!system)
	{
		return 0;
	}
	
	result = system->Initialise();
	if(result)
	{
		system->Run();
	}
	
	system->Shutdown();
	delete system;
	system = 0;
	
	return 0;
}