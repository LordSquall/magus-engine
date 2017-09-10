#ifndef _UA_H_
#define _UA_H_

/* System Includes */

/* Local Project Includes */
#include "../scenemanagement/scenenode.h"

namespace MagusEngine
{
	/*
		Name: UA
		Type: Class
		Purpose: Respresents the server side elements of the User Application
	*/
	class UA
	{
	public:
		/*
		*	Default Constructor
		*/
		UA();

		/*
		*	Initialise the UA with a human readable name
		*	args:
		*		name - UA name
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
		/* Human readable UA name */
		char _name[50];

		/* Root node of the graphical scene */
		SceneNode* _root;
	};
}

#endif