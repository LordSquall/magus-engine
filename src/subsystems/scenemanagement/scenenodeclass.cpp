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
		renderer->CheckError();
		renderer->DrawRectangle(0, 0, 50, 50);
		renderer->CheckError();
	}

	void SceneNodeClass::Shutdown()
	{
	}

	void SceneNodeClass::AddChild(SceneNodeClass* sceneNode)
	{
		m_children.push_back(sceneNode);
	}
}