#include "scene.h"

Entity Scene::createEntity(const std::string& name = std::string())
{
	Entity entity = { m_Registry.create(), this };
	entity.addComponent<TransformComponent>();
	auto& tag = entity.addComponent<TagComponent>();
	tag.m_Tag = name.empty() ? "Entity" : name;
	return entity;
	
}

void Scene::destroyEntity(Entity entity)
{
	m_Registry.destroy(entity);
}

void Scene::setActiveCamera(CameraComponent* camera)
{
	if (Scene::m_ActiveCameraRef != nullptr)
	{
		Scene::m_ActiveCameraRef->m_IsPrimary = 0;
		CameraComponent::m_MouseOffset.x = 0;
		CameraComponent::m_MouseOffset.y = 0;
		CameraComponent::m_MousePos.x = 0;
		CameraComponent::m_MousePos.y = 0;
	}
	Scene::m_ActiveCameraRef = camera;
	Scene::m_ActiveCameraRef->m_IsPrimary = 1;
}


void Scene::onUpdateEditor(float deltaTime)
{

}

void Scene::onUpdateRuntime(float deltaTime)
{

}

template<class T>
void Scene::onComponentAdded(Entity entity, T& compoennt)
{
	static_assert(false);
}

template<>
void Scene::onComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
{
}

template<>
void Scene::onComponentAdded<TagComponent>(Entity entity, TagComponent& component)
{
}

template<>
void Scene::onComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
{
}

template<>
void Scene::onComponentAdded<ModelComponent>(Entity entity, ModelComponent& component)
{
}

template<>
void Scene::onComponentAdded<PointLightComponent>(Entity entity, PointLightComponent& component)
{
}

template<>
void Scene::onComponentAdded<DirectLightComponent>(Entity entity, DirectLightComponent& component)
{
}

template<>
void Scene::onComponentAdded<FlashLightComponent>(Entity entity, FlashLightComponent& component)
{
}