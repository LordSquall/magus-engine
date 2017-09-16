#include "SceneParser.h"

namespace MagusEngine
{
	SceneParser::SceneParser(Resources* resources)
	{
		_resources = resources;

		_materialStackHead = 0;

		/* Add the default material to the material stack */
		_materialStack[_materialStackHead] = _resources->GetMaterial("default");
		_materialStackHead++;
	}

	Scene* SceneParser::Parse(const char* filename)
	{
		Scene* newScene = new Scene();

		tinyxml2::XMLDocument doc;
		doc.LoadFile(filename);

		/* Get engine element */
		tinyxml2::XMLElement* sceneRootElement = doc.FirstChildElement("scene");

		/* Check to make sure the root tag is scene */
		if (sceneRootElement != NULL)
		{
			/* Scene Title */
			newScene->Initialise(sceneRootElement->Attribute("title"));

			/* Set the styles element */
			tinyxml2::XMLElement* stylesElement = sceneRootElement->FirstChildElement("styles");

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

					_resources->AddColor(e->Attribute("name"), new Color(e->Attribute("name"), r, g, b, a));
				}

				/* Load material table */
				for (tinyxml2::XMLElement* e = stylesElement->FirstChildElement("material"); e != NULL; e = e->NextSiblingElement("material"))
				{
					Material* material = new Material(e->Attribute("name"));
					material->SetColor1(_resources->GetColor(e->Attribute("color1")));
					material->SetColor2(_resources->GetColor(e->Attribute("color2")));
					material->SetTexture(_resources->GetTexture(e->Attribute("texture")));
					_resources->AddMaterial(e->Attribute("name"), material);
				}
			}

			/* Set graphical model element */
			tinyxml2::XMLElement* graphicalModelElement = sceneRootElement->FirstChildElement("graphicalmodel");

			/* Check to make sure the graphical model element is present */
			if (graphicalModelElement != NULL)
			{
				/* Set root element of the scene */
				tinyxml2::XMLElement* rootElement = graphicalModelElement->FirstChildElement("node");

				newScene->SetRootNode(ProcessSceneNode(rootElement));
			}

		}

		return newScene;
	}

	SceneNode* SceneParser::ProcessSceneNode(tinyxml2::XMLElement* element)
	{
		/* Create a new scene node */
		SceneNode* newNode = new SceneNode();


		/* Get the children count */
		int childrenCount = element->IntAttribute("children");

		/* Initialise the node name */
		newNode->Initialise(element->Attribute("name"), childrenCount);

		/* Set Criticality */
		newNode->SetCriticality(element->BoolAttribute("critical"));

		/* Get the material */
		Material* material = _resources->GetMaterial(element->Attribute("material"));
		if (material == NULL)
		{
			newNode->SetMaterial(_materialStack[_materialStackHead - 1]);
		}
		else
		{
			newNode->SetMaterial(material);
			_materialStack[_materialStackHead] = material;
			_materialStackHead++;
		}

		/* Get filter info */
		newNode->SetIsFilter(element->BoolAttribute("filter"));

		if (childrenCount > 0)
		{
			for (tinyxml2::XMLElement* e = element->FirstChildElement("node"); e != NULL; e = e->NextSiblingElement("node"))
			{
				/* Process child node */
				newNode->AddChild(ProcessSceneNode(e));
			}
		}

		if (material != NULL)
		{
			_materialStackHead--;
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

		/* Check for material information */
		tinyxml2::XMLElement* materialElement = element->FirstChildElement("material");

		if (materialElement != NULL)
		{
			/* color 1 */
			Color* color1 = _resources->GetColor(materialElement->Attribute("color1"));
			
			if (color1 != NULL)
			{
				newNode->GetMaterial()->SetColor1(color1);
			}

			/* color 2 */
			Color* color2 = _resources->GetColor(materialElement->Attribute("color2"));

			if (color2 != NULL)
			{
				newNode->GetMaterial()->SetColor2(color2);
			}

			/* texture */
			Texture* texture = _resources->GetTexture(materialElement->Attribute("texture"));

			if (texture != NULL)
			{
				newNode->GetMaterial()->SetTexture(texture);
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


	Component* SceneParser::ProcessSceneNodeComponent(tinyxml2::XMLElement* element)
	{
		/* Check to determine the type of the component */
		if (strcmp(element->Name(), "graphics2d") == 0)
		{
			return ProcessSceneNodeComponentGraphics2D(element);
		}
		
		return NULL;
	}

	Graphic2D* SceneParser::ProcessSceneNodeComponentGraphics2D(tinyxml2::XMLElement* element)
	{
		/* Create component as a 2d graphic */
		Graphic2D* newGraphics2DComponent = new Graphic2D();

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
				Text* newDrawable = new Text(e->FloatAttribute("x", 0.0f), e->FloatAttribute("y", 0.0f), "UNKNOWN");
				newDrawable->SetContent(e->Attribute("content"));
				newDrawable->SetFont(_resources->GetFont(e->IntAttribute("font")));
				newGraphics2DComponent->SetDrawable(newDrawable);

			}if (strcmp(e->Name(), "ellipse") == 0)
			{
				Ellipse* newDrawable = new Ellipse(e->FloatAttribute("x"), e->FloatAttribute("y"), e->FloatAttribute("rx"), e->FloatAttribute("ry"));
				newGraphics2DComponent->SetDrawable(newDrawable);
			}
			if (strcmp(e->Name(), "path") == 0)
			{
				Path* newDrawable = new Path(e->Attribute("points"));
				newGraphics2DComponent->SetDrawable(newDrawable);
			}
		}

		return newGraphics2DComponent;
	}
}