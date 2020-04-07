#ifndef ODIN_EVENT_HPP
#define ODIN_EVENT_HPP

#include <odin/Config.hpp>
#include <odin/window/Keyboard.hpp>
#include <functional>
#include <limits>

namespace odin
{
	class Window;


	struct KeyEvent
	{
		Keyboard::Key code;
	};
	

	struct ResizeEvent
	{
		uint32_t width;
		uint32_t height;
	};


	class Event
	{	
	public:
		enum class Type : uint32_t
		{
			KeyPressed = ODIN_BIT(0),
			KeyReleased = ODIN_BIT(1),
			WindowClosed = ODIN_BIT(2),
			KeyRepeated = ODIN_BIT(3),
			LostFocus = ODIN_BIT(4),
			GainedFocus = ODIN_BIT(5),
			WindowResized = ODIN_BIT(6),
			All = std::numeric_limits<std::underlying_type_t<Type>>::max()
		};


		union
		{
			KeyEvent key;
			ResizeEvent size;
		};

		Window* window;
		Type type;
	};

	using EventCallbackFn = std::function<void(const Event& ev)>;
	
	inline void DefaultEventCallback(const Event&)
	{
		//Empty callback
	}
}

#endif