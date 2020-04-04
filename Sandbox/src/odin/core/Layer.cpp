#include <odin/core/Layer.hpp>
#include <odin/core/LayerManager.hpp>


namespace odin
{
	void Layer::requestClear()
	{
		m_layerManager->clear();
	}

	void Layer::requestPop()
	{
		m_layerManager->pop();
	}

	void Layer::requestPush(Layer::Ptr layer)
	{
		m_layerManager->push(std::move(layer));
	}
}