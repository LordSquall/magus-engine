#include "Scene.h"

namespace MagusEngine
{
	Scene::Scene()
	{
	}

	bool Scene::Initialise(const char* name)
	{
		/* Copy the name */
		strcpy_s(_name, name);

		return true;
	}

	/** Getters **/
	char* Scene::GetName() { return _name; }
	SceneNode* Scene::GetRootNode() { return _root; }

	/** Setters **/
	void Scene::SetRootNode(SceneNode* node) { _root = node; }

}