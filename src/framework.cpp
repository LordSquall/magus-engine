#include "framework.h"

namespace MagusEngine
{
	Framework::Framework()
	{

	}

	bool Framework::Initialise(char* dataDirectory)
	{
		/* Process the data directory to load external resources */
		ProcessDataDirectory(dataDirectory);

		/* Create the os subsystem depending on current platform */
		_os = new OS();

		/* Initialise the os */
		if (_os->Initialise(&_config) == false)
		{
			printf("Error: Unable to Initialise OS SubSystem!\n");
			return false;
		}

		/* Initialise the graphics subsystem */
		_graphics.Initialise(_os);

		for(std::vector<SceneNode*>::iterator it = _uaScenes.begin(); it != _uaScenes.end(); ++it)
		{
			_graphics.AddScene((SceneNode*)&it);
		}
		
		return true;
	}

	bool Framework::Frame()
	{
		/* Input Frame */

		/* Graphics Frame */
		_graphics.Frame();

		return true;
	}

	void Framework::Shutdown()
	{

	}

	bool Framework::ProcessDataDirectory(const char* dataDirectory)
	{
		int uaCount = 0;

		/* look for engine config file in directory */
		tinydir_dir dir;
		tinydir_open(&dir, dataDirectory);

		/* Process each file in turn */
		while (dir.has_next)
		{
			/* Get file information */
			tinydir_file dirFile;
			tinydir_readfile(&dir, &dirFile);

			/* Open the file as XML Document*/
			if (dirFile.is_dir == false)
			{
				if(strcmp(dirFile.extension, "conf") == 0)
				{
					ProcessEngineConfig(dirFile.path);
				}

				if(strcmp(dirFile.extension, "uadf") == 0)
				{
					ProcessUA(dirFile.path);
				}
			}
			else
			{
				if((strcmp(dirFile.name, ".") != 0) && (strcmp(dirFile.name, "..") != 0))
				{
					ProcessDataDirectory(dirFile.path);
				}
			}
			tinydir_next(&dir);
		}

		tinydir_close(&dir);

		return true;
	}

	bool Framework::ProcessEngineConfig(const char* filename)
	{
		tinyxml2::XMLDocument doc;
		doc.LoadFile(filename);

		/* Get engine element */
		tinyxml2::XMLElement* engineElement = doc.FirstChildElement("engine");

		/* Check to make sure the root tag is engine */
		if (engineElement != NULL)
		{
			/* title */
			strcpy_s(_config.title, engineElement->Attribute("title"));

			/* Set resolution element */
			tinyxml2::XMLElement* resolutionElement = engineElement->FirstChildElement("resolution");

			/* Check to make sure the resolution element is present */
			if(resolutionElement != NULL)
			{
				/* width */
				_config.width = resolutionElement->IntAttribute("width");
						
				/* height */
				_config.height = resolutionElement->IntAttribute("height");
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}

		return true;
	}


	bool Framework::ProcessUA(const char* uaFile)
	{

		tinyxml2::XMLDocument doc;
		doc.LoadFile(uaFile);

		/* Get engine element */
		tinyxml2::XMLElement* uaElement = doc.FirstChildElement("UA");

		/* Check to make sure the root tag is UA */
		if (uaElement != NULL)
		{
			/* Set scene element */
			tinyxml2::XMLElement* sceneElement = uaElement->FirstChildElement("scene");

			/* Check to make sure the scene element is present */
			if(sceneElement != NULL)
			{
				/* Set root element of the scene */
				tinyxml2::XMLElement* rootElement = sceneElement->FirstChildElement("node");

				_uaScenes.push_back(ProcessSceneNode(rootElement));
			}
		}

		return true;
	}


	SceneNode* Framework::ProcessSceneNode(tinyxml2::XMLElement* element)
	{
		/* Create a new scene node */
		SceneNode* newNode = new SceneNode();
		
		/* Get the children count */
		int childrenCount = element->IntAttribute("children");

		/* Initialise the node name */
		newNode->Initialise(element->Attribute("name"));

		if(childrenCount > 0)
		{
			for(tinyxml2::XMLElement* e = element->FirstChildElement("node"); e != NULL; e = e->NextSiblingElement("node"))
			{
				newNode->AddChild(ProcessSceneNode(e));
			}
		}
	
		/* Check for transform information */
		tinyxml2::XMLElement* transformElement = element->FirstChildElement("transform");

		if(transformElement != NULL)
		{
			/* Check for position information */
			tinyxml2::XMLElement* positionElement = transformElement->FirstChildElement("position");

			if(positionElement != NULL)
			{
				newNode->SetPosition(positionElement->FloatAttribute("x"), positionElement->FloatAttribute("y"), positionElement->FloatAttribute("z"));
			}

			/* Check for rotation information */
			tinyxml2::XMLElement* rotationElement = transformElement->FirstChildElement("rotation");

			if(rotationElement != NULL)
			{
				newNode->SetPosition(rotationElement->FloatAttribute("x"), rotationElement->FloatAttribute("y"), rotationElement->FloatAttribute("z"));
			}

			/* Check for scale information */
			tinyxml2::XMLElement* scaleElement = transformElement->FirstChildElement("scale");

			if(scaleElement != NULL)
			{
				newNode->SetPosition(scaleElement->FloatAttribute("x"), scaleElement->FloatAttribute("y"), scaleElement->FloatAttribute("z"));
			}
		}

		return newNode;
	}

	int Framework::CountUAFiles(const char* directory)
	{
		int file_count = 0;

		/* look for ua config files in directory */
		tinydir_dir dir;
		tinydir_open(&dir, directory);

		/* Process each file in turn */
		while (dir.has_next)
		{
			/* Get file information */
			tinydir_file dirFile;
			tinydir_readfile(&dir, &dirFile);

			/* Open the file as XML Document*/
			if (dirFile.is_dir == false)
			{
				file_count++;
			}
			tinydir_next(&dir);
		}

		tinydir_close(&dir);

		return file_count;
	}
}