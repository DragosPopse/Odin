#include <iostream>
#include <odin/window/Window.hpp>

int main()
{
	
	odin::Window window(800, 600);


	while (window.isOpen())
	{
		odin::Event ev;

		while (window.pollEvent(ev))
		{
			switch (ev.type)
			{
			case odin::Event::Type::WindowClosed:
				window.close();
				break;
			}
		}
	}

	return 0;
}