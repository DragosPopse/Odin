#include <iostream>
#include <odin/core/Entry.hpp>
#include <odin/core/App.hpp>


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
		create(app);
	}
};


odin::App* odin::CreateApp()
{
	return new Application();
}