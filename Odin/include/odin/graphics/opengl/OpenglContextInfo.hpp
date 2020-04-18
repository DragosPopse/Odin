#ifndef ODIN_OPENGL_CONTEXT_INFO_HPP
#define ODIN_OPENGL_CONTEXT_INFO_HPP

#include <odin/Config.hpp>

namespace odin
{
	struct OpenglContextInfo
	{
		int32_t majorVersion = 3;
		int32_t minorVersion = 3;


		constexpr OpenglContextInfo() = default;
		~OpenglContextInfo() = default;
	};
}

#endif