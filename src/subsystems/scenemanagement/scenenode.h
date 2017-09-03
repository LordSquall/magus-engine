#ifndef _SCENE_NODE_H_
#define _SCENE_NODE_H_

#include "../graphics/renderer_interface.h"

#include <vector>

namespace MagusEngine
{
	class SceneNode
	{
	public:
		SceneNode();
		
		bool Initialise();

		void Render(Renderer_Interface* renderer);

		void Shutdown();

		void AddChild(SceneNode* sceneNode);

	public:
		std::vector<SceneNode*> m_children;

	};
}

#endif