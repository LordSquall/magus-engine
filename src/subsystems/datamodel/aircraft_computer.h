#ifndef _AIRCRAFT_COMPUTER_H_
#define _AIRCRAFT_COMPUTER_H_

/* System Includes */
#include <string.h>
#include <atomic>
#include <thread>

/* Typedefs */
typedef char Byte;

namespace MagusEngine
{
	class AircraftComputer_DataModel
	{
	public:
		AircraftComputer_DataModel();

		bool Update(Byte* buffer);

	public:
		float _pitch;
		float _yaw;
		float _roll;
	};
}
#endif