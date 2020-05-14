#include <odin/graphics/opengl/OpenglRenderer.hpp>
#include <iostream>

namespace odin
{
	uint32_t Renderer::Impl::s_quadVAO = 0;
	uint32_t Renderer::Impl::s_quadEBO = 0;
	uint32_t Renderer::Impl::s_quadVBO = 0;


	void Renderer::Impl::init()
	{
		float vertices[]{
			-0.5f, 0.5f, 0.f,
			-0.5f, -0.5f, 0.f,
			0.5f, -0.5f, 0.f,
			0.5f, 0.5f, 0.f
		};
		uint32_t indices[]{
			0, 1, 2,
			0, 2, 3
		};
		glGenVertexArrays(1, &s_quadVAO);
		glGenBuffers(1, &s_quadVBO);
		glGenBuffers(1, &s_quadEBO);

		glBindVertexArray(s_quadVAO);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, s_quadVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_quadEBO);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	}


	void Renderer::Impl::draw()
	{
		glBindVertexArray(s_quadVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}


	void Renderer::Impl::destroy()
	{
		glDeleteVertexArrays(1, &s_quadVAO);
		glDeleteBuffers(1, &s_quadVBO);
		glDeleteBuffers(1, &s_quadEBO);
	}


	void Renderer::Impl::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}


	void Renderer::Impl::setClearColor(const Color& color)
	{
		glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
	}
}