#ifndef ODIN_ENTRY_HPP
#define ODIN_ENTRY_HPP

#include <odin/Config.hpp>
#include <iostream>

namespace odin
{
	class App;
	class Layer;
	App* createApp();
}

extern odin::App* odin::createApp();

#if defined(ODIN_PLATFORM_WINDOWS)

#include <Windows.h>

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow);

#else

int main(int argc, char** argv);

#endif

#endif