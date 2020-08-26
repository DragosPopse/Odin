#ifndef ODIN_LAYER_HPP
#define ODIN_LAYER_HPP

#include <odin/Config.hpp>
#include <odin/window/Event.hpp>
#include <memory>
#include <odin/core/Time.hpp>

namespace odin
{
	class SceneManager;

	class Scene
	{
	public:
		using Ptr = std::shared_ptr<Scene>;

		Scene() = default;
		virtual ~Scene() = default;

		virtual bool onEvent(const Event&) { return true; }
		virtual bool update(Time) { return false; }
		virtual bool fixedUpdate(Time) { return false; }
		virtual bool draw() { return false; }
		
		uint32_t getEventMask() const { return m_eventMask; }

	protected:
		template <typename... Args>
		void registerEvents(Args... args)
		{
			m_eventMask = mask(args...);
		}

		void requestPush(Scene::Ptr layer);
		void requestPop();
		void requestClear();

	private:
		friend class SceneManager;


		SceneManager* m_sceneManager = nullptr;
		uint32_t m_eventMask = 0;
	};
}

#endif