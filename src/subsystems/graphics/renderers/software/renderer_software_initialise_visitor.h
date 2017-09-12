#ifndef _RENDERER_SOFTWARE_INITIALISE_VISITOR_H_
#define _RENDERER_SOFTWARE_INITIALISE_VISITOR_H_

/* System Includes */

/* Local Project Includes */
#include "../../../scenemanagement/visitor.h"
#include "../../../math/vertex.h"
#include "../../../resources/resources.h"
#include "renderer_software.h"

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
		Renderer_Software_Initialise_Visitor(Renderer_Software* softwareRenderer);

		/* Visitor Functions */
		bool Initialise(Renderer_Interface* lowlevelRenderer, Resources* resources);

		void PreVisit(SceneNode* sceneNode);
		void Visit(SceneNode* sceneNode);
		void PostVisit(SceneNode* sceneNode);
		
		void PreVisit(Component* component);
		void Visit(Component* component);
		void PostVisit(Component* component);

		void PreVisit(Graphic2D* graphic2D);
		void Visit(Graphic2D* graphic2D);
		void PostVisit(Graphic2D* graphic2D);

		/* Getters */
		Renderer_Interface* GetLowLevelRenderer();

	private:
		Renderer_Interface* _lowLevelRenderer;
		Resources*			_resources;

		Renderer_Software* _softwareRenderer;
	};
}

#endif
