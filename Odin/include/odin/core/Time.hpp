#ifndef ODIN_TIME_HPP
#define ODIN_TIME_HPP

#include <odin/Config.hpp>
#include <ctime>
#include <chrono>

#define ODIN_USE_TIME_LITERALS using namespace std::chrono_literals

namespace odin
{
	using Time = std::chrono::duration<float>;
}

#endif