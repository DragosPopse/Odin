#include <odin/core/App.hpp>
#include <iostream>
#include <glad/glad.h>
#include <odin/core/StopWatch.hpp>


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

		m_systemLogger.setStream(*info.systemLogStream);
		m_systemLogger.setFormat(ODIN_STANDARD_LOG_FORMAT);
		m_systemLogger.useLocalTime(true);

		m_fixedDeltaTime = 1s / static_cast<float>(info.fixedTicksPerSecond);

		m_systemLogger(odin::Logger::Level::Debug, concat("Fixed Delta: ", m_fixedDeltaTime.count()));

		OpenglContext::init();

		m_window.setEventCallback(
			[this](const Event& ev)
			{
				m_layerManager.dispatchEvent(ev);
			});
		info.window.win32Instance = s_win32Instance;
		m_window.create(info.window);

		m_systemLogger(odin::Logger::Level::Debug, "Window created");

		m_glContext.create(m_window, info.opengl);
		m_glContext.makeCurrent(m_window);
		m_systemLogger(odin::Logger::Level::Debug, "OpenGL Context created");

		m_layerManager.push(info.entryLayer);
		m_layerManager.applyChanges();
	}

	void App::Run()
	{
		StopWatch clock;
		Time dt;
		while (m_window.isOpen())
		{
			m_window.processEvents();

			dt = clock.restart();
			m_layerManager.update(dt);
			while (dt > m_fixedDeltaTime)
			{
				dt -= m_fixedDeltaTime;
				m_layerManager.fixedUpdate(m_fixedDeltaTime);
			}


			glClearColor(0, 0, 0, 1);
			m_layerManager.draw();
			glClear(GL_COLOR_BUFFER_BIT);
			OpenglContext::swapBuffers(m_window);

			m_layerManager.applyChanges();
			if (m_layerManager.empty())
			{
				m_window.close();
			}
		}
	}
}