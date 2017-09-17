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

		Vertex				_vertexBuildBuffer[1000];
		unsigned int		_indicesBuildBuffer[4000];

		bool				_renderCritical;

		Texture*			_cachedTexture;
	};
}

#endif
