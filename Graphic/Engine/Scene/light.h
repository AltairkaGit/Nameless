#pragma once
#include "Math/math.h"
class Light
{
public:
	Light() = default;
	Light(const glm::vec3& col = { 1.0f, 1.0f, 1.0f }, float i = 1.0f);
	glm::vec3 color;
	float intensivity;
};

class PointLight : public Light
{
public:
	PointLight() = default;
	PointLight(const glm::vec3& col = { 1.0f, 1.0f, 1.0f }, const glm::vec3& pos = { 0.0f, 0.0f, 0.0f }, float c = 1.0f, float l = 0.1f, float q = 0.01f, float i = 1.0f);
	glm::vec3 position;
	float quadratic;
	float linear;
	float constant;
};

class DirectLight : public Light
{
public:
	DirectLight() = default;
	DirectLight(const glm::vec3& col = { 1.0f, 1.0f, 1.0f }, const glm::vec3& dir = { 0.0f, -1.0f, 0.0f }, float i = 1.0f);
	glm::vec3 dirrection;
};

class FlashLight : public Light
{
public:
	FlashLight() = default;
	FlashLight(const glm::vec3& col = { 1.0f, 1.0f, 1.0f }, const glm::vec3& pos = { 0.0f, 0.0f, 0.0f }, const glm::vec3& dir = { 0.0f, -1.0f, 0.0f }, float _cutOff = 0.1f, float _outCutOff = 0.8f, float i = 1.0f);
	glm::vec3 dirrection;
	glm::vec3 position;
	float cutOff;
	float outCutOff;
};