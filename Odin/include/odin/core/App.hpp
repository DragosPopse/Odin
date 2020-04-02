#pragma once

#include <odin/Config.hpp>
#include <odin/window/Window.hpp>
#include <odin/core/AppInfo.hpp>

int main(int argc, char** argv);

namespace odin
{
	class App
	{
	public:
		App() = default;
		virtual ~App() = default;

		void create(const AppInfo& app);

	private:
		void Run();
		
	private:
		friend int ::main(int argc, char** argv);

		Window window;
	};

	App* CreateApp();
}