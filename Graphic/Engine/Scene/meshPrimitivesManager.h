#pragma once
#include <map>
#include <queue>
#include "Core/base.h"
#include "Core/vertexArray.h"

/** Manager to control the lifecycle
	of each mesh primitive
	i.e. vertices and indices arrays
*/
class MeshPrimitivesManager
{
public:
	MeshPrimitivesManager();

	/** Constructs an instance returns 
		a proptietare handle of the
		manager
	*/
	uint32_t load(const std::vector<Vertex>& vertices, 
		const std::vector<uint32_t>& indices, bool clacTangents = 0);

	const OwnRef<VertexArray>& get(const uint32_t& handle) const;
	void unload(const uint32_t& handle);
private:
	/** I use the map class because I
		foresee not so much unique
		instances here(perhaps 20-500)
	*/
	std::map<uint32_t, OwnRef<VertexArray>> m_Map;

	uint32_t getNextHandle();
	void freeHandle(uint32_t handle);
	std::queue<uint32_t> m_Handles;
	uint32_t m_MaxHandle = 0;
private:
	void calcTangents(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
};