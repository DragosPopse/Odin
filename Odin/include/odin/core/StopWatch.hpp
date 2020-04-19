#ifndef ODIN_STOP_WATCH_HPP
#define ODIN_STOP_WATCH_HPP

#include <odin/core/Time.hpp>

namespace odin
{
	template <typename DurationType, typename ClockType = std::chrono::steady_clock>
	class BasicStopWatch
	{
	public:
		BasicStopWatch()
		{
			m_start = ClockType::now();
		}

		~BasicStopWatch() = default;

		DurationType elapsedTime() const
		{
			return ClockType::now() - m_start;
		}

		DurationType restart()
		{
			auto duration = elapsedTime();
			m_start = ClockType::now();
			return duration;
		}

	private:
		typename ClockType::time_point m_start;
	};

	using StopWatch = BasicStopWatch<Time>;
}

#endif