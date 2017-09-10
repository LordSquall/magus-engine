#ifndef _UA_PARSER_H_
#define _UA_PARSER_H_

/* System Includes */

/* Local Project Includes */
#include "UA.h"
#include "../scenemanagement/scenenode.h"
#include "../scenemanagement/component.h"
#include "../graphics/graphic2d.h"
#include "../graphics/primitives/rectangle.h"
#include "../external/tinydir/tinydir.h"
#include "../external/tinyxml2/tinyxml2.h"

namespace MagusEngine
{
	class UAParser
	{
	public:
		static UA* ParserUAFile(const char* filename);

		static SceneNode* ProcessSceneNode(tinyxml2::XMLElement* element);
		
		static Component* ProcessSceneNodeComponent(tinyxml2::XMLElement* element);

		static Graphic2D* ProcessSceneNodeComponentGraphics2D(tinyxml2::XMLElement* element);
	};
}

#endif