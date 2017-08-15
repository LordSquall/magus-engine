#ifndef _INPUT_CLASS_H_
#define _INPUT_CLASS_H_

namespace ElementaEngine
{
	class InputClass
	{
	public:
		InputClass();
		
		void Initialise();

		void KeyDown(unsigned int);
		void KeyUp(unsigned int);

		bool IsKeyDown(unsigned int);

	private:
		bool m_keys[256];
	};
}

#endif