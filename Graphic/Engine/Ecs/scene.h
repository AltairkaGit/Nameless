#pragma once
#include <vector>
#include <string>
#include "Math/math.h"
#include "components.h"
#include "entt.hpp"
#include "material.h"
#include "entity.h"
#include "model.h"
#include "light.h"


//make it class Entity manager
class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	Entity createEntity(const std::string& name = std::string());
	void destroyEntity(Entity entity);

	template<class... Args>
	entt::registry* const getEntityManager() { return &m_Registry; }

	void onUpdateRuntime(float deltaTime);
	void onUpdateEditor(float deltaTime);

	const glm::vec3& getWorldUp() { return m_WorldUp; }
	static void setActiveCamera(CameraComponent* camera);
public:
	static CameraComponent* m_ActiveCameraRef;
private:
	template<class T>
	void onComponentAdded(Entity entity, T& compoennt);

private:
	entt::registry m_Registry;
	glm::vec3 m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	friend class Entity;
};
