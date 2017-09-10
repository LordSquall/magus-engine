#ifndef _VISITABLE_H_
#define _VISITABLE_H_

namespace MagusEngine
{	
	class Visitor;

	class Visitable
	{
	public:
		virtual void Accept(Visitor* visitor) = 0;
	};
}

#endif