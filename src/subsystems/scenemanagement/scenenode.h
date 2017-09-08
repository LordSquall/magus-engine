#ifndef _SCENE_NODE_H_
#define _SCENE_NODE_H_

#include "../math/vector.h"

#include <vector>

namespace MagusEngine
{
	class Visitor;

	class Transform{
	public:
		Vector3f position;
		Vector3f rotation;
		Vector3f scale;
	
		Transform();
	};

	class SceneNode
	{
	public:
		SceneNode();
		
		bool Initialise(const char* name);


		void Shutdown();

		void AddChild(SceneNode* sceneNode);

		char* GetName();

		void SetPosition(Vector3f position);
		void SetRotation(Vector3f position);
		void SetScale(Vector3f position);

		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);

		void Accept(Visitor* visitor);

	public:
		char _name[25];

		Transform _tranform;
		std::vector<SceneNode*> _children;

	};
}

#endif