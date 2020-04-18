#include <iostream>
#include <odin/core/Entry.hpp>
#include <odin/core/App.hpp>
#include <glad/glad.h>
#include <odin/debug/Logger.hpp>


class EntryLayer : 
	public odin::Layer
{
	odin::Logger log;

public:
	EntryLayer()
	{
		registerEvents(
			odin::Event::Type::All
		);
		log.setStream(std::cout);
		log["code"] = []()->std::string {
			return "mycode";
		};
		log.setFormat("{1}  {code} {2}");
		log(odin::Logger::Level::Debug, "World", "Hello");
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
			std::cout << "Pressed" << '\n';
			return false;

		case odin::Event::Type::WindowResized:
			glViewport(0, 0, ev.size.width, ev.size.height);
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
		app.window.width = 600;
		app.window.height = 600;
		app.window.title = L"Odin Testone";
		app.window.style = odin::mask(odin::Window::Style::Overlapped);
		app.entryLayer.reset(new EntryLayer());
		app.opengl.majorVersion = 3;
		app.opengl.minorVersion = 3;
		create(app);
		glViewport(0, 0, app.window.width, app.window.height);
	}
};


odin::App* odin::CreateApp()
{
	return new Application();
}