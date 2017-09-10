#ifndef _RENDERER_SOFTWARE_INITIALISE_VISITOR_H_
#define _RENDERER_SOFTWARE_INITIALISE_VISITOR_H_

/* System Includes */

/* Local Project Includes */
#include "../../../scenemanagement/visitor.h"

namespace MagusEngine
{
	/*
	Name:  Renderer_Software_Initialise_Visitor
	Type: Class
	Purpose: Implements a initialisation visitor specific to the inbuild software renderer
	*/
	class Renderer_Software_Initialise_Visitor : public Visitor
	{
	public:
		/*
		Default contstructor
		*/
		Renderer_Software_Initialise_Visitor();

		/* Visitor Functions */
		bool Initialise(Renderer_Interface* lowlevelRenderer, Resources* resources);
		void Visit(SceneNode* sceneNode);
		void Visit(Component* component);
		void Visit(Graphic2D* graphic2D);

		/* Getters */
		Renderer_Interface* GetLowLevelRenderer();

	private:
		Renderer_Interface* _lowLevelRenderer;
		Resources*			_resources;
	};
}

#endif
