#include "model.h"

Model::Model(const std::vector<Mesh>& meshes, glm::vec3 maxPos, glm::vec3 minPos, const std::string& name = "")
	: m_Meshes(meshes), m_Name(name), m_MaxPos(maxPos), m_MinPos(minPos)
{
}