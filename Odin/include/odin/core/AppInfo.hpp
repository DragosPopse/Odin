#ifndef ODIN_APP_INFO_HPP
#define ODIN_APP_INFO_HPP

#include <odin/Config.hpp>
#include <odin/window/WindowInfo.hpp>
#include <memory>
#include <iostream>

#if defined(ODIN_RENDERAPI_OPENGL)

#endif
#include <odin/graphics/GraphicsInfo.hpp>

namespace odin
{
	class Layer;

	/*
		Configures initial settings of odin.
	*/
	struct AppInfo
	{
		AppInfo() = default;
		~AppInfo() = default;

		/*
			Name of the application. 
			Should be a ANSI string because it will also be used in initializing Vulkan. 
		*/
		std::string name;

		/*
			Display window
		*/
		WindowInfo window;

		/*
			OpenGL context settings
		*/
		GraphicsInfo graphics;

		/*
			Number of times the fixedUpdate() will occur per second
		*/
		uint32_t fixedTicksPerSecond = 60;

		/*
			String to be used to format library logs. 
		*/
		std::string systemLogFormat = ODIN_STANDARD_LOG_FORMAT;

		/*
			Stream used for writing logs from withing odin. 
			Should be a global stream.
			Defaults to console.
		*/
		std::ostream* systemLogStream = &std::cout;
	};
}

#endif