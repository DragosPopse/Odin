#include <odin/core/App.hpp>
#include <iostream>
#include <glad/glad.h>
#include <odin/core/StopWatch.hpp>
#include <vulkan/vulkan.h>
#include <odin/graphics/vk/VulkanContext.hpp>
#include <odin/window/Window.hpp>
#include <odin/graphics/Renderer.hpp>


namespace odin
{
	

	App* App::s_instance = nullptr;

#if defined(ODIN_PLATFORM_WINDOWS)
	HINSTANCE App::s_win32Instance = 0;
#endif

	App::App() :
		m_fixedDeltaTime(1.f / 60.f)
	{
		s_instance = this;
	}

	void App::create(const AppInfo& info)
	{
		ODIN_USE_TIME_LITERALS;


		m_fixedDeltaTime = 1s / static_cast<float>(info.fixedTicksPerSecond);
	
		GraphicsContext::init();

		m_window.setEventCallback(
			[this](const Event& ev)
			{
				m_sceneManager.dispatchEvent(ev);
			});
		info.window.win32Instance = s_win32Instance;
		m_window.create(info.window);
		//uint32_t extensions = 0;
		//vkEnumerateInstanceExtensionProperties(nullptr, &extensions, nullptr);
		//m_systemLogger(Logger::Level::Info, concat(extensions, " Extensions"));

		info.graphics.vulkan.appName = info.name;

		m_graphicsContext.create(m_window, info.graphics);

		Renderer::init();
		std::shared_ptr<Scene> layerPtr(createEntryScene());
		m_sceneManager.push(std::move(layerPtr));
		m_sceneManager.applyChanges();
	}

	void App::Run()
	{
		StopWatch clock;
		Time dt;
		m_running = true;
		while (m_running)
		{
			m_window.processEvents();

			dt = clock.restart();
			m_sceneManager.update(dt);
			while (dt > m_fixedDeltaTime)
			{
				dt -= m_fixedDeltaTime;
				m_sceneManager.fixedUpdate(m_fixedDeltaTime);
			}


			
			Renderer::clear();
			m_sceneManager.draw();
			m_graphicsContext.swapBuffers();

			m_sceneManager.applyChanges();
			if (m_sceneManager.empty())
			{
				m_running = false;
			}
		}
	}

	App::~App()
	{
		m_graphicsContext.destroy();
		m_window.close();
	}
}