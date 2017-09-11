#ifndef _RENDERER_WINDOWS_RENDER_VISITOR_H_
#define _RENDERER_WINDOWS_RENDER_VISITOR_H_

/* System Includes */

/* Local Project Includes */
#include "../../../scenemanagement/visitor.h"
#include "../../../math/matrix.h"

namespace MagusEngine
{
	/*
	Name:  Renderer_Windows_Render_Visitor
	Type: Class
	Purpose: Implements a render visitor specific to windows to create opengl content on the gpu
	*/
	class Renderer_Windows_Render_Visitor : public Visitor
	{
	public:
		/*
		Default contstructor
		*/
		Renderer_Windows_Render_Visitor();

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

		Matrix4f			_matrixStack[64];
		unsigned int		_matrixStackHead;
	};
}

#endif
