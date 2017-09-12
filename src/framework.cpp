#include "framework.h"

namespace MagusEngine
{
	Framework::Framework()
	{
		_uas = 0;
		_maxUACount = 0;
		_uaCount = 0;
	}

	bool Framework::Initialise(char* configfilePath)
	{
		/* Initialise Variables */
		_uaCount = 0;
		_maxUACount = 2;


		/* Allocate memory for uaScenes */
		_uas = (UA**)malloc(sizeof(UA**) * _maxUACount);

		/* Process the configuration file */
		ProcessEngineConfig(configfilePath);

		/* Process the UA files */
		ProcessUADataDirectory(_resources.GetRootPath());

		/* Create the os subsystem depending on current platform */
		_os = new OS();

		/* Initialise the os */
		if (_os->Initialise(&_config, &_resources) == false)
		{
			printf("Error: Unable to Initialise OS SubSystem!\n");
			return false;
		}

		/* Initialise the graphics subsystem */
		_graphics.Initialise(_os, &_resources, &_config, _uaCount - 1);

		/* Add each of the generated ua to the graphical root node */
		for (int i = 0; i < _uaCount; i++)
		{
			_graphics.AddScene(_uas[i]->GetRootNode());
		}

		/* Run the Initialise frame to allocate renderer specific memory and initialise visitors */
		_graphics.InitialiseFrame();
		
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
		if (_uas != 0)
		{
			delete _uas;
			_uas = 0;
		}
	}

	bool Framework::ProcessUADataDirectory(const char* uadir)
	{
		int uaCount = 0;

		/* look for engine config file in directory */
		tinydir_dir dir;
		tinydir_open(&dir, uadir);

		/* Process each file in turn */
		while (dir.has_next)
		{
			/* Get file information */
			tinydir_file dirFile;
			tinydir_readfile(&dir, &dirFile);

			/* Open the file as XML Document*/
			if (dirFile.is_dir == false)
			{
				if(strcmp(dirFile.extension, "uadf") == 0)
				{
					_uas[_uaCount] = UAParser::ParserUAFile(dirFile.path, &_resources);
					_uaCount++;
				}
			}
			else
			{
				if((strcmp(dirFile.name, ".") != 0) && (strcmp(dirFile.name, "..") != 0))
				{
					ProcessUADataDirectory(dirFile.path);
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


			/* Set resources element */
			tinyxml2::XMLElement* resourcesElement = engineElement->FirstChildElement("resources");

			/* Check to make sure the resources element is present */
			if (resourcesElement != NULL)
			{
				/* Root path */
				_resources.SetRootPath(resourcesElement->Attribute("root"));

				/* Initialise resources object */
				_resources.Initialise(resourcesElement->IntAttribute("texturemax"),
					resourcesElement->IntAttribute("shadermax"),
					resourcesElement->IntAttribute("colormax"),
					resourcesElement->IntAttribute("materialmax"),
					resourcesElement->IntAttribute("fontmax"));

				/* Process each of the texture tags in turn */
				for (tinyxml2::XMLElement* e = resourcesElement->FirstChildElement("texture"); e != NULL; e = e->NextSiblingElement("texture"))
				{
					_resources.AddTextureFromFile(e->Attribute("name"), e->Attribute("path"));
				}

				/* Process each of the shader tags in turn */
				for (tinyxml2::XMLElement* e = resourcesElement->FirstChildElement("shader"); e != NULL; e = e->NextSiblingElement("shader"))
				{
					_resources.AddShaderFromFile(e->Attribute("name"), e->Attribute("vertexpath"), e->Attribute("fragmentpath"));
				}

				/* Process each of the shader tags in turn */
				for (tinyxml2::XMLElement* e = resourcesElement->FirstChildElement("font"); e != NULL; e = e->NextSiblingElement("font"))
				{
					_resources.AddFontFromFile(e->Attribute("name"), e->Attribute("path"));
				}

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
}