#ifndef _RENDERER_SOFTWARE_RENDER_VISITOR_H_
#define _RENDERER_SOFTWARE_RENDER_VISITOR_H_

/* System Includes */

/* Local Project Includes */
#include "../../camera.h"
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
		bool Initialise(Renderer_Interface* lowlevelRenderer, Resources* resources, Camera* camera, Matrix4f* projection2D, Matrix4f* projection3D);
		
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

		void PreVisit(Graphic3D* graphic3d);
		void Visit(Graphic3D* graphic3d);
		void PostVisit(Graphic3D* graphic3d);

		void PreVisit(Model* model);
		void Visit(Model* model);
		void PostVisit(Model* model);

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

		Matrix4f*			_2DProjection;
		Matrix4f*			_3DProjection;

		Texture*			_cachedTexture;
	};
}

#endif
