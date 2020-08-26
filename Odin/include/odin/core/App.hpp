#ifndef ODIN_APP_HPP
#define ODIN_APP_HPP

#include <odin/Config.hpp>
#include <odin/window/Window.hpp>
#include <odin/core/AppInfo.hpp>
#include <odin/core/LayerManager.hpp>
#include <odin/graphics/GraphicsContext.hpp>

#include <memory>
#include <odin/core/Time.hpp>


namespace odin
{
	class App
	{
	public:
		App();
		virtual ~App();

		virtual Layer* createEntryLayer() = 0;

		void create(const AppInfo& app);

		inline static App& get() { return *s_instance; }

	private:
		void Run();
		
	private:
		friend ODIN_MAIN_SIGNATURE;

		static App* s_instance;
		
#if defined(ODIN_PLATFORM_WINDOWS)
		static HINSTANCE s_win32Instance;
#endif

		Window m_window;
		LayerManager m_layerManager;
		GraphicsContext m_graphicsContext;
		Time m_fixedDeltaTime;

		bool m_running = false;
	};

	App* CreateApp();
}


#endif