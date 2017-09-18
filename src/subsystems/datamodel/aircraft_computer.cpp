#include "aircraft_computer.h"

namespace MagusEngine
{

	AircraftComputer_DataModel::AircraftComputer_DataModel()
	{
		_pitch.store(0.0f);
		_yaw.store(0.0f);
		_roll.store(0.0f);
	}


	bool AircraftComputer_DataModel::Update(Byte* buffer)
	{
		float value;
		memcpy(&value, buffer, sizeof(float));
		_pitch.store(value);

		memcpy(&value, buffer, sizeof(float));
		_yaw.store(value);

		memcpy(&value, buffer, sizeof(float));
		_roll.store(value);

		return true;
	}

}