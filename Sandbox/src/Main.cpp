﻿#include <iostream>
#include <odin/core/Entry.hpp>
#include <odin/core/App.hpp>
#include <glad/glad.h>
#include <fstream>
#include <odin/graphics/Renderer.hpp>
#include <odin/graphics/Shader.hpp>
#include <gmath/mat.hpp>
#include <gmath/vec.hpp>
#include <odin/graphics/Texture.hpp>
#include <odin/core/Time.hpp>
#include <odin/core/StopWatch.hpp>

ODIN_USE_TIME_LITERALS;

template <size_t ROWS, size_t COLS, typename T>
void printMat(const gm::Mat<T, ROWS, COLS>& mat)
{
	for (size_t i = 0; i < mat.rows; i++)
	{
		for (size_t j = 0; j < mat.columns; j++)
		{
			std::cout << mat[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

template <size_t SIZE, typename T>
void printVec(const gm::Vec<T, SIZE>& vec)
{
	for (size_t i = 0; i < vec.size; i++)
	{
		std::cout << vec[i] << ' ';
	}
	std::cout << '\n';
}

class EntryLayer : 
	public odin::Scene
{
	odin::VertexBuffer m_vb;
	odin::Shader m_shader;
	odin::Texture m_texture;
	odin::Time m_elapsedTime = 0s;

public:
	EntryLayer()
	{
		registerEvents(
			odin::Event::Type::All
		);

		m_shader.loadFromFile("assets/shader.vert", odin::Shader::Type::Vertex);
		m_shader.loadFromFile("assets/shader.frag", odin::Shader::Type::Fragment);
		m_shader.link();
		odin::Renderer::setClearColor(odin::Color(0, 124, 124, 255));

		m_texture.loadFromFile("assets/sstest.png");
		m_texture.bind();
		
		//m_log(odin::Logger::Level::Debug, v2[1]);
		
	}

	bool onEvent(const odin::Event& ev) override
	{
		switch (ev.type)
		{
		case odin::Event::Type::WindowClosed:
			requestClear();
			return false;

		case odin::Event::Type::KeyRepeated:
		case odin::Event::Type::KeyPressed:
			return false;

		case odin::Event::Type::WindowResized:
			return false;
		}

		return true;
	}


	bool update(odin::Time time) override
	{ 
		m_elapsedTime += time;
		return true;
	}


	bool draw() override
	{
		gm::Mat4f transform({ {
			{0.5f, 0.f, 0.f, 0.3f},
			{0.f, 0.5f, 0.f, 0.f},
			{0.f, 0.f, 1.f, 0},
			{0.f, 0.f, 0.f, 1.f}
		} });

		gm::Vec4f texTransform(0.f, 0.f, 0.5f, 1.f);
		m_shader.bind();
		m_texture.bind();
		m_shader.setMat4("u_Transform", transform);
		m_shader.setVec4("u_TexTransform", texTransform);
		m_shader.setFloat("u_ElapsedTime", m_elapsedTime.count());
		odin::Renderer::draw();
		return false;
	}
};


class Application :
	public odin::App
{
public:
	Application()
	{
		odin::AppInfo app;
		app.name = "Sandbox";
		app.window.width = 600;
		app.window.height = 600;
		app.window.title = L"ᚠ ᚡ ᚢ ᚣ ᚤ ᚥ ᚦ ᚧ ᚨ ᚩ";
		app.window.style = odin::mask(odin::Window::Style::Overlapped);
		//app.graphics.opengl.majorVersion = 3;
		//app.graphics.opengl.minorVersion = 3;
		create(app);
	}

	odin::Scene* createEntryScene() final
	{
		return new EntryLayer();
	}
};


odin::App* odin::createApp()
{
	return new Application();
}