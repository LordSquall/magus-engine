#include "UAParser.h"

namespace MagusEngine
{
	UA* UAParser::ParserUAFile(const char* filename)
	{
		UA* newUA = new UA();

		tinyxml2::XMLDocument doc;
		doc.LoadFile(filename);

		/* Get engine element */
		tinyxml2::XMLElement* uaElement = doc.FirstChildElement("UA");

		/* Check to make sure the root tag is UA */
		if (uaElement != NULL)
		{
			/* UA Title */
			newUA->Initialise(uaElement->Attribute("title"));

			/* Set scene element */
			tinyxml2::XMLElement* sceneElement = uaElement->FirstChildElement("scene");

			/* Check to make sure the scene element is present */
			if (sceneElement != NULL)
			{
				/* Set root element of the scene */
				tinyxml2::XMLElement* rootElement = sceneElement->FirstChildElement("node");

				newUA->SetRootNode(ProcessSceneNode(rootElement));
			}
		}

		return newUA;
	}

	SceneNode* UAParser::ProcessSceneNode(tinyxml2::XMLElement* element)
	{
		/* Create a new scene node */
		SceneNode* newNode = new SceneNode();


		/* Get the children count */
		int childrenCount = element->IntAttribute("children");

		/* Initialise the node name */
		newNode->Initialise(element->Attribute("name"), childrenCount);

		if (childrenCount > 0)
		{
			for (tinyxml2::XMLElement* e = element->FirstChildElement("node"); e != NULL; e = e->NextSiblingElement("node"))
			{
				newNode->AddChild(ProcessSceneNode(e));
			}
		}

		/* Check for transform information */
		tinyxml2::XMLElement* transformElement = element->FirstChildElement("transform");

		if (transformElement != NULL)
		{
			/* Check for position information */
			tinyxml2::XMLElement* positionElement = transformElement->FirstChildElement("position");

			if (positionElement != NULL)
			{
				newNode->SetPosition(positionElement->FloatAttribute("x"), positionElement->FloatAttribute("y"), positionElement->FloatAttribute("z"));
			}

			/* Check for rotation information */
			tinyxml2::XMLElement* rotationElement = transformElement->FirstChildElement("rotation");

			if (rotationElement != NULL)
			{
				newNode->SetPosition(rotationElement->FloatAttribute("x"), rotationElement->FloatAttribute("y"), rotationElement->FloatAttribute("z"));
			}

			/* Check for scale information */
			tinyxml2::XMLElement* scaleElement = transformElement->FirstChildElement("scale");

			if (scaleElement != NULL)
			{
				newNode->SetPosition(scaleElement->FloatAttribute("x"), scaleElement->FloatAttribute("y"), scaleElement->FloatAttribute("z"));
			}
		}

		/* Check for component information */
		tinyxml2::XMLElement* componentElement = element->FirstChildElement("components");

		if (componentElement != NULL)
		{
			/* Get the component count */
			int componentCount = componentElement->IntAttribute("count");

			if (componentCount > 0)
			{
				/* Initialise memory in scene node for components */
				newNode->InitialiseComponents(componentCount);

				/* Process each of the component tags in turn */
				for (tinyxml2::XMLElement* e = componentElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
				{
					newNode->AddComponent(ProcessSceneNodeComponent(e));
				}
			}
		}

		return newNode;
	}


	Component* UAParser::ProcessSceneNodeComponent(tinyxml2::XMLElement* element)
	{
		/* Check to determine the type of the component */
		if (strcmp(element->Name(), "graphics2d") == 0)
		{
			return ProcessSceneNodeComponentGraphics2D(element);
		}
		
		return NULL;
	}

	Graphic2D* UAParser::ProcessSceneNodeComponentGraphics2D(tinyxml2::XMLElement* element)
	{
		/* Create component as a 2d graphic */
		Graphic2D* newGraphics2DComponent = new Graphic2D();

		/* Process each of the children tags in turn */
		for (tinyxml2::XMLElement* e = element->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			/* Check to determine the type of the drawable */
			if (strcmp(e->Name(), "rectangle") == 0)
			{
				float x = e->FloatAttribute("x");
				float y = e->FloatAttribute("y");
				float width = e->FloatAttribute("width");
				float height = e->FloatAttribute("height");
				newGraphics2DComponent->GetDrawable();
				Rectangle* newDrawable = new Rectangle();
				newGraphics2DComponent->SetDrawable(newDrawable);
			}
		}

		return newGraphics2DComponent;
	}
}