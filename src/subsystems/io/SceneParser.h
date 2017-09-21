#ifndef _SCENE_PARSER_H_
#define _SCENE_PARSER_H_

/* System Includes */

/* Local Project Includes */
#include "../scenemanagement/scene.h"
#include "../scenemanagement/scenenode.h"
#include "../scenemanagement/component.h"
#include "../graphics/graphic2d.h"
#include "../graphics/graphic3d.h"
#include "../graphics/primitives/rectangle.h"
#include "../graphics/primitives/line.h"
#include "../graphics/primitives/text.h"
#include "../graphics/primitives/ellipse.h"
#include "../graphics/primitives/path.h"
#include "../graphics/primitives/model.h"
#include "../external/tinydir/tinydir.h"
#include "../external/tinyxml2/tinyxml2.h"

namespace MagusEngine
{
	class SceneParser
	{
	public:
		SceneParser(Resources* resources);

		Scene* Parse(const char* filename);

	private:

		SceneNode* ProcessSceneNode(tinyxml2::XMLElement* element);
		Component* ProcessSceneNodeComponent(tinyxml2::XMLElement* element);
		Graphic2D* ProcessSceneNodeComponentGraphics2D(tinyxml2::XMLElement* element);
		Graphic3D* ProcessSceneNodeComponentGraphics3D(tinyxml2::XMLElement* element);

	private:
		Resources*			_resources;
		Material*			_materialStack[64];
		unsigned int		_materialStackHead;

		bool				_criticallityStack[64];
		unsigned int		_criticallityStackHead;
	};
}

#endif