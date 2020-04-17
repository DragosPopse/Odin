#ifndef ODIN_APP_INFO_HPP
#define ODIN_APP_INFO_HPP

#include <odin/Config.hpp>
#include <odin/window/WindowInfo.hpp>
#include <memory>

#if defined(ODIN_RENDERAPI_OPENGL)

#endif
#include <odin/graphics/opengl/OpenglContextInfo.hpp>

namespace odin
{
	class Layer;

	struct AppInfo
	{
		WindowInfo window;
		std::shared_ptr<Layer> entryLayer;
		OpenglContextInfo opengl;
	};
}

#endif