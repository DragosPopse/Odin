#ifndef ODIN_EVENT_HPP
#define ODIN_EVENT_HPP

#include <odin/Config.hpp>
#include <odin/window/Keyboard.hpp>
#include <functional>

namespace odin
{
	class Window;


	struct KeyEvent
	{
		Keyboard::Key code;
	};
	
	struct TextEvent
	{

	};


	class Event
	{	
	public:
		enum class Type
		{
			KeyPressed = ODIN_BIT(0),
			KeyReleased = ODIN_BIT(1),
			WindowClosed = ODIN_BIT(2),
			KeyRepeated = ODIN_BIT(3)
		};


		union
		{
			KeyEvent key;
		};

		Window* window;
		Type type;
	};

	using EventCallbackFn = std::function<void(const Event& ev)>;
	
	inline void DefaultEventCallback(const Event& ev)
	{
		//Empty callback
	}
}

#endif