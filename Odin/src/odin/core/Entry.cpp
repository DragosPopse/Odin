#include <odin/core/Entry.hpp>
#include <odin/core/App.hpp>

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	auto* app = odin::CreateApp();
	app->Run();
	delete app;
	return 0;
}