#ifndef _ALTIMETER_DM_H_
#define _ALTIMETER_DM_H_

/* System Includes */
#include <atomic>
#include <thread>

/* Typedefs */
typedef char Byte;

namespace MagusEngine
{
	class Altimeter_DataModel
	{
	public:
		Altimeter_DataModel();

		bool Update(Byte* buffer);

	public:
		std::atomic<float> _altitude;
	};
}
#endif