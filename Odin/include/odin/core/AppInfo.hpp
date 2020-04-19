#ifndef ODIN_APP_INFO_HPP
#define ODIN_APP_INFO_HPP

#include <odin/Config.hpp>
#include <odin/window/WindowInfo.hpp>
#include <memory>
#include <iostream>

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

		/*
			Stream used for writing logs from withing odin. 
			Should be a global stream.
			Defaults to console.
		*/
		std::ostream* systemLogStream = &std::cout;
	};
}

#endif