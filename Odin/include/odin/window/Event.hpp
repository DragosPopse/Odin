#ifndef ODIN_EVENT_HPP
#define ODIN_EVENT_HPP

#include <odin/Config.hpp>

namespace odin
{
	struct KeyPressedEvent
	{

	};

	class Event
	{	
	public:
		enum class Type
		{
			KeyPressed,
			KeyReleased,
			WindowClosed
		};

		union
		{

		};

		Type type;
	};
}

#endif