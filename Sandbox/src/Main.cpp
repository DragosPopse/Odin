#include <iostream>
#include <odin/core/Entry.hpp>
#include <odin/core/App.hpp>
#include <glad/glad.h>
#include <odin/debug/Logger.hpp>
#include <fstream>


class EntryLayer : 
	public odin::Layer
{
	odin::Logger m_log;

public:
	EntryLayer()
	{
		registerEvents(
			odin::Event::Type::All
		);
		m_log.setStream(std::cout);
		m_log["tag"] = []() {
			return "gnjergneiugaeirsg";
		};
		m_log.useLocalTime(true);
		m_log.setFormat("[{mday}/{nmon}/{year} {hour}:{min}:{sec}] [{lvl}] {0}");
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
			m_log(odin::Logger::Level::Info, "Pressed");
			return false;

		case odin::Event::Type::WindowResized:
			return false;
		}

		return true;
	}

	bool draw() override
	{
		
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
		app.window.title = L"Odin Testone";
		app.window.style = odin::mask(odin::Window::Style::Overlapped);
		app.entryLayer.reset(new EntryLayer());
		//app.graphics.opengl.majorVersion = 3;
		//app.graphics.opengl.minorVersion = 3;
		create(app);
	}
};


odin::App* odin::CreateApp()
{
	return new Application();
}