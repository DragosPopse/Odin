#include <iostream>
#include <odin/core/Entry.hpp>
#include <odin/core/App.hpp>


class Application :
	public odin::App
{
public:
	Application()
	{
		std::cout << "ENTRY\n";
	}
};


odin::App* odin::CreateApp()
{
	return new Application();
}