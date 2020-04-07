#ifndef ODIN_LAYER_HPP
#define ODIN_LAYER_HPP

#include <odin/Config.hpp>
#include <odin/window/Event.hpp>
#include <memory>

namespace odin
{
	class LayerManager;

	class Layer
	{
	public:
		using Ptr = std::shared_ptr<Layer>;

		Layer() = default;
		virtual ~Layer() = default;

		virtual bool onEvent(const Event& ev) { return true; }
		
		uint32_t getEventMask() const { return m_eventMask; }

	protected:
		template <typename... Args>
		void registerEvents(Args... args)
		{
			m_eventMask = mask(args...);
		}

		void requestPush(Layer::Ptr layer);  
		void requestPop();
		void requestClear();

	private:
		friend class LayerManager;


		LayerManager* m_layerManager = nullptr;
		uint32_t m_eventMask = 0;
	};
}

#endif