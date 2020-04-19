#ifndef ODIN_LAYER_MANAGER_HPP
#define ODIN_LAYER_MANAGER_HPP

#include <memory>
#include <odin/core/Layer.hpp>
#include <odin/window/Event.hpp>
#include <vector>
#include <queue>

namespace odin
{
	class LayerManager
	{
	public:
		struct StackChange
		{
			enum class Type
			{
				Push,
				Pop,
				Clear
			};

			Layer::Ptr layer;
			StackChange::Type type;

			StackChange(StackChange::Type changeType, Layer::Ptr changedLayer = nullptr) :
				layer(changedLayer),
				type(changeType)
			{
			}
		};

		LayerManager() = default;
		~LayerManager() = default;

		void push(Layer::Ptr layer);
		void pop();
		void clear();

		bool empty() const { return m_stack.empty(); }

		void applyChanges();

		void update(Time dt);
		void fixedUpdate(Time dt);
		void draw();

		void dispatchEvent(const Event& ev);
		
	private:
		std::vector<Layer::Ptr> m_stack;
		std::queue<StackChange> m_pendingChanges;
	};
}

#endif