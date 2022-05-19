#pragma once
#include <vector>
#include "Core/base.h"
#include "Math/math.h"

struct SceneNode
{
	std::vector<uint32_t> children;
	uint32_t model;
	glm::mat4 trs = glm::mat4(1.0f);
};
