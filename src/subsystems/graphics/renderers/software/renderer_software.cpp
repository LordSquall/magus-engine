#include "renderer_software.h"

namespace MagusEngine
{
	Renderer_Software::Renderer_Software(FrameworkConfig* config)
	{
		/* Allocate memory for vbos (KB)*/
		_vboMemoryPool = (Vertex*)malloc(sizeof(Vertex) * config->sr_vbo_memorylimit );
		
		if (_vboMemoryPool == NULL)
		{
			LOGERROR("Unable to allocated memory of  %d Bytes for Software Renderer vbo memory pool", sizeof(Vertex) * config->sr_vbo_memorylimit);
		}
		else
		{
			LOGINFO("Software Renderer allocated %d Bytes of vbo memory pool [%d Vertices]", sizeof(Vertex) * config->sr_vbo_memorylimit, config->sr_vbo_memorylimit);
		}

		_vboMemoryPoolLimit = config->sr_vbo_memorylimit;
		_vboMemoryPoolUsed = 0;


		/* Allocate memory for ibos (KB)*/
		_iboMemoryPool = (unsigned int*)malloc(sizeof(unsigned int) * config->sr_ibo_memorylimit);

		if (_iboMemoryPool == NULL)
		{
			LOGERROR("Unable to allocated memory of  %d Bytes for Software Renderer ibo memory pool", sizeof(unsigned int) * config->sr_ibo_memorylimit);
		}
		else
		{
			LOGINFO("Software Renderer allocated %d Bytes of ibo memory pool [%d Indices]", sizeof(unsigned int) * config->sr_ibo_memorylimit, config->sr_ibo_memorylimit);
		}

		_iboMemoryPoolLimit = config->sr_ibo_memorylimit;
		_iboMemoryPoolUsed = 0;

		/* Allocate vbo table */
		_vboMemoryTable = (MemoryBuffer*)malloc(sizeof(MemoryBuffer) * (config->sr_vbo_limit));

		if (_vboMemoryTable == NULL)
		{
			LOGERROR("Unable to allocated memory of %d Bytes for Software Renderer vbo memory table", sizeof(MemoryBuffer) * (config->sr_vbo_limit));
		}
		else
		{
			LOGINFO("Software Renderer allocated %d Bytes of ibo memory table [%d Memory Blocks]", sizeof(MemoryBuffer) * (config->sr_vbo_limit), config->sr_vbo_limit);
		}

		_vboMemoryTableLimit = config->sr_vbo_limit;
		_vboMemoryTableUsed = 0;
		
		/* Allocate ibo table */
		_iboMemoryTable = (MemoryBuffer*)malloc(sizeof(MemoryBuffer) * (config->sr_ibo_limit));

		if (_iboMemoryTable == NULL)
		{
			LOGERROR("Unable to allocated memory of %d Bytes for Software Renderer ibo memory table", sizeof(MemoryBuffer) * (config->sr_ibo_limit));
		}
		else
		{
			LOGINFO("Software Renderer allocated %d Bytes of ibo memory table [%d Memory Blocks]", sizeof(MemoryBuffer) * (config->sr_ibo_limit), config->sr_ibo_limit);
		}

		_iboMemoryTableLimit = config->sr_ibo_limit;
		_iboMemoryTableUsed = 0;
	}

	bool Renderer_Software::Initialise(void* system, int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync)
	{
		/* Set class variables */
		_screenSizeWidth = screenWidth;
		_screenSizeHeight = screenHeight;
		_screenPixelDepth = screenDepth;

		/* Allocate data for front buffer */
		_framebuffer.Initialise(screenWidth, screenHeight, screenDepth);

		/* Initialise the scane buffer */
		_scanbuffer.Initialise(screenWidth, screenHeight, &_framebuffer);

		return true;
	}
	
	void Renderer_Software::Shutdown()
	{
	}

	void Renderer_Software::DrawRectangle(int x, int y, int width, int height)
	{
		
	}

	void Renderer_Software::BeginScene(float red, float green, float blue, float alpha)
	{
		_framebuffer.Clear(red, green, blue, alpha);

		return;
	}
	
	void Renderer_Software::EndScene()
	{
		
		//_debugBitmap.Save((BYTE*)_framebuffer.GetData(), 32, 24, "C:\\Temp\\image.bmp");
		return;
	}
	
	void Renderer_Software::CheckError()
	{
	}

	/* Data Loading API */
	unsigned int Renderer_Software::GenerateVertexBuffer(Vertex* vertices, VBO_Structure* vbodata)
	{
		unsigned int vbohandle = 0;

		/* Check to ensure there is enought memory left in pool to allocate table entry and pool resources */
		if (_vboMemoryTableUsed > _vboMemoryTableLimit)
		{
			LOGERROR("VBO Table Limit reached. Unable to allocate vertex buffer");
			return 0;
		}

		if ((_vboMemoryPoolUsed + vbodata->vertexlength) > _vboMemoryPoolLimit)
		{
			LOGERROR("VBO Memory Pool Limit reached. Unable to allocate vertex buffer");
		}

		/* Get next slot in the vbo table */
		MemoryBuffer* vbo = &_vboMemoryTable[_vboMemoryTableUsed];

		/* store start and end pointers to memory buffer */
		vbo->start = &_vboMemoryPool[_vboMemoryPoolUsed];
		vbo->end = &_vboMemoryPool[_vboMemoryPoolUsed] + (sizeof(Vertex) * vbodata->vertexlength);

		/* Copy data into vbo memory */
		memcpy(vbo->start, vertices, sizeof(Vertex) * vbodata->vertexlength);

		/* Store vbo memory handle */
		vbohandle = _vboMemoryTableUsed;

		/* Increment the pool and table usage, Use max incase of later updates to data */
		_vboMemoryPoolUsed += vbodata->vertexmax;
		LOGINFO("VBO Memory Pool allocation: %d vertices used %d vertices remaining", _vboMemoryPoolUsed, _vboMemoryPoolLimit - _vboMemoryPoolUsed);

		_vboMemoryTableUsed++;
		LOGINFO("VBO Table allocation: %d entries remaining", _vboMemoryTableLimit - _vboMemoryTableUsed);

		return vbohandle;
	}

	unsigned int Renderer_Software::GenerateIndicesBuffer(unsigned int* indices, VBO_Structure* vbodata)
	{
		unsigned int ibohandle = 0;


		/* Check to ensure there is enought memory left in pool to allocate table entry and pool resources */
		if (_iboMemoryTableUsed > _iboMemoryTableLimit)
		{
			LOGERROR("IBO Table Limit reached. Unable to allocate index buffer");
			return 0;
		}

		if ((_iboMemoryPoolUsed + vbodata->indexlength) > _iboMemoryPoolLimit)
		{
			LOGERROR("IBO Memory Pool Limit reached. Unable to allocate index buffer");
		}

		/* Get next slot in the ibo table */
		MemoryBuffer* ibo = &_iboMemoryTable[_iboMemoryTableUsed];

		/* store start and end pointers to memory buffer */
		ibo->start = &_iboMemoryPool[_iboMemoryPoolUsed];
		ibo->end = &_iboMemoryPool[_iboMemoryPoolUsed] + (sizeof(unsigned int) * vbodata->indexlength);

		/* Copy data into ibo memory */
		memcpy(ibo->start, indices, sizeof(unsigned int) * vbodata->indexlength);

		/* Store ibo memory handle */
		ibohandle = _iboMemoryTableUsed;

		/* Increment the pool and table usage use max incase of later updates to data */
		_iboMemoryPoolUsed += vbodata->indexmax;
		LOGINFO("IBO Memory Pool allocation: %d indices used %d indices remaining", _iboMemoryPoolUsed, _iboMemoryPoolLimit - _iboMemoryPoolUsed);

		_iboMemoryTableUsed++;
		LOGINFO("IBO Table allocation: %d entries remaining", _iboMemoryTableLimit - _iboMemoryTableUsed);

		return ibohandle;
	}

	unsigned int Renderer_Software::UpdateVertexBuffer(VBO_Structure* bufferData, Vertex* vertices, unsigned int vertexStart, unsigned int vertexCount)
	{
		/* Get next slot in the vbo table */
		MemoryBuffer* vbo = &_vboMemoryTable[bufferData->vertexhandle];

		/* Copy data into vbo memory */
		memcpy(vbo->start, vertices, sizeof(Vertex) * vertexCount);

		return bufferData->vertexhandle;
	}

	unsigned int Renderer_Software::UpdateIndicesBuffer(VBO_Structure* bufferData, unsigned int* indices, unsigned int indicesStart, unsigned int indicesCount)
	{
		/* Get next slot in the ibo table */
		MemoryBuffer* ibo = &_iboMemoryTable[bufferData->indexhandle];

		/* Copy data into ibo memory */
		memcpy(ibo->start, indices, sizeof(unsigned int) * indicesCount);

		return bufferData->indexhandle;
	}


	unsigned int Renderer_Software::DrawBuffers(VBO_Structure* bufferData, RenderDrawCallType type)
	{

		Matrix4f mvp = (*_projectionMatix) * (*_modelMatrix);

		/* Get vbo structure */
		MemoryBuffer* vboMemoryBuffer = &_vboMemoryTable[bufferData->vertexhandle];
		Vertex* vertices = (Vertex*)vboMemoryBuffer->start;

		/* Get ibo structure */
		MemoryBuffer* iboMemoryBuffer = &_iboMemoryTable[bufferData->indexhandle];
		unsigned int* indicies = (unsigned int*)iboMemoryBuffer->start;

		/* Render each triangle */
		for (unsigned int i = 0; i < bufferData->indexlength; i+=3)
		{
			unsigned int indexa = (*(indicies + i));
			unsigned int indexb = (*(indicies + i + 1));
			unsigned int indexc = (*(indicies + i + 2));
			_scanbuffer.FillTriangle(vertices[indexa].Transform(mvp), vertices[indexb].Transform(mvp), vertices[indexc].Transform(mvp), _CurrentMaterial, _CurrentTexture);
		}

		return 0;
	}

	void Renderer_Software::SetCurrentModelMatrix(Matrix4f* matrix)
	{
		_modelMatrix = matrix;
		return;
	}

	void Renderer_Software::SetCurrentProjectionMatrix(Matrix4f* matrix)
	{
		_projectionMatix = matrix;
	}

	void Renderer_Software::SetCurrentViewMatrix(Matrix4f* matrix)
	{

	}

	void Renderer_Software::SetMaterial(Material* material)
	{
		/* Set the Current Material */
		_CurrentMaterial = material;

		/* TODO Color Map */

		/* Set the texture */
		SetTexture(material->GetTexture());

		return;
	}

	void Renderer_Software::SetTexture(Texture* texture)
	{
		/* Set the Current Texture */
		_CurrentTexture = texture;


		return;
	}

	/* Shader API */
	void Renderer_Software::CompileShaderObject(Shader* shader)
	{
		return;
	}

	void Renderer_Software::SetCurrentShader(Shader* shader)
	{
		return;
	}

	/* Texture API */
	void Renderer_Software::CreateTexture(Texture* texture)
	{

	}


	/* Filter API */
	void Renderer_Software::ActivateFilter(VBO_Structure* bufferData)
	{

	}

	void Renderer_Software::DeactivateFilter(VBO_Structure* bufferData)
	{

	}

	void Renderer_Software::SaveBitmap()
	{
		
	}


	Byte* Renderer_Software::GetFramebufferData()
	{
		return _framebuffer.GetData();
	}
}