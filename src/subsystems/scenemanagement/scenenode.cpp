#include "scenenode.h"

#include "../graphics/visitor.h"

namespace MagusEngine
{
	Transform::Transform()
	{
		position.SetX(0.0f);
		position.SetY(0.0f);
		position.SetZ(0.0f);

		rotation.SetX(0.0f);
		rotation.SetY(0.0f);
		rotation.SetZ(0.0f);
				
		scale.SetX(1.0f);
		scale.SetY(1.0f);
		scale.SetZ(1.0f);
	}

	SceneNode::SceneNode()
	{
		_tranform = Transform();
	}
	
	bool SceneNode::Initialise(const char* name)
	{
		strcpy_s(_name, name);
		return true;
	}

	void SceneNode::Shutdown()
	{
	}

	void SceneNode::AddChild(SceneNode* sceneNode)
	{
		_children.push_back(sceneNode);
	}

	
	void SceneNode::Accept(Visitor* visitor)
	{
		for(std::vector<SceneNode*>::iterator it = _children.begin(); it != _children.end(); ++it)
		{
			visitor->Visit((SceneNode*)*it);
		}

		visitor->Visit(this);
	}

	char* SceneNode::GetName()
	{
		return _name;
	}


	void SceneNode::SetPosition(Vector3f position)	{ _tranform.position = position; }
	void SceneNode::SetRotation(Vector3f rotation)	{ _tranform.rotation = rotation; }
	void SceneNode::SetScale(Vector3f scale)		{ _tranform.scale = scale; }

	void SceneNode::SetPosition(float x, float y, float z) { 
		_tranform.position.SetX(x);
		_tranform.position.SetY(y); 
		_tranform.position.SetZ(z); 
	}

	void SceneNode::SetRotation(float x, float y, float z) { 
		_tranform.rotation.SetX(x);
		_tranform.rotation.SetY(y); 
		_tranform.rotation.SetZ(z); 
	}

	void SceneNode::SetScale(float x, float y, float z) { 
		_tranform.scale.SetX(x);
		_tranform.scale.SetY(y); 
		_tranform.scale.SetZ(z); 
	}
}