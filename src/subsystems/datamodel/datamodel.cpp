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

	float DataModel::GetAltitude()
	{
		return _altimeter._altitude;
	}
}