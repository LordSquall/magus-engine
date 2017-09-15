#include "resources.h"

namespace MagusEngine
{
	Resources::Resources()
	{
		
	}

	bool Resources::Initialise(unsigned int textureMax, unsigned int shaderMax, unsigned int colorMax, unsigned int materialMax, unsigned int fontMax, unsigned int meshMax)
	{
		/* Initialse memory for research hashtables */
		if (_textureHashTable.Initialise(textureMax) == false)
		{
			LOGERROR("Unable to Initialise Texture ResourcesStorage");
			return false;
		}
		else
		{
			LOGINFO("Initialised Texture Resources Storage [MAX %d]", textureMax);
		}

		if (_shadersHashTable.Initialise(shaderMax) == false)
		{
			LOGERROR("Unable to Initialise Shader Resources");
			return false;
		}
		else
		{
			LOGINFO("Initialised Shader Resources Storage [MAX %d]", shaderMax);
		}

		if (_colorHashTable.Initialise(colorMax) == false)
		{
			LOGERROR("Unable to Initialise Color Resources");
			return false;
		}
		else
		{
			LOGINFO("Initialised Color Resources Storage [MAX %d]", colorMax);
		}

		if (_materialsHashTable.Initialise(materialMax) == false)
		{
			LOGERROR("Unable to Initialise Material Resources");
			return false;
		}
		else
		{
			LOGINFO("Initialised Material Resources Storage [MAX %d]", materialMax);
		}

		if (_fontsHashTable.Initialise(fontMax) == false)
		{
			LOGERROR("Unable to Initialise Font Resources");
			return false;
		}
		else
		{
			LOGINFO("Initialised Font Resources Storage [MAX %d]", fontMax);
		}

		if (_meshHashTable.Initialise(meshMax) == false)
		{
			LOGERROR("Unable to Initialise Mesh Resources");
			return false;
		}
		else
		{
			LOGINFO("Initialised Mesh Resources Storage [MAX %d]", meshMax);
		}

		/* Create dummy 1x1 image with full alpha as default bound texture */
		LOGINFO("Creating Default Texture Resource [_defaultBound]");
		Texture* newTexture = new Texture("_defaultBound", 1, 1);
		newTexture->Initialise(1);
		newTexture->GetData()[0] = 0x00;
		newTexture->GetData()[1] = 0x00;
		newTexture->GetData()[2] = 0x00;
		newTexture->GetData()[3] = 0xFF;

		if (AddTexture("_defaultBound", newTexture) == false)
		{
			LOGERROR("Unable to Initialise Default Texture");
			return false;
		}


		return true;
	}

	bool Resources::AddTextureFromFile(const char* name, const char* path)
	{
		Texture* newTexture = 0;
		const char* extension = GetFileExt(path);

		if(strcmp(extension, "bmp") == 0)
		{
			newTexture = LoadBmp(name, path);
		}
		else if(strcmp(extension, "png") == 0)
		{
			newTexture = LoadPng(name, path);
		}

		/* Add the resources object */
		AddTexture(name, newTexture);
		
		return true;
	}

	bool Resources::AddShaderFromFile(const char* name, const char* vertexpath, const char* fragmentPath)
	{
		/* Full path buffer */
		char fullVertexPathBuffer[255];
		char fullFragmentPathBuffer[255];
		sprintf_s(fullVertexPathBuffer, "%s%s", _rootPath, vertexpath);
		sprintf_s(fullFragmentPathBuffer, "%s%s", _rootPath, fragmentPath);

		/* Sortes file size */
		std::streamsize filesize;

		/* New texture object */
		Shader* newShader = new Shader(name);

		/* Open the vertex file */
		std::ifstream vertexFile(fullVertexPathBuffer, std::ios::binary | std::ios::ate);
		if (!vertexFile)
		{
			printf("Failure to open bitmap file.\n");
			return false;
		}

		/* Get file size */
		filesize = vertexFile.tellg();

		/* Reset stream */
		vertexFile.seekg(0);

		/* Allocate memory in shader for source */
		newShader->InitailiseVertexSourceBuffer((unsigned int)filesize - 1);

		/* Read fill contents into the shader source buffer */
		vertexFile.read(newShader->GetVertexSrc(), filesize);

		/* Close file stream */
		vertexFile.close();

		/* Append termination character */
		newShader->GetVertexSrc()[filesize] = '\0';

		/* Open the fragment file */
		std::ifstream fragmentFile(fullFragmentPathBuffer, std::ios::binary | std::ios::ate);
		if (!fragmentFile)
		{
			printf("Failure to open fragment file.\n");
			return false;
		}

		/* Get file size */
		filesize = fragmentFile.tellg();

		/* Reset stream */
		fragmentFile.seekg(0);

		/* Allocate memory in shader for source */
		newShader->InitailiseFragmentSourceBuffer((unsigned int)filesize + 1);

		/* Read fill contents into the shader source buffer */
		fragmentFile.read(newShader->GetFragmentSrc(), filesize);

		/* Close the file stream */
		fragmentFile.close();

		/* Append termination character */
		newShader->GetFragmentSrc()[filesize] = '\0';

		/* Add the resources object */
		AddShader(name, newShader);
		
		return true;
	}

	bool Resources::AddFontFromFile(const char* name, const char* path)
	{
		/* Full path buffer */
		char fullPathBuffer[255];
		sprintf_s(fullPathBuffer, "%s%s", _rootPath, path);
	
		Font* newFont = FontParser::ParseFontFile(fullPathBuffer, name, this);

		/* Add the resources object */
		AddFont(name, newFont);
		
		return true;
	}

	bool Resources::AddMeshFromFile(const char* name, const char* path)
	{
		/* Full path buffer */
		char fullPathBuffer[255];
		sprintf_s(fullPathBuffer, "%s%s", _rootPath, path);

		Mesh* newMesh = OBJParser::ParseOBJFile(fullPathBuffer, name, this);

		/* Add the resources object */
		AddMesh(name, newMesh);

		return true;
	}

	Texture* Resources::LoadBmp(const char* name, const char* path)
	{
		/* Full path buffer */
		char fullPathBuffer[255];
		sprintf_s(fullPathBuffer, "%s%s", _rootPath, path);

		/* Open the file */
		std::ifstream file(fullPathBuffer, std::ios::binary);
		if (!file)
		{
			printf("Failure to open bitmap file.\n");
			return NULL;
		}

		BITMAPFILEHEADER* bmpHeader = nullptr; // Header
		BITMAPINFOHEADER* bmpInfo = nullptr; // Info 

		Byte* datBuff[2] = { nullptr, nullptr };

		Byte* pixels = nullptr;

		// Allocate byte memory that will hold the two headers
		datBuff[0] = new Byte[sizeof(BITMAPFILEHEADER)];
		datBuff[1] = new Byte[sizeof(BITMAPINFOHEADER)];

		file.read((char*)datBuff[0], sizeof(BITMAPFILEHEADER));
		file.read((char*)datBuff[1], sizeof(BITMAPINFOHEADER));

		// Construct the values from the buffers
		bmpHeader = (BITMAPFILEHEADER*)datBuff[0];
		bmpInfo = (BITMAPINFOHEADER*)datBuff[1];

		// Check if the file is an actual BMP file
		if (bmpHeader->bfType != 0x4D42)
		{
			printf("File %s isn't a bitmap file\n", fullPathBuffer);
			return NULL;
		}

		// Calculate image size
		long imageSize = bmpInfo->biWidth * bmpInfo->biHeight * (bmpInfo->biBitCount / 8);

		// First allocate pixel memory
		pixels = new Byte[imageSize];

		// Go to where image data starts, then read in image data
		file.seekg(bmpHeader->bfOffBits);
		file.read((char*)pixels, imageSize);


		Byte tmpRGB = 0; // Swap buffer
		for (long i = 0; i < imageSize; i += 3)
		{
			tmpRGB = pixels[i];
			pixels[i] = pixels[i + 2];
			pixels[i + 2] = tmpRGB;
		}


		file.close();

		/* New texture object */
		Texture* newTexture = new Texture(name, bmpInfo->biWidth, bmpInfo->biHeight);

		/* Intialise texture memory */
		newTexture->Initialise(imageSize);

		/* Load pixels in to texture object */
		newTexture->LoadPixelData(pixels, imageSize);

		delete[] datBuff[0];
		delete[] datBuff[1];

		return newTexture;
	}

	Texture* Resources::LoadPng(const char* name, const char* path)
	{
		/* Full path buffer */
		char fullPathBuffer[255];
		sprintf_s(fullPathBuffer, "%s%s", _rootPath, path);

		unsigned int error;
		unsigned width, height;
		unsigned char* pixels = nullptr;

		error = lodepng_decode32_file(&pixels, &width, &height, fullPathBuffer);

		/* Calculate image size */
		long imageSize = width * height * 4;

		/* New texture object */
		Texture* newTexture = new Texture(name, width, height);

		/* Intialise texture memory */
		newTexture->Initialise(imageSize);

		/* Load pixels in to texture object */
		newTexture->LoadPixelData((Byte*)pixels, imageSize);

		return newTexture;
	}

	/* Shader Functions */
	bool Resources::AddShader(const char* name, Shader* shader)
	{
		ShaderDataItem* dataItem = new ShaderDataItem();
		strcpy_s(dataItem->id, name);
		dataItem->data = shader;

		_shadersHashTable.Insert(dataItem);

		return true;
	}

	unsigned int Resources::GetShaderCount()
	{
		return _shadersHashTable.GetCount();
	}

	Shader* Resources::GetShader(unsigned int index)
	{
		return ((ShaderDataItem*)_shadersHashTable.Get(index))->data;
	}

	Shader* Resources::GetShader(const char* name)
	{
		if (name != NULL)
		{
			ShaderDataItem* dataItem = (ShaderDataItem*)_shadersHashTable.Search(name);
			if (dataItem != NULL)
			{
				return dataItem->data;
			}
		}
		return NULL;
	}

	/* Texture Functions */
	bool Resources::AddTexture(const char* name, Texture* texture)
	{
		TextureDataItem* dataItem = new TextureDataItem();

		if (dataItem == NULL)
		{
			LOGERROR("Failed 'new' on Texture Data Item");
			return false;
		}

		if (strcpy_s(dataItem->id, name) != 0)
		{
			LOGERROR("strcpy_s failed");
			return false;
		}
		dataItem->data = texture;

		if (_textureHashTable.Insert(dataItem) == false)
		{
			LOGERROR("Unable to add Texture [%s] to hashtable", texture->GetName());
			return false;
		}
		else
		{
			LOGINFO("Texture [%s] Added to Resources", texture->GetName());
		}

		return true;
	}

	unsigned int Resources::GetTextureCount()
	{
		return _textureHashTable.GetCount();
	}

	Texture* Resources::GetTexture(unsigned int index)
	{
		return ((TextureDataItem*)_textureHashTable.Get(index))->data;
	}

	Texture* Resources::GetTexture(const char* name)
	{
		if (name != NULL)
		{
			TextureDataItem* dataItem = (TextureDataItem*)_textureHashTable.Search(name);
			if (dataItem != NULL)
			{
				return dataItem->data;
			}
		}
		return NULL;
	}

	/* Color Functions */
	bool Resources::AddColor(const char* name, Color* color)
	{
		ColorDataItem* dataItem = new ColorDataItem();
		strcpy_s(dataItem->id, name);
		dataItem->data = color;

		_colorHashTable.Insert(dataItem);

		return true;
	}
	
	unsigned int Resources::GetColorCount()
	{
		return _colorHashTable.GetCount();
	}

	Color* Resources::GetColor(unsigned int index)
	{
		return ((ColorDataItem*)_colorHashTable.Get(index))->data;
	}

	Color* Resources::GetColor(const char* name)
	{
		if (name != NULL)
		{
			ColorDataItem* dataItem = (ColorDataItem*)_colorHashTable.Search(name);
			if (dataItem != NULL)
			{
				return dataItem->data;
			}
		}
		return NULL;
	}


	/* Material Functions */
	bool Resources::AddMaterial(const char* name, Material* material)
	{
		MaterialDataItem* dataItem = new MaterialDataItem();
		strcpy_s(dataItem->id, name);
		dataItem->data = material;

		_materialsHashTable.Insert(dataItem);

		return true;
	}

	unsigned int Resources::GetMaterialCount()
	{
		return _materialsHashTable.GetCount();
	}

	Material* Resources::GetMaterial(unsigned int index)
	{
		return ((MaterialDataItem*)_materialsHashTable.Get(index))->data;
	}

	Material* Resources::GetMaterial(const char* name)
	{
		if (name != NULL)
		{
			MaterialDataItem* dataItem = (MaterialDataItem*)_materialsHashTable.Search(name);
			if (dataItem != NULL)
			{
				return dataItem->data;
			}
		}
		return NULL;
	}

	/* Font Functions */
	bool Resources::AddFont(const char* name, Font* font)
	{
		FontDataItem* dataItem = new FontDataItem();
		strcpy_s(dataItem->id, name);
		dataItem->data = font;

		_fontsHashTable.Insert(dataItem);

		return true;
	}

	unsigned int Resources::GetFontCount()
	{
		return _fontsHashTable.GetCount();
	}

	Font* Resources::GetFont(unsigned int index)
	{
		return ((FontDataItem*)_fontsHashTable.Get(index))->data;
	}

	Font* Resources::GetFont(const char* name)
	{
		if (name != NULL)
		{
			FontDataItem* dataItem = (FontDataItem*)_fontsHashTable.Search(name);
			if (dataItem != NULL)
			{
				return dataItem->data;
			}
		}
		return NULL;
	}

	/* Mesh Functions */
	bool Resources::AddMesh(const char* name, Mesh* font)
	{
		MeshDataItem* dataItem = new MeshDataItem();
		strcpy_s(dataItem->id, name);
		dataItem->data = font;

		_meshHashTable.Insert(dataItem);

		return true;
	}

	unsigned int Resources::GetMeshCount()
	{
		return _meshHashTable.GetCount();
	}

	Mesh* Resources::GetMesh(unsigned int index)
	{
		return ((MeshDataItem*)_meshHashTable.Get(index))->data;
	}

	Mesh* Resources::GetMesh(const char* name)
	{
		if (name != NULL)
		{
			MeshDataItem* dataItem = (MeshDataItem*)_meshHashTable.Search(name);
			if (dataItem != NULL)
			{
				return dataItem->data;
			}
		}
		return NULL;
	}

	/* Setters */
	void Resources::SetRootPath(const char* path) { strcpy_s(_rootPath, path); }

	/* Getters */
	char* Resources::GetRootPath() { return _rootPath; }
}