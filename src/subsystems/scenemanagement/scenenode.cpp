#include "scenenodeclass.h"

namespace MagusEngine
{
	SceneNodeClass::SceneNodeClass()
	{
	
	}
	
	bool SceneNodeClass::Initialise()
	{
		return true;
	}

	void SceneNodeClass::Render(RendererClass* renderer)
	{

	}

	void SceneNodeClass::Shutdown()
	{
	}

	void SceneNodeClass::AddChild(SceneNodeClass* sceneNode)
	{
		m_children.push_back(sceneNode);
	}
}