#ifndef ODIN_ENTRY_HPP
#define ODIN_ENTRY_HPP

#include <odin/Config.hpp>
#include <iostream>

namespace odin
{
	class App;
	App* CreateApp();
}

extern odin::App* odin::CreateApp();

#if defined(ODIN_PLATFORM_WINDOWS)

#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow);

#else

int main(int argc, char** argv);

#endif

#endif