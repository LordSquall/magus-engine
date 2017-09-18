#ifndef _DATAMODEL_H_
#define _DATAMODEL_H_

/* System includes */
#include <thread>
#include <atomic>

/* Libraries */
#pragma comment(lib, "ws2_32.lib")

/* Local Project Includes */
#include "../logging/logger.h"
#include "altimeter_dm.h"
#include "aircraft_computer.h"

/* Typedefs */
typedef char Byte;

namespace MagusEngine
{
	class DataModel
	{
	public:
		bool Initialise();

		float GetAltitude();

		float GetPitch();
		float GetYaw();
		float GetRoll();

		Altimeter_DataModel* GetAltitudeDM();
		AircraftComputer_DataModel* GetAircraftState();

	private:
		/* Data Models */
		Altimeter_DataModel _altimeter;
		AircraftComputer_DataModel _aircraftState;
	};
}
#endif