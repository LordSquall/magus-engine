/* includes */
#include "subsystems/systems/systemclass.h"
#include "subsystems/systems/windowsclass.h"

int main()
{
	ElementaEngine::SystemClass* system;
	bool result;
	
	
	system = new ElementaEngine::WindowsClass();
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