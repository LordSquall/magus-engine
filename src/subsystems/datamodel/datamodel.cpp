#include "datamodel.h"

namespace MagusEngine
{
	bool DataModel::Initialise()
	{
		return true;
	}

	Altimeter_DataModel* DataModel::GetAltitudeDM()
	{
		return &_altimeter;
	}

	AircraftComputer_DataModel* DataModel::GetAircraftState()
	{
		return &_aircraftState;
	}


	float DataModel::GetAltitude()
	{
		return _altimeter._altitude;
	}


	float DataModel::GetPitch()
	{
		return _aircraftState._pitch;
	}
	
	float DataModel::GetYaw()
	{
		return _aircraftState._yaw;
	}
	
	float DataModel::GetRoll()
	{
		return _aircraftState._roll;
	}
}