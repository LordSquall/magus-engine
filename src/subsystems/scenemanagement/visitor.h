#ifndef _VISITOR_H_
#define _VISITOR_H_

/* System Includes */
#include <stdio.h>

/* Local Project Includes */
#include "../graphics/renderers/renderer_interface.h"
#include "../resources/resources.h"

namespace MagusEngine
{
	class SceneNode;
	class Component;
	class Graphic2D;
	class Graphic3D;
	class Rectangle;
	class Line;
	class Text;
	class Ellipse;
	class Path;
	class Model;
	class Camera;
	
	class Visitor
	{
	public:
		virtual bool Initialise(Renderer_Interface* lowlevelRenderer, Resources* resources, Camera* camera, Matrix4f* projection2D, Matrix4f* projection3D) = 0;

		virtual void PreVisit(SceneNode* sceneNode) = 0;
		virtual void Visit(SceneNode* sceneNode) = 0;
		virtual void PostVisit(SceneNode* sceneNode) = 0;

		virtual void PreVisit(Component* component) = 0;
		virtual void Visit(Component* component) = 0;
		virtual void PostVisit(Component* component) = 0;

		virtual void PreVisit(Graphic2D* graphic2d) = 0;
		virtual void Visit(Graphic2D* graphic2d) = 0;
		virtual void PostVisit(Graphic2D* graphic2d) = 0;

		virtual void PreVisit(Rectangle* rectangle) = 0;
		virtual void Visit(Rectangle* rectangle) = 0;
		virtual void PostVisit(Rectangle* rectangle) = 0;

		virtual void PreVisit(Line* line) = 0;
		virtual void Visit(Line* line) = 0;
		virtual void PostVisit(Line* line) = 0;

		virtual void PreVisit(Text* text) = 0;
		virtual void Visit(Text* text) = 0;
		virtual void PostVisit(Text* text) = 0;

		virtual void PreVisit(Ellipse* ellipse) = 0;
		virtual void Visit(Ellipse* ellipse) = 0;
		virtual void PostVisit(Ellipse* ellipse) = 0;

		virtual void PreVisit(Path* path) = 0;
		virtual void Visit(Path* path) = 0;
		virtual void PostVisit(Path* path) = 0;

		virtual void PreVisit(Graphic3D* graphic3d) = 0;
		virtual void Visit(Graphic3D* graphic3d) = 0;
		virtual void PostVisit(Graphic3D* graphic3d) = 0;

		virtual void PreVisit(Model* model) = 0;
		virtual void Visit(Model* model) = 0;
		virtual void PostVisit(Model* model) = 0;

	};
}

#endif