/* includes */
#include "subsystems/systems/systemclass.h"
#include "subsystems/systems/windowsclass.h"

int main()
{
	MagusEngine::SystemClass* system;
	bool result;
	
	
	system = new MagusEngine::WindowsClass();
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