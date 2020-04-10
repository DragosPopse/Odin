#include <odin/core/Entry.hpp>
#include <odin/core/App.hpp>


#if defined(ODIN_PLATFORM_WINDOWS)

#include <cstdio>

namespace
{
	void createConsole()
	{
		AllocConsole();
		std::freopen("CONOUT$", "w", stdout);
		std::freopen("CONIN$", "r", stdin);
	}
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, 
	LPSTR pCmdLine,
	int nCmdShow)
{
	createConsole();
	odin::App::s_win32Instance = hInstance;
	auto* app = odin::CreateApp();
	app->Run();
	delete app;
	return 0;
}

#else

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	auto* app = odin::CreateApp();
	app->Run();
	delete app;
	return 0;
}


#endif