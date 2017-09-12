#include "UAParser.h"

namespace MagusEngine
{
	UA* UAParser::ParserUAFile(const char* filename, Resources* resources)
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

			/* Set the styles element */
			tinyxml2::XMLElement* stylesElement = uaElement->FirstChildElement("styles");

			/* Check to make sure the styles element is present */
			if (stylesElement != NULL)
			{
				/* Load color table */
				for (tinyxml2::XMLElement* e = stylesElement->FirstChildElement("color"); e != NULL; e = e->NextSiblingElement("color"))
				{
					float r = e->FloatAttribute("r");
					float g = e->FloatAttribute("g");
					float b = e->FloatAttribute("b");
					float a = e->FloatAttribute("a");

					resources->AddColor(e->IntAttribute("id"), e->Attribute("name"), r, g, b, a);
				}

				/* Load material table */
				for (tinyxml2::XMLElement* e = stylesElement->FirstChildElement("material"); e != NULL; e = e->NextSiblingElement("material"))
				{
					resources->AddMaterial(new Material(e->IntAttribute("id"), e->Attribute("name"), e->IntAttribute("colorid", -1), e->IntAttribute("textureid", -1)));
				}
			}

			/* Set scene element */
			tinyxml2::XMLElement* sceneElement = uaElement->FirstChildElement("scene");

			/* Check to make sure the scene element is present */
			if (sceneElement != NULL)
			{
				/* Set root element of the scene */
				tinyxml2::XMLElement* rootElement = sceneElement->FirstChildElement("node");

				newUA->SetRootNode(ProcessSceneNode(rootElement, resources));
			}

		}

		return newUA;
	}

	SceneNode* UAParser::ProcessSceneNode(tinyxml2::XMLElement* element, Resources* resources)
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
				newNode->AddChild(ProcessSceneNode(e, resources));
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
				newNode->SetRotation(rotationElement->FloatAttribute("x"), rotationElement->FloatAttribute("y"), rotationElement->FloatAttribute("z"));
			}

			/* Check for scale information */
			tinyxml2::XMLElement* scaleElement = transformElement->FirstChildElement("scale");

			if (scaleElement != NULL)
			{
				newNode->SetScale(scaleElement->FloatAttribute("x"), scaleElement->FloatAttribute("y"), scaleElement->FloatAttribute("z"));
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
					newNode->AddComponent(ProcessSceneNodeComponent(e, resources));
				}
			}
		}

		return newNode;
	}


	Component* UAParser::ProcessSceneNodeComponent(tinyxml2::XMLElement* element, Resources* resources)
	{
		/* Check to determine the type of the component */
		if (strcmp(element->Name(), "graphics2d") == 0)
		{
			return ProcessSceneNodeComponentGraphics2D(element, resources);
		}
		
		return NULL;
	}

	Graphic2D* UAParser::ProcessSceneNodeComponentGraphics2D(tinyxml2::XMLElement* element, Resources* resources)
	{
		/* Create component as a 2d graphic */
		Graphic2D* newGraphics2DComponent = new Graphic2D();

		/* Retrive material id */
		newGraphics2DComponent->SetMaterial(resources->GetMaterial(element->IntAttribute("material")));

		/* Process each of the children tags in turn */
		for (tinyxml2::XMLElement* e = element->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			/* Check to determine the type of the drawable */
			if (strcmp(e->Name(), "rectangle") == 0)
			{
				Rectangle* newDrawable = new Rectangle(e->FloatAttribute("x"), e->FloatAttribute("y"), e->FloatAttribute("width"), e->FloatAttribute("height"));
				newGraphics2DComponent->SetDrawable(newDrawable);
			}
			if (strcmp(e->Name(), "line") == 0)
			{
				Line* newDrawable = new Line(e->FloatAttribute("x1"), e->FloatAttribute("y1"), e->FloatAttribute("x2"), e->FloatAttribute("y2"));
				newDrawable->SetWidth(e->FloatAttribute("width"));
				newGraphics2DComponent->SetDrawable(newDrawable);

			}if (strcmp(e->Name(), "text") == 0)
			{
				Text* newDrawable = new Text(e->FloatAttribute("x", 0.0f), e->FloatAttribute("y", 0.0f), e->Attribute("content", "UNKNOWN"));
				newGraphics2DComponent->SetDrawable(newDrawable);
			}
		}

		return newGraphics2DComponent;
	}
}