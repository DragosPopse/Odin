#include <odin/graphics/Renderer.hpp>


#if defined(ODIN_RENDERAPI_OPENGL)

#include <odin/graphics/opengl/OpenglRenderer.hpp>

#endif


namespace odin
{
	void Renderer::init()
	{
		Impl::init();
	}


	void Renderer::draw()
	{
		Impl::draw();
	}



	void Renderer::clear()
	{
		Impl::clear();
	}


	void Renderer::setClearColor(const Color& color)
	{
		Impl::setClearColor(color);
	}
}