#ifndef _UA_PARSER_H_
#define _UA_PARSER_H_

/* System Includes */

/* Local Project Includes */
#include "UA.h"
#include "../scenemanagement/scenenode.h"
#include "../scenemanagement/component.h"
#include "../graphics/graphic2d.h"
#include "../graphics/primitives/rectangle.h"
#include "../graphics/primitives/line.h"
#include "../graphics/primitives/text.h"
#include "../external/tinydir/tinydir.h"
#include "../external/tinyxml2/tinyxml2.h"

namespace MagusEngine
{
	class UAParser
	{
	public:
		UAParser(Resources* resources);

		UA* Parse(const char* filename);

	private:

		SceneNode* ProcessSceneNode(tinyxml2::XMLElement* element);
		Component* ProcessSceneNodeComponent(tinyxml2::XMLElement* element);
		Graphic2D* ProcessSceneNodeComponentGraphics2D(tinyxml2::XMLElement* element);

	private:
		Resources*			_resources;
		Material*			_materialStack[64];
		unsigned int		_materialStackHead;
	};
}

#endif