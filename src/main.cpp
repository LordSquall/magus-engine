/* Local Project Includes */
#include "subsystems/systems/systemclass.h"
#include "subsystems/systems/windowsclass.h"

/* Program Entry Point */
int main()
{
	MagusEngine::SystemClass* system;
	bool result;
	
#ifdef _WIN32 || _WIN64
	system = new MagusEngine::WindowsClass();
#elif __linux__ || linux || __linux
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