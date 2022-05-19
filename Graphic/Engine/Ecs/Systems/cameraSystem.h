#pragma once
#include "../Math/math.h"
#include "../Scene/components.h"
#include "../Scene/scene.h"

struct CameraSystem
{
public:
	CameraSystem() = default;
	CameraSystem(CameraSystem&) = delete;
	CameraSystem(Scene* scene) : m_Scene(scene) {}
	
	void setView(TransformComponent& transform, BasisComponent& basis);
	void setBasis(CameraComponent& camera, TransformComponent& transform, BasisComponent& basis);
	void setView(TransformComponent& transform, BasisComponent& basis);
	void setPerspective(CameraComponent& camera);
	void setOrtho(CameraComponent& camera);
	void onUpdate(float deltaTime);
private:
	Scene* m_Scene;
};