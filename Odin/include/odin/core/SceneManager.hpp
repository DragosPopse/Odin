#ifndef ODIN_LAYER_MANAGER_HPP
#define ODIN_LAYER_MANAGER_HPP

#include <memory>
#include <odin/core/Scene.hpp>
#include <odin/window/Event.hpp>
#include <vector>
#include <queue>

namespace odin
{
	class SceneManager
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

			Scene::Ptr layer;
			StackChange::Type type;

			StackChange(StackChange::Type changeType, Scene::Ptr changedLayer = nullptr) :
				layer(changedLayer),
				type(changeType)
			{
			}
		};

		SceneManager() = default;
		~SceneManager() = default;

		void push(Scene::Ptr layer);
		void pop();
		void clear();

		bool empty() const { return m_stack.empty(); }

		void applyChanges();

		void update(Time dt);
		void fixedUpdate(Time dt);
		void draw();

		void dispatchEvent(const Event& ev);
		
	private:
		std::vector<Scene::Ptr> m_stack;
		std::queue<StackChange> m_pendingChanges;
	};
}

#endif