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

	/*
		Configures initial settings of odin.
	*/
	struct AppInfo
	{
		AppInfo() = default;

		/*
			Display window
		*/
		WindowInfo window;
		/*
			First layer that gets pushed into the stack
		*/
		std::shared_ptr<Layer> entryLayer;
		/*
			OpenGL context settings
		*/
		OpenglContextInfo opengl;
		/*
			Number of times the fixedUpdate() will occur per second
		*/
		uint32_t fixedTicksPerSecond = 60;

		/*
			Stream used for writing logs from withing odin. 
			Should be a global stream.
			Defaults to console.
		*/
		std::ostream* systemLogStream = &std::cout;
	};
}

#endif