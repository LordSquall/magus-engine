/* Local Project Includes */
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