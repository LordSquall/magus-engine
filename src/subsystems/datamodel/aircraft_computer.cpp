#include "aircraft_computer.h"

namespace MagusEngine
{

	AircraftComputer_DataModel::AircraftComputer_DataModel()
	{
		_pitch = 0.0f;
		_yaw = 0.0f;
		_roll = 0.0f;
	}


	bool AircraftComputer_DataModel::Update(Byte* buffer)
	{
		float value;
		memcpy(&value, buffer, sizeof(float));
		_pitch = value;

		printf("pitch: %.3f\n", _pitch);
		//memcpy(&value, buffer, sizeof(float));
		//_pitch = value;

		//memcpy(&value, buffer, sizeof(float));
		//_pitch = value;

		return true;
	}

}