#include "altimeter_dm.h"

namespace MagusEngine
{

	Altimeter_DataModel::Altimeter_DataModel()
	{
		_altitude.store(0.0f);
	}


	bool Altimeter_DataModel::Update(Byte* buffer)
	{
		float value;
		memcpy(&value, buffer, sizeof(float));
		_altitude.store(value);
		
		return true;
	}

}