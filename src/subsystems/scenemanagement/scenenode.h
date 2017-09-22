#ifndef _SCENE_NODE_H_
#define _SCENE_NODE_H_

#include "../math/vector.h"
#include "visitable.h"
#include "component.h"
#include <vector>
#include <malloc.h>

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

	class SceneNode : public Visitable
	{
	public:
		SceneNode();
		
		bool Initialise(const char* name, int maxChildren);

		bool InitialiseComponents(int maxComponent);

		void Shutdown();

		void AddChild(SceneNode* sceneNode);

		void AddComponent(Component* component);

		Component* GetComponent(int index);

		char* GetName();

		void SetPosition(Vector3f position);
		void SetRotation(Vector3f position);
		void SetScale(Vector3f position);

		void SetPosition(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);

		Vector3f* GetPosition();
		Vector3f* GetRotation();
		Vector3f* GetScale();


		void SetCriticality(bool critical);
		bool IsCritical();


		void SetIsFilter(bool isFilter);
		bool IsFilter();

		void SetMaterial(Material* material);
		Material* GetMaterial();

		void Accept(Visitor* visitor);

	public:
		char _name[50];

		bool	_isCritical;
		bool	_isFilter;

		Transform _tranform;
		SceneNode** _children;
		unsigned int _maxChildCount;
		unsigned int _childCount;

		Component** _components;
		unsigned int _maxComponentCount;
		unsigned int _componentCount;

		Material _material;
	};
}

#endif