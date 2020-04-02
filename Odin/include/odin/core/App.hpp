#pragma once

#include <odin/Config.hpp>
#include <odin/window/Window.hpp>

int main(int argc, char** argv);

namespace odin
{
	class App
	{
	public:
		App() = default;
		virtual ~App() = default;

	private:
		void Run();
		
	private:
		friend int ::main(int argc, char** argv);

		Window window;
	};

	App* CreateApp();
}