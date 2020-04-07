#pragma once

#include <odin/Config.hpp>
#include <odin/window/Window.hpp>
#include <odin/core/AppInfo.hpp>
#include <odin/core/LayerManager.hpp>
#include <memory>

int main(int argc, char** argv);

namespace odin
{
	class App
	{
	public:
		App();
		virtual ~App() = default;

		void create(const AppInfo& app);

		inline static App& get() { return *s_instance; }

	private:
		void Run();
		
	private:
		friend ODIN_MAIN_SIGNATURE;

		static App* s_instance;

		Window m_window;
		LayerManager m_layerManager;
	};

	App* CreateApp();
}