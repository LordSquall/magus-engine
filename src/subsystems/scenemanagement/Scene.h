#ifndef _SCENE_H_
#define _SCENE_H_

/* System Includes */

/* Local Project Includes */
#include "../scenemanagement/scenenode.h"

namespace MagusEngine
{
	/*
		Name: Scene
		Type: Class
		Purpose: Respresents the server side elements of the User Application
	*/
	class Scene
	{
	public:
		/*
		*	Default Constructor
		*/
		Scene();

		/*
		*	Initialise the Scene with a human readable name
		*	args:
		*		name - Scene name
		*	returns:
		*		initialisation success
		*/
		bool Initialise(const char* name);


		/** Getters **/
		char*		GetName();
		SceneNode*	GetRootNode();
		
		/** Setters **/
		void		SetRootNode(SceneNode* node);

	private:
		/* Human readable Scene name */
		char _name[50];

		/* Root node of the graphical scene */
		SceneNode* _root;
	};
}

#endif