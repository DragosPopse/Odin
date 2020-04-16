#ifndef ODIN_OPENGL_CONTEXT_HPP
#define ODIN_OPENGL_CONTEXT_HPP

#include <odin/Config.hpp>

#if defined(ODIN_PLATFORM_WINDOWS)
#include <odin/graphics/opengl/wgl/WglContext.hpp>

namespace odin
{
	using OpenglContext = WglContext;
}

#endif

#endif