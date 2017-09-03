#include "scenenode.h"

namespace MagusEngine
{
	SceneNode::SceneNode()
	{
	
	}
	
	bool SceneNode::Initialise()
	{
		return true;
	}

	void SceneNode::Render(Renderer_Interface* renderer)
	{

	}

	void SceneNode::Shutdown()
	{
	}

	void SceneNode::AddChild(SceneNode* sceneNode)
	{
		m_children.push_back(sceneNode);
	}
}