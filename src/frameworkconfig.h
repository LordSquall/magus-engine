#ifndef _FRAMEWORKCONFIG_H_
#define _FRAMEWORKCONFIG_H_

namespace MagusEngine
{	
	typedef struct FrameworkConfig
	{
		char title[25];
		int width;
		int height;

		unsigned int sr_vbo_memorylimit;
		unsigned int sr_ibo_memorylimit;
		unsigned int sr_vbo_limit;
		unsigned int sr_ibo_limit;
	}FrameworkConfig;
}

#endif