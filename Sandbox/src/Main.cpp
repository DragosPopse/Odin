#include <iostream>
#include <odin/core/Entry.hpp>
#include <odin/core/App.hpp>


class EntryLayer : 
	public odin::Layer
{
public:
	EntryLayer()
	{
		registerEvents(
			odin::Event::Type::KeyPressed, 
			odin::Event::Type::WindowClosed
		);
	}

	bool onEvent(const odin::Event& ev) override
	{
		switch (ev.type)
		{
		case odin::Event::Type::WindowClosed:
			requestClear();
			return false;

		case odin::Event::Type::KeyPressed:
			std::cout << odin::Keyboard::interpretKeyCode(ev.key.code) << '\n';
			return false;
		}

		return true;
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
		app.entryLayer.reset(new EntryLayer());
		create(app);
	}

	
};


odin::App* odin::CreateApp()
{
	return new Application();
}