#ifndef ODIN_GRAPHICS_CONTEXT_HPP
#define ODIN_GRAPHICS_CONTEXT_HPP

#include <odin/Config.hpp>
#include <odin/graphics/GraphicsInfo.hpp>
#include <odin/window/Window.hpp>


namespace odin
{
	class GraphicsContext
	{
		class Impl; // Vulkan/OpenGL/DirectX

	public:
		GraphicsContext();
		~GraphicsContext();

		void create(Window& window, const GraphicsInfo& info);
		void destroy();
		void swapBuffers();

		static void init();

	private:
		std::unique_ptr<Impl> m_impl;
	};
}


#endif