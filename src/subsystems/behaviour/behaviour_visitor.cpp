#include "behaviour_visitor.h"

#include "../scenemanagement/scenenode.h"
#include "../graphics/graphic2d.h"
#include "../graphics/primitives/text.h"

namespace MagusEngine
{
	BehaviourVisitor::BehaviourVisitor(DataModel* datamodel)
	{
		_dataModel = datamodel;

		initialPass = true;
	}

	/* Visitor Functions */
	bool BehaviourVisitor::Initialise(Renderer_Interface* lowlevelRenderer, Resources* resources, Camera* camera, Matrix4f* projection2D, Matrix4f* projection3D)
	{
		return true;
	}

	void BehaviourVisitor::PreVisit(SceneNode* sceneNode){}
	void BehaviourVisitor::Visit(SceneNode* sceneNode)
	{
		if (strcmp(sceneNode->GetName(), "horizon") == 0)
		{
			if (initialPass == true)
			{
				horizonBasePosition.x = sceneNode->GetPosition()->x;
				horizonBasePosition.y = sceneNode->GetPosition()->y;
				horizonBasePosition.z = sceneNode->GetPosition()->z;


				horizonBaseRotation.x = sceneNode->GetRotation()->x;
				horizonBaseRotation.y = sceneNode->GetRotation()->y;
				horizonBaseRotation.z = sceneNode->GetRotation()->z;
			}

			sceneNode->SetPosition(horizonBasePosition.x, horizonBasePosition.y + _dataModel->GetPitch(), horizonBasePosition.z);
		}

		if (strcmp(sceneNode->GetName(), "airspeed_value_lb") == 0)
		{
			/*Graphic2D* graphic = (Graphic2D*)sceneNode->GetComponent(0);
			Text* text = (Text*)graphic->GetDrawable();

			sprintf(text->GetContent(), "%.1f", _dataModel->GetAltitude());

			graphic->updateRequired = true;*/
		}

		if (strcmp(sceneNode->GetName(), "rosering_bg") == 0)
		{
			sceneNode->SetRotation(0.0f, 0.0f, sceneNode->GetRotation()->z + 1.0f);
		}
		if (strcmp(sceneNode->GetName(), "testcube") == 0)
		{
			//sceneNode->SetRotation(0.0f, 0.0f, sceneNode->GetRotation()->z + 1.0f);
		}
	}
	void BehaviourVisitor::PostVisit(SceneNode* sceneNode) {}

	void BehaviourVisitor::PreVisit(Component* component) {}
	void BehaviourVisitor::Visit(Component* component){}
	void BehaviourVisitor::PostVisit(Component* component) {}

	void BehaviourVisitor::PreVisit(Graphic2D* graphic2D) {}
	void BehaviourVisitor::Visit(Graphic2D* graphic2D){}
	void BehaviourVisitor::PostVisit(Graphic2D* graphic2D) {}

	void BehaviourVisitor::PreVisit(Rectangle* rectangle) {}
	void BehaviourVisitor::Visit(Rectangle* rectangle) {}
	void BehaviourVisitor::PostVisit(Rectangle* rectangle) {}

	void BehaviourVisitor::PreVisit(Line* line) {}
	void BehaviourVisitor::Visit(Line* line) {}
	void BehaviourVisitor::PostVisit(Line* line) {}

	void BehaviourVisitor::PreVisit(Text* text) {}
	void BehaviourVisitor::Visit(Text* text) {}
	void BehaviourVisitor::PostVisit(Text* text) {}

	void BehaviourVisitor::PreVisit(Ellipse* ellipse) {}
	void BehaviourVisitor::Visit(Ellipse* ellipse) {}
	void BehaviourVisitor::PostVisit(Ellipse* ellipse) {}

	void BehaviourVisitor::PreVisit(Path* path) {}
	void BehaviourVisitor::Visit(Path* path) {}
	void BehaviourVisitor::PostVisit(Path* path) {}

	void BehaviourVisitor::PreVisit(Graphic3D* graphic3d) {}
	void BehaviourVisitor::Visit(Graphic3D* graphic3d) {}
	void BehaviourVisitor::PostVisit(Graphic3D* graphic3d) {}

	void BehaviourVisitor::PreVisit(Model* model) {}
	void BehaviourVisitor::Visit(Model* model) {}
	void BehaviourVisitor::PostVisit(Model* model) {}
}