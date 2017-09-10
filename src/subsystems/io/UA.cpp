#include "UA.h"

namespace MagusEngine
{
	UA::UA()
	{
	}

	bool UA::Initialise(const char* name)
	{
		/* Copy the name */
		strcpy_s(_name, name);

		return true;
	}

	/** Getters **/
	char* UA::GetName() { return _name; }
	SceneNode* UA::GetRootNode() { return _root; }

	/** Setters **/
	void UA::SetRootNode(SceneNode* node) { _root = node; }

}