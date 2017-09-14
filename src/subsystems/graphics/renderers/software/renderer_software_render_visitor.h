#ifndef _RENDERER_SOFTWARE_RENDER_VISITOR_H_
#define _RENDERER_SOFTWARE_RENDER_VISITOR_H_

/* System Includes */

/* Local Project Includes */
#include "../../../scenemanagement/visitor.h"
#include "../../../math/matrix.h"

namespace MagusEngine
{
	/*
	Name:  Renderer_Software_Render_Visitor
	Type: Class
	Purpose: Implements a render visitor specific  to the inbuild software rendere
	*/
	class Renderer_Software_Render_Visitor : public Visitor
	{
	public:
		/*
		Default contstructor
		*/
		Renderer_Software_Render_Visitor();

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

		void PreVisit(Rectangle* rectangle);
		void Visit(Rectangle* rectangle);
		void PostVisit(Rectangle* rectangle);

		void PreVisit(Line* line);
		void Visit(Line* line);
		void PostVisit(Line* line);

		void PreVisit(Text* text);
		void Visit(Text* text);
		void PostVisit(Text* text);

		void PreVisit(Ellipse* ellipse);
		void Visit(Ellipse* ellipse);
		void PostVisit(Ellipse* ellipse);

		void PreVisit(Path* path);
		void Visit(Path* path);
		void PostVisit(Path* path);

		/* Getters */
		Renderer_Interface* GetLowLevelRenderer();

	private:
		Renderer_Interface* _lowLevelRenderer;
		Resources*			_resources;

		Matrix4f			_matrixStack[64];
		unsigned int		_matrixStackHead;

		bool				_renderCritical;

		Texture*			_cachedTexture;
	};
}

#endif
