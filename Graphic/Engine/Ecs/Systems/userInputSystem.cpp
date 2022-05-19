#include "userInputSystem.h"
#include "../Scene/components.h"

void MouseInputSystem::onUpdate(float_t deltaTime)
{
	auto entityManager = m_Scene->getEntityManager();
	//process camera
	auto group = entityManager->group<CameraComponent, TransformComponent, BasisComponent>();
	for (auto& entity : group)
	{
		auto [camera, transform, basis] = group.get(entity);
		if (camera.m_IsPrimary)
		{
			const WindowData& windowData = Renderer::getWindow()->getWindowData();
			glm::vec2 offset(windowData.m_Xoffset, windowData.m_Yoffset);
			offset *= camera.m_Sensivity;
			float& yaw = transform.m_Rotation.z;
			float& pitch = transform.m_Rotation.y;
			yaw += offset.x;
			pitch += offset.y;
		}
	}
}

void KeyboardInputSystem::onUpdate(float_t deltaTime)
{
	auto entityManager = m_Scene->getEntityManager();
	//process keyboard
	auto group = entityManager->group<CameraComponent, TransformComponent, BasisComponent>();
	for (auto& entity : group)
	{
		auto [camera, transform, basis] = group.get(entity);
		if (camera.m_IsPrimary)
		{
			Window* window = Renderer::getWindow();
			const WindowData& windowData = window->getWindowData();
			float velocity = camera.m_MoveSpeed * deltaTime;
			if (Input::isKeyPressed(Escape))
			{
				window->setShouldClose();
			}
			else
			{
				if (Input::isKeyPressed(W))
				{
					transform.m_Translation += camera.m_Forward * velocity;
				}
				if (Input::isKeyPressed(S))
				{
					transform.m_Translation -= camera.m_Forward * velocity;
				}
				if (Input::isKeyPressed(A))
				{
					transform.m_Translation -= basis.m_Right * velocity;
				}
				if (Input::isKeyPressed(D))
				{
					transform.m_Translation += basis.m_Right * velocity;
				}
				if (Input::isKeyPressed(Space))
				{
					transform.m_Translation += m_Scene->getWorldUp() * velocity;
				}
				if (Input::isKeyPressed(LeftShift))
				{
					transform.m_Translation -= m_Scene->getWorldUp() * velocity;
				}
			}
		}
	}
}

