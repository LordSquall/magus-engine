#ifndef _BEHAVIOUR_VISITOR_H_
#define _BEHAVIOUR_VISITOR_H_

/* System Includes */

/* Local Project Includes */
#include "../datamodel/datamodel.h"
#include "../scenemanagement/visitor.h"

namespace MagusEngine
{
	/*
	Name:  Behaviour Visitor
	Type: Class
	Purpose: Implements a visitor responisble for update the scene based on external inputs
	*/
	class BehaviourVisitor : public Visitor
	{
	public:
		/*
		Default contstructor
		*/
		BehaviourVisitor(DataModel* dataModel);

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

		bool initialPass;

	private:
		DataModel*	_dataModel;

		Vector3f horizonBasePosition; 
		Vector3f horizonBaseRotation;

	};
}

#endif
