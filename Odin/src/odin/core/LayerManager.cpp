#include <odin/core/LayerManager.hpp>
#include <odin/core/ReverseContainer.hpp>
#include <iostream>

namespace odin
{
	void LayerManager::clear()
	{
		m_pendingChanges.emplace(StackChange::Type::Clear);
	}

	void LayerManager::pop()
	{
		m_pendingChanges.emplace(StackChange::Type::Pop);
	}

	void LayerManager::push(Layer::Ptr layer)
	{
		m_pendingChanges.emplace(StackChange::Type::Push, std::move(layer));
	}

	void LayerManager::dispatchEvent(const Event& ev)
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

	void LayerManager::update(Time dt)
	{
		for (auto& layer : ReverseContainer(m_stack))
		{
			if (!layer->update(dt))
			{
				break;
			}
		}
	}

	void LayerManager::fixedUpdate(Time dt)
	{
		for (auto& layer : ReverseContainer(m_stack))
		{
			if (!layer->fixedUpdate(dt))
			{
				break;
			}
		}
	}

	void LayerManager::draw()
	{
		for (auto& layer : m_stack)
		{
			if (!layer->draw())
			{
				break;
			}
		}
	}

	void LayerManager::applyChanges()
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
				change.layer->m_layerManager = this;
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