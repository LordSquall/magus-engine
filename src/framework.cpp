#include "framework.h"

namespace MagusEngine
{
	Framework::Framework()
	{
		_sceneCount = 0;
	}

	bool Framework::Initialise(FrameworkConfig* config)
	{
		/* Initialise Variables */
		_sceneCount = 0;
		
		_config = config;

		/* Process the configuration file */
		if (!ProcessEngineConfig(config->configfilePath))
		{
			LOGERROR("Unable to process configuration file: %s", config->configfilePath);
			return false;
		}
		LOGINFO("Configuration Processed Successfully!");

		/* Create the os subsystem depending on current platform */
		_os = new OS();

		/* Initialise the os */
		if (_os->Initialise(_config, &_resources) == false)
		{
			LOGERROR("Unable to Initialise OS SubSystem!");
			return false;
		}

		/* Initialise the graphics subsystem */
		_graphics.Initialise(_os, &_resources, _config, _sceneCount - 1);

		/* Add each of the generated ua to the graphical root node */
		for (int i = 0; i < _sceneCount; i++)
		{
			_graphics.AddScene(_scenes[i]->GetRootNode());
		}

		/* Run the Initialise frame to allocate renderer specific memory and initialise visitors */
		_graphics.InitialiseFrame();
		
		/* Intialise the Data Model */
		if (_dataModel.Initialise() == false)
		{
			LOGERROR("Unable to Initialise Datamodel on port 9000");
			return false;
		}

		/* Initailise the bahavioural visitor to control message between the dm and scene */
		_behaviourVisitor = new BehaviourVisitor(&_dataModel);
		
		/* Intialise network communications */
		_network = new Network();

		_network->SetDataModel(&_dataModel);
		_network->EstablishUDP(9000);
		_network->StartRecieve();


		return true;
	}

	bool Framework::Frame()
	{
		/* Input Frame */
		
		/* Behavioural Update */
		_graphics.GetRootSceneNode()->Accept(_behaviourVisitor);

		_behaviourVisitor->initialPass = false;

		/* Graphics Frame */
		return _graphics.Frame();
	}

	bool Framework::Shutdown()
	{
		/* Shutdown resources */
		if (_resources.Shutdown() == false)
		{
			LOGERROR("Unable to Shutdown Resources Subsystem");
			return false;
		}
		
		if (_graphics.Shutdown() == false)
		{
			LOGERROR("Unable to Shutdown Graphics Subsystem");
			return false;
		}

		if (_os != NULL)
		{
			if (_os->Shutdown() == false)
			{
				LOGERROR("Unable to Shutdown OS Subsystem");
				return false;
			}
			delete _os;
			_os = NULL;
		}
		
		return true;
	}

	bool Framework::ProcessUADataDirectory(const char* uadir)
	{
		int uaCount = 0;

		/* create a Scene Parser */
		SceneParser sceneparser(&_resources);

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
					_scenes[_sceneCount] = sceneparser.Parse(dirFile.path);
					_sceneCount++;
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
		tinyxml2::XMLError error = doc.LoadFile(filename);

		/* Check for xml errors */
		if (error != tinyxml2::XMLError::XML_SUCCESS)
		{
			LOGERROR("Failure to Read XML file @%s [%s]", filename, tinyxml2::XMLDocument::ErrorIDToName(error));
			return false;
		}
		else
		{
			LOGINFO("Configuration File Loaded @%s", filename);
		}

		/* Get engine element */
		tinyxml2::XMLElement* engineElement = doc.FirstChildElement("engine");

		/* Check to make sure the root tag is engine */
		if (engineElement != NULL)
		{
			/* title */
			const char* title = engineElement->Attribute("title");

			if (title == NULL){
				LOGERROR("Engine tag missing 'title' attribute @ line %d", engineElement->GetLineNum());
				return false;
			}
			strcpy(_config->title, title);


			/* resolution element */
			tinyxml2::XMLElement* resolutionElement = engineElement->FirstChildElement("resolution");

			/* Check to make sure the resolution element is present */
			if(resolutionElement != NULL)
			{
				/* width */
				int width = resolutionElement->IntAttribute("width");
				if (width == 0)
				{
					LOGERROR("Resolution tag either missing 'width' attribute or attribute cannot be '0' @ line %d", resolutionElement->GetLineNum());
					return false;
				}
				_config->width = width;

				/* height */
				int height = resolutionElement->IntAttribute("height");
				if (width == 0)
				{
					LOGERROR("Resolution tag either missing 'width' attribute or attribute cannot be '0' @ line %d", resolutionElement->GetLineNum());
					return false;
				}
				_config->height = height;

				/* fullscreen */
				_config->fullscreen = resolutionElement->BoolAttribute("fullscreen");
			}
			else
			{
				LOGERROR("Missing required 'resolution' element from configuration file");
				return false;
			}

			/* Set software renderer element */
			tinyxml2::XMLElement* swrendererElement = engineElement->FirstChildElement("softwarerenderer");

			/* Check to make sure the software renderer element is present */
			if (swrendererElement != NULL)
			{
				/* vbo memory limit */
				unsigned int vbo_mem_limit = swrendererElement->IntAttribute("vbomemory");
				if (vbo_mem_limit == 0)
				{
					LOGWARN("SWRenderer tag either missing 'vbomemory' attribute or attribute is set to '0' @ line %d", swrendererElement->GetLineNum());
					return false;
				}
				_config->sr_vbo_memorylimit = vbo_mem_limit;

				/* ibo memory limit */
				unsigned int ibo_mem_limit = swrendererElement->IntAttribute("ibomemory");
				if (ibo_mem_limit == 0)
				{
					LOGWARN("SWRenderer tag either missing 'ibomemory' attribute or attribute is set to '0' @ line %d", swrendererElement->GetLineNum());
					return false;
				}
				_config->sr_ibo_memorylimit = ibo_mem_limit;

				/* vbo count */
				unsigned int vbo_count = swrendererElement->IntAttribute("vbolimit");
				if (vbo_count == 0)
				{
					LOGWARN("SWRenderer tag either missing 'vbolimit' attribute or attribute is set to '0' @ line %d", swrendererElement->GetLineNum());
					return false;
				}
				_config->sr_vbo_limit = vbo_count;

				/* ibo count */
				unsigned int ibo_count = swrendererElement->IntAttribute("ibolimit");
				if (ibo_count == 0)
				{
					LOGWARN("SWRenderer tag either missing 'ibolimit' attribute or attribute is set to '0' @ line %d", swrendererElement->GetLineNum());
					return false;
				}
				_config->sr_ibo_limit = ibo_count;
			}
			else
			{
				LOGERROR("Missing required 'softwarerenderer' element from configuration file");
				return false;
			}


			/* Set resources element */
			tinyxml2::XMLElement* resourcesElement = engineElement->FirstChildElement("resources");

			/* Check to make sure the resources element is present */
			if (resourcesElement != NULL)
			{
				/* Root path */
				const char* rootPath = resourcesElement->Attribute("root");
				if (rootPath != NULL)
				{
					_resources.SetRootPath(rootPath);
				}
				else
				{
					LOGERROR("Missing 'root' attribute in 'resource' tag @ line %d", resourcesElement->GetLineNum());
					return false;
				}

				/* Check to ensure resource path is available */
				tinydir_dir dir;
				tinydir_open(&dir, _resources.GetRootPath());

				if (strcmp(dir.path, "") == 0)
				{
					LOGERROR("Unable to find resource path: %s\n", _resources.GetRootPath());
					return false;
				}

				int texturemax = resourcesElement->IntAttribute("texturemax");
				int shadermax = resourcesElement->IntAttribute("shadermax");
				int colormax = resourcesElement->IntAttribute("colormax");
				int materialmax = resourcesElement->IntAttribute("materialmax");
				int fontmax = resourcesElement->IntAttribute("fontmax");
				int meshmax = resourcesElement->IntAttribute("meshmax");

				/* Check to ensure resource values are available */
				if (texturemax == 0) LOGWARN("Texture max value 'texturemax' is either missing or set to '0' @ line %d", resourcesElement->GetLineNum());
				if (shadermax == 0) LOGWARN("Shader max value 'shadermax' is either missing or set to '0' @ line %d", resourcesElement->GetLineNum());
				if (colormax == 0) LOGWARN("Color max value 'colormax' is either missing or set to '0' @ line %d", resourcesElement->GetLineNum());
				if (materialmax == 0) LOGWARN("Material max value 'materialmax' is either missing or set to '0' @ line %d", resourcesElement->GetLineNum());
				if (fontmax == 0) LOGWARN("Font max value 'fontmax' is either missing or set to '0' @ line %d", resourcesElement->GetLineNum());
				if (meshmax == 0) LOGWARN("Mesh max value 'meshmax' is either missing or set to '0' @ line %d", resourcesElement->GetLineNum());

				/* Initialise resources object */
				if (_resources.Initialise(texturemax, shadermax, colormax, materialmax, fontmax, meshmax) == false)
				{
					LOGERROR("Unable to Initialise Resources SubSystem");
				}

				LOGHEADER("Adding Engine Resources");

				/* Process each of the texture tags in turn */
				for (tinyxml2::XMLElement* e = resourcesElement->FirstChildElement("texture"); e != NULL; e = e->NextSiblingElement("texture"))
				{

					if (_resources.AddTextureFromFile(e->Attribute("name"), e->Attribute("path")))
					{
						LOGINFO("Loaded Texture: %s", e->Attribute("name"));
					}
				}

				/* Process each of the shader tags in turn */
				for (tinyxml2::XMLElement* e = resourcesElement->FirstChildElement("shader"); e != NULL; e = e->NextSiblingElement("shader"))
				{
					if(_resources.AddShaderFromFile(e->Attribute("name"), e->Attribute("vertexpath"), e->Attribute("fragmentpath")))
					{
						LOGINFO("Loaded Shader: %s", e->Attribute("name"));
					}
				}

				/* Process each of the font tags in turn */
				for (tinyxml2::XMLElement* e = resourcesElement->FirstChildElement("font"); e != NULL; e = e->NextSiblingElement("font"))
				{
					if(_resources.AddFontFromFile(e->Attribute("name"), e->Attribute("path")))
					{
						LOGINFO("Loaded Font: %s", e->Attribute("name"));
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
					material->SetColor1(_resources.GetColor(e->Attribute("color1")));
					material->SetColor2(_resources.GetColor(e->Attribute("color2")));
					material->SetTexture(_resources.GetTexture(e->Attribute("texture")));
					_resources.AddMaterial(e->Attribute("name"), material);
				}

				/* Process each of the mesh tags in turn */
				for (tinyxml2::XMLElement* e = resourcesElement->FirstChildElement("mesh"); e != NULL; e = e->NextSiblingElement("mesh"))
				{
					if (_resources.AddMeshFromFile(e->Attribute("name"), e->Attribute("path")))
					{
						LOGINFO("Loaded Mesh: %s", e->Attribute("name"));
					}
				}
			}
			else
			{
				LOGERROR("Missing 'resources' element from configuration file");
				return false;
			}

			/* Get scenes element */
			tinyxml2::XMLElement* scenesElement = engineElement->FirstChildElement("scenes");

			/* Check to make sure the next tag is scenesElement */
			if (scenesElement != NULL)
			{
				/* Process each of the scene tags in turn */
				for (tinyxml2::XMLElement* e = scenesElement->FirstChildElement("scene"); e != NULL; e = e->NextSiblingElement("scene"))
				{
					/* Full path buffer */
					char fullPathBuffer[255];

					/* create a Scene Parser */
					SceneParser sceneparser(&_resources);


					sprintf(fullPathBuffer, "%s%s", _resources.GetRootPath(), e->Attribute("path"));

					_scenes[_sceneCount] = sceneparser.Parse(fullPathBuffer);
					_sceneCount++;
				}
			}
			else
			{
				LOGERROR("Missing 'scenes' element from configuration file");
				return false;
			}
		}
		else
		{
			LOGERROR("Missing 'engine' element from configuration file");
			return false;
		}

		return true;
	}
}