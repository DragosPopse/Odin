#include <odin/core/App.hpp>
#include <iostream>


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
		m_window.setEventCallback(
			[this](const Event& ev)
			{
				m_layerManager.dispatchEvent(ev);
			});
		info.window.win32Instance = s_win32Instance;
		m_window.create(info.window);

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
		}
	}
}