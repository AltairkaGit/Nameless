#pragma once
#include <vector>
#include <string>
#include "../Math/math.h"
#include "material.h"
#include "../Core/camera.h"
#include "model.h"
#include "light.h"

struct TagComponent
{
	std::string m_Tag;

	TagComponent() = default;
	TagComponent(const TagComponent&) = default;
	TagComponent(const std::string& tag) : m_Tag(tag) 
	{}
};

struct TransformComponent
{
	//position
	glm::vec3 m_Translation = { 0.0f, 0.0f, 0.0f };
	//fov yaw pitch in Euler's angles
	glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_Scale = { 1.0f, 1.0f, 1.0f };

	TransformComponent() = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(const glm::vec3& translation) : m_Translation(translation)
	{}

	glm::mat4 getTransform() const
	{
		glm::mat4 rotationMat = glm::toMat4(glm::quat(m_Rotation));
		return glm::translate(glm::mat4(1.0f), m_Translation)
			* rotationMat
			* glm::scale(glm::mat4(1.0f), m_Scale);
	}
};

struct BasisComponent
{
	glm::vec3 m_Front = { 0.0f, 0.0f, 1.0f };
	glm::vec3 m_Up = { 0.0f, 1.0f, 0.0f };
	glm::vec3 m_Right = {1.0f, 0.0f, 0.0f};
	glm::mat4 m_View = glm::mat4(1.0f);

	BasisComponent() = default;
	BasisComponent(BasisComponent&) = default;
	BasisComponent(const glm::vec3& front, const glm::vec3& up, const glm::vec3& right)
		: m_Front(front), m_Up(up), m_Right(right) {}

	glm::mat4& getView() { return m_View; }
};

struct CameraComponent
{
	Camera m_Camera;
	glm::vec3 m_Forward = { 0.0f, 0.0f, 1.0f };
	float m_MoveSpeed = 8.5f;
	float m_Fov = 45.0f;
	float m_Sensivity = 0.1f;
	bool m_IsCapturedMouse = 0;
	bool m_IsPrimary = 0;

	CameraComponent() = default;
	CameraComponent(const CameraComponent&) = default;
	CameraComponent(const Camera& camera) : m_Camera(camera)
	{}
};

struct ModelComponent
{
	Model m_Model;

	ModelComponent() = default;
	ModelComponent(const ModelComponent&) = default;
	ModelComponent(const Model& model) : m_Model(model)
	{}
};

struct PointLightComponent
{
	PointLight m_Light;

	PointLightComponent() = default;
	PointLightComponent(const PointLightComponent&) = default;
	PointLightComponent(const PointLight& light) : m_Light(light)
	{}
};

struct DirectLightComponent
{
	DirectLight m_Light;

	DirectLightComponent() = default;
	DirectLightComponent(const DirectLightComponent&) = default;
	DirectLightComponent(const DirectLight & light) : m_Light(light)
	{}
};

struct FlashLightComponent
{
	FlashLight m_Light;

	FlashLightComponent() = default;
	FlashLightComponent(const FlashLightComponent&) = default;
	FlashLightComponent(const FlashLight & light) : m_Light(light)
	{}
};


