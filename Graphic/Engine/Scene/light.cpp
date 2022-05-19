#include "light.h"

Light::Light(const glm::vec3& col, float i)
{
	color = col;
	intensivity = i;
}

PointLight::PointLight(const glm::vec3& col, const glm::vec3& pos, float c, float l, float q, float i)
	: Light(col, i)
{
	position = pos;
	quadratic = q;
	linear = l;
	constant = c;
}

DirectLight::DirectLight(const glm::vec3& col, const glm::vec3& dir, float i)
	: Light(col, i)
{
	dirrection = dir;
}

FlashLight::FlashLight(const glm::vec3& col, const glm::vec3& pos, const glm::vec3& dir, float _cutOff, float _outCutOff, float i)
	: Light(col, i)
{
	dirrection = dir;
	position = pos;
	outCutOff = _outCutOff;
	cutOff = _cutOff;
}
