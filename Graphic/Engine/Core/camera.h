#pragma once
#include "Math/math.h"

enum class MovementDirection { FORWARD, BACK, LEFT, RIGHT, TOP, BOTTOM };

class Camera
{
public:
	Camera() = default;
	Camera(const glm::mat4& projection) : m_Projection(projection) {}
	virtual ~Camera() = default;

	void setPerspective(float fov, float aspectRatio, float zNear = 0.1f, float zFar = 200.0f);
	void setOrtho(float left, float right, float bottom, float top, float zNear = 0.1f, float zFar = 200.0f);
	const glm::mat4& getProjection() { return m_Projection; }
private:
	glm::mat4 m_Projection = glm::mat4(1.0f);
};
