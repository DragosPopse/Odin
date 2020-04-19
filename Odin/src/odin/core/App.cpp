#include <odin/core/App.hpp>
#include <iostream>
#include <glad/glad.h>


namespace odin
{


	App* App::s_instance = nullptr;

#if defined(ODIN_PLATFORM_WINDOWS)
	HINSTANCE App::s_win32Instance = 0;
#endif

	App::App()
	{
		s_instance = this;
	}

	void App::create(const AppInfo& info)
	{
		m_systemLogger.setStream(*info.systemLogStream);
		m_systemLogger.setFormat(ODIN_STANDARD_LOG_FORMAT);
		m_systemLogger.useLocalTime(true);
		OpenglContext::init();
		m_window.setEventCallback(
			[this](const Event& ev)
			{
				m_layerManager.dispatchEvent(ev);
			});
		info.window.win32Instance = s_win32Instance;
		m_window.create(info.window);
		m_systemLogger(odin::Logger::Level::Info, "Window created");

		m_glContext.create(m_window, info.opengl);
		m_glContext.makeCurrent(m_window);
		m_systemLogger(odin::Logger::Level::Info, "OpenGL Context created");

		m_layerManager.push(info.entryLayer);
		m_layerManager.applyChanges();
	}

	void App::Run()
	{
		while (m_window.isOpen())
		{
			m_window.processEvents();

			m_layerManager.applyChanges();

			if (m_layerManager.empty())
			{
				m_window.close();
			}

			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			OpenglContext::swapBuffers(m_window);
		}
	}
}