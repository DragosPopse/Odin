#include <odin/core/SceneManager.hpp>
#include <odin/core/ReverseContainer.hpp>
#include <iostream>

namespace odin
{
	void SceneManager::clear()
	{
		m_pendingChanges.emplace(StackChange::Type::Clear);
	}

	void SceneManager::pop()
	{
		m_pendingChanges.emplace(StackChange::Type::Pop);
	}

	void SceneManager::push(Scene::Ptr scene)
	{
		m_pendingChanges.emplace(StackChange::Type::Push, std::move(scene));
	}

	void SceneManager::dispatchEvent(const Event& ev)
	{
		for (auto& layer : ReverseContainer(m_stack))
		{
			if (layer->getEventMask() & static_cast<uint32_t>(ev.type))
			{
				if (!layer->onEvent(ev))
				{
					break;
				}
			}
		}
	}

	void SceneManager::update(Time dt)
	{
		for (auto& layer : ReverseContainer(m_stack))
		{
			if (!layer->update(dt))
			{
				break;
			}
		}
	}

	void SceneManager::fixedUpdate(Time dt)
	{
		for (auto& layer : ReverseContainer(m_stack))
		{
			if (!layer->fixedUpdate(dt))
			{
				break;
			}
		}
	}

	void SceneManager::draw()
	{
		for (auto& layer : m_stack)
		{
			if (!layer->draw())
			{
				break;
			}
		}
	}

	void SceneManager::applyChanges()
	{
		while (!m_pendingChanges.empty())
		{
			auto& change = m_pendingChanges.front();

			switch (change.type)
			{
			case StackChange::Type::Clear:
				m_stack.clear();
				break;
				
			case StackChange::Type::Push:
				change.layer->m_sceneManager = this;
				m_stack.push_back(std::move(change.layer));
				break;

			case StackChange::Type::Pop:
				m_stack.pop_back();
				break;
			}

			m_pendingChanges.pop();
		}
	}
}