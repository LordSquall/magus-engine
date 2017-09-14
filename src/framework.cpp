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
		if (!ProcessEngineConfig(configfilePath))
		{
			return false;
		}

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

		/* create a UA Parser */
		UAParser uaparser(&_resources);

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
					_uas[_uaCount] = uaparser.Parse(dirFile.path);
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

			/* Set software renderer element */
			tinyxml2::XMLElement* swrendererElement = engineElement->FirstChildElement("softwarerenderer");

			/* Check to make sure the software renderer element is present */
			if (swrendererElement != NULL)
			{
				/* vbo memory limit */
				_config.sr_vbo_memorylimit = swrendererElement->IntAttribute("vbomemory");

				/* ibo memory limit */
				_config.sr_ibo_memorylimit = swrendererElement->IntAttribute("ibomemory");

				/* vbo count */
				_config.sr_vbo_limit = swrendererElement->IntAttribute("vbolimit");

				/* ibo count */
				_config.sr_ibo_limit = swrendererElement->IntAttribute("ibolimit");

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

				/* Check to ensure resource path is available */
				tinydir_dir dir;
				tinydir_open(&dir, _resources.GetRootPath());

				if (strcmp(dir.path, "") == 0)
				{
					printf("Unable to find resource path: %s\n", _resources.GetRootPath());
					return false;
				}

				/* Initialise resources object */
				_resources.Initialise(resourcesElement->IntAttribute("texturemax"),
					resourcesElement->IntAttribute("shadermax"),
					resourcesElement->IntAttribute("colormax"),
					resourcesElement->IntAttribute("materialmax"),
					resourcesElement->IntAttribute("fontmax"),
					resourcesElement->IntAttribute("meshmax"));

				/* Process each of the texture tags in turn */
				for (tinyxml2::XMLElement* e = resourcesElement->FirstChildElement("texture"); e != NULL; e = e->NextSiblingElement("texture"))
				{
					if (_resources.AddTextureFromFile(e->Attribute("name"), e->Attribute("path")))
					{
						printf("[Resources] Loaded Texture: %s\n", e->Attribute("name"));
					}
				}

				/* Process each of the shader tags in turn */
				for (tinyxml2::XMLElement* e = resourcesElement->FirstChildElement("shader"); e != NULL; e = e->NextSiblingElement("shader"))
				{
					if(_resources.AddShaderFromFile(e->Attribute("name"), e->Attribute("vertexpath"), e->Attribute("fragmentpath")))
					{
						printf("[Resources] Loaded Shader: %s\n", e->Attribute("name"));
					}
				}

				/* Process each of the font tags in turn */
				for (tinyxml2::XMLElement* e = resourcesElement->FirstChildElement("font"); e != NULL; e = e->NextSiblingElement("font"))
				{
					if(_resources.AddFontFromFile(e->Attribute("name"), e->Attribute("path")))
					{
						printf("[Resources] Loaded Font: %s\n", e->Attribute("name"));
					}
				}

				/* Process each of the color tags in turn */
				for (tinyxml2::XMLElement* e = resourcesElement->FirstChildElement("color"); e != NULL; e = e->NextSiblingElement("color"))
				{
					_resources.AddColor(e->Attribute("name"), new Color(e->Attribute("name"), e->FloatAttribute("r"), e->FloatAttribute("g"), e->FloatAttribute("b"), e->FloatAttribute("a")));
				}

				/* Process each of the mateials tags in turn */
				for (tinyxml2::XMLElement* e = resourcesElement->FirstChildElement("material"); e != NULL; e = e->NextSiblingElement("material"))
				{
					Material* material = new Material(e->Attribute("name"));
					material->SetColor(_resources.GetColor(e->Attribute("color")));
					material->SetTexture(_resources.GetTexture(e->Attribute("texture")));
					_resources.AddMaterial(e->Attribute("name"), material);
				}

				/* Process each of the mesh tags in turn */
				for (tinyxml2::XMLElement* e = resourcesElement->FirstChildElement("mesh"); e != NULL; e = e->NextSiblingElement("mesh"))
				{
					if (_resources.AddMeshFromFile(e->Attribute("name"), e->Attribute("path")))
					{
						printf("[Resources] Loaded Mesh: %s\n", e->Attribute("name"));
					}
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