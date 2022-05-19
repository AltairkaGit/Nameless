#pragma once
#include <vector>
#include <string>
#include "mesh.h"
#include "Math/math.h"

/** Just contain meshes ids
	which should be drawn
*/
class Model
{
public:
	Model(const std::vector<Mesh>& meshes, glm::vec3 maxPos, glm::vec3 minPos, const std::string& name = "");

	Model(const Model&) = delete;
	Model& operator=(Model&) = delete;

	const std::vector<Mesh>& getMeshes() const { return m_Meshes; }
	const glm::vec3& getMaxPos() const { return m_MaxPos; }
	const glm::vec3& getMinPos() const { return m_MinPos; }
private:
	/** This vectors needs to create octree
		They define min and max position of
		The model in Object Space
	*/
	glm::vec3 m_MaxPos = glm::vec3(HUGE_VALF);
	glm::vec3 m_MinPos = glm::vec3(0.0f);

	std::vector<Mesh> m_Meshes;
	std::string m_Name;

	friend class SceneImporter;
};