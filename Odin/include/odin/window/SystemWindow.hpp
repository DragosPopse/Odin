#ifndef ODIN_SYSTEM_WINDOW_HPP
#define ODIN_SYSTEM_WINDOW_HPP

#include <queue>
#include <odin/window/Event.hpp>
#include <odin/window/WindowHandle.hpp>

namespace odin
{
	template <typename Derived>
	class SystemWindow
	{
	public:
		SystemWindow() = default;
		~SystemWindow() = default;
		
		bool pollEvent(Event& ev)
		{
			if (m_eventQueue.empty())
			{
				processEvents();
			}

			if (m_eventQueue.empty())
			{
				return false;
			}
			ev = m_eventQueue.front();
			m_eventQueue.pop();
			return true;
		}

		WindowHandle getHandle() const
		{
			return static_cast<const Derived&>(*this).getHandle();
		}

	protected:
		void pushEvent(const odin::Event& ev)
		{
			m_eventQueue.push(ev);
		}

		void processEvents()
		{
			static_cast<Derived&>(*this).processEvents();
		}

	private:
		std::queue<Event> m_eventQueue;
	};
}


#endif
