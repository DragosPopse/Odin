#ifndef ODIN_SYSTEM_WINDOW_HPP
#define ODIN_SYSTEM_WINDOW_HPP

#include <queue>
#include <odin/window/Event.hpp>
#include <odin/window/WindowHandle.hpp>

namespace odin
{
	class Window;

	template <typename Derived>
	class SystemWindow
	{
	public:
		SystemWindow(Window* apiWindow) :
			m_apiWindow(apiWindow)
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

		void setEventCallback(EventCallbackFn callback)
		{
			m_onEventCallback = callback;
		}



	protected:
		void pushEvent(const odin::Event& ev)
		{
			m_eventQueue.push(ev);
		}

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
