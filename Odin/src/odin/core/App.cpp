#include <odin/core/App.hpp>
#include <iostream>


namespace odin
{
	App* App::s_instance = nullptr;

	App::App()
	{
		s_instance = this;
	}

	void App::create(const AppInfo& info)
	{
		m_window.create(info.window);
		m_window.setEventCallback(
			[this](const Event& ev)
			{
				m_layerManager.dispatchEvent(ev);
			});

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