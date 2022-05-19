#include "camera.h"

void Camera::setPerspective(float fov, float aspectRatio, float zNear, float zFar)
{
	m_Projection = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
}

void Camera::setOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_Projection = glm::ortho(left, right, bottom, top, zNear, zFar);
}
