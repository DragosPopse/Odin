#include <odin/core/Scene.hpp>
#include <odin/core/SceneManager.hpp>


namespace odin
{
	void Scene::requestClear()
	{
		m_sceneManager->clear();
	}

	void Scene::requestPop()
	{
		m_sceneManager->pop();
	}

	void Scene::requestPush(Scene::Ptr scene)
	{
		m_sceneManager->push(std::move(scene));
	}
}