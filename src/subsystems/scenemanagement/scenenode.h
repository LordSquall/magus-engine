#ifndef _SCENE_NODE_CLASS_H_
#define _SCENE_NODE_CLASS_H_

#include "../graphics/rendererclass.h"

#include <vector>

namespace MagusEngine
{
	class SceneNodeClass
	{
	public:
		SceneNodeClass();
		
		bool Initialise();

		void Render(RendererClass* renderer);

		void Shutdown();

		void AddChild(SceneNodeClass* sceneNode);

	public:
		std::vector<SceneNodeClass*> m_children;

	};
}

#endif