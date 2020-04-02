#ifndef ODIN_EVENT_HPP
#define ODIN_EVENT_HPP

#include <odin/Config.hpp>

namespace odin
{
	class Window;

	struct KeyPressedEvent
	{

	};

	struct KeyReleasedEvent
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
			KeyPressedEvent keyPressed;
			KeyReleasedEvent keyReleased;
		};

		Window* window;
		Type type;
	};

	using EventCallbackFn = void(*)(const Event& ev);
	
	inline void DefaultEventCallback(const Event& ev)
	{
		//Empty callback
	}
}

#endif