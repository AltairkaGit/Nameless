#include "camera_system.h"

void CameraSystem::setView(TransformComponent& transform, BasisComponent& basis)
{
	basis.m_View = glm::lookAt(transform.m_Translation, transform.m_Translation + basis.m_Front, basis.m_Up);
}

void CameraSystem::setPerspective(CameraComponent& camera)
{
	camera.m_Camera.setPerspective(camera.m_Fov, CameraComponent::m_AspectRatio);
}

//TODO: create some orthographic component
void CameraSystem::setOrtho(CameraComponent& camera)
{
	camera.m_Camera.setOrtho(-1.0f, 1.0f, -1.0f, 1.0f);
}

void CameraSystem::setBasis(CameraComponent& camera, TransformComponent& transform, BasisComponent& basis)
{
	float& yaw = transform.m_Rotation.z;
	float& pitch = transform.m_Rotation.y;
	basis.m_Front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	basis.m_Front.y = sin(glm::radians(pitch));
	basis.m_Front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	basis.m_Front = glm::normalize(basis.m_Front);
	basis.m_Right = glm::normalize(glm::cross(basis.m_Front, m_Scene->getWorldUp()));
	basis.m_Up = glm::normalize(glm::cross(basis.m_Right, basis.m_Front));
	camera.m_Forward = glm::normalize(glm::cross(m_Scene->getWorldUp(), basis.m_Right));
}

void CameraSystem::onUpdate(float deltaTime)
{
	auto entityManager = m_Scene->getEntityManager();
	auto group = entityManager->group<CameraComponent, TransformComponent, BasisComponent>();

	for (auto entity : group)
	{
		auto [camera, transform, basis] = group.get(entity);
		if (camera.m_IsPrimary)
		{
			setBasis(camera, transform, basis);
			setPerspective(camera);
			setView(transform, basis);
		}

	}
}