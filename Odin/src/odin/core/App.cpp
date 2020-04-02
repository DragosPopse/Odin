#include <odin/core/App.hpp>
#include <iostream>


namespace odin
{
	void App::create(const AppInfo& info)
	{
		window.create(info.window);
	}

	void App::Run()
	{
		while (window.isOpen())
		{
			window.processEvents();
		}
	}
}