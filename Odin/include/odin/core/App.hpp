#ifndef ODIN_APP_HPP
#define ODIN_APP_HPP

#include <odin/Config.hpp>
#include <odin/window/Window.hpp>
#include <odin/core/AppInfo.hpp>
#include <odin/core/LayerManager.hpp>
#include <odin/graphics/GraphicsContext.hpp>

#include <memory>
#include <odin/debug/Logger.hpp>
#include <odin/core/Time.hpp>

#include <odin/graphics/opengl/OpenglContext.hpp>
#include <odin/graphics/vk/VulkanContext.hpp>
int main(int argc, char** argv);

namespace odin
{
	class App
	{
	public:
		App();
		virtual ~App();

		void create(const AppInfo& app);

		inline Logger& getSystemLogger() { return m_systemLogger; }

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
		Logger m_systemLogger;
		Time m_fixedDeltaTime;

		bool m_running = false;
	};

	App* CreateApp();
}


#endif