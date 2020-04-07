#ifndef ODIN_SYSTEM_WINDOW_HPP
#define ODIN_SYSTEM_WINDOW_HPP

#include <queue>
#include <odin/window/Event.hpp>
#include <odin/window/WindowHandle.hpp>
#include <odin/math/Vec2.hpp>

namespace odin
{
	class Window;

	template <typename Derived>
	class SystemWindow
	{
	public:
		SystemWindow(Window* apiWindow, EventCallbackFn eventCallback) :
			m_apiWindow(apiWindow),
			m_onEventCallback(eventCallback)
		{
		}
		~SystemWindow() = default;
		
		void processEvents()
		{
			impl().processEvents();
		}

		WindowHandle getHandle() const
		{
			return impl().getHandle();
		}
		
		Vec2u getSize() const
		{
			return impl().getSize();
		}

	protected:

		Window* m_apiWindow = nullptr;
		EventCallbackFn m_onEventCallback;

	private:
		friend class Window;

		Derived& impl()
		{
			return static_cast<Derived&>(*this);
		}

		const Derived& impl() const
		{
			return static_cast<const Derived&>(*this);
		}
	};
}


#endif
