#include "MeshPrimitivesManager.h"

MeshPrimitivesManager::MeshPrimitivesManager()
{
	m_Handles.push(m_MaxHandle);
}

const OwnRef<VertexArray>& MeshPrimitivesManager::get(const uint32_t& handle) const
{
	if (m_Map.find(handle) != m_Map.end())
	{
		return m_Map.at(handle);
	}
}

void MeshPrimitivesManager::unload(const uint32_t& handle)
{
	if (m_Map.find(handle) != m_Map.end()) {
		m_Map.erase(handle);
		freeHandle(handle);
	}
}

uint32_t MeshPrimitivesManager::load(const std::vector<Vertex>& vertices, 
	const std::vector<uint32_t>& indices, bool clacTangents = 0)
{
	uint32_t handle = getNextHandle();

	if (calcTangents) calcTangents(const_cast<std::vector<Vertex>&>(vertices), 
		const_cast<std::vector<uint32_t>&>(indices));
	m_Map[handle] = VertexArray::create();
	OwnRef<VertexArray>& data = m_Map[handle];

	OwnRef<VertexBuffer> vbo = VertexBuffer::create(vertices);
	vbo->setLayout({
		{ "iPosition", ShaderDataType::Float3 },
		{ "iNormal",   ShaderDataType::Float3 },
		{ "iTexture",  ShaderDataType::Float2 },
		{ "iTangent",  ShaderDataType::Float3 },
		});
	data->addVertexBuffer(vbo);

	OwnRef<IndexBuffer> ebo = IndexBuffer::create(indices);
	data->setIndexBuffer(ebo);
	data->unbind();

	return handle;
}

uint32_t MeshPrimitivesManager::getNextHandle()
{
	uint32_t handle = m_Handles.back();
	m_Handles.pop();
	if (handle == m_MaxHandle) {
		m_MaxHandle++;
		m_Handles.push(m_MaxHandle);
	}
}

void MeshPrimitivesManager::freeHandle(uint32_t handle)
{
	m_Handles.push(handle);
}

void MeshPrimitivesManager::calcTangents(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices)
{
	for (uint32_t i = 0; i < indices.size(); i += 3)
	{
		//current triangle
		Vertex& v1 = vertices[indices[i]];
		Vertex& v2 = vertices[indices[i + 1]];
		Vertex& v3 = vertices[indices[i + 2]];
		glm::vec3 edge1 = v2.position - v1.position;
		glm::vec3 edge2 = v3.position - v1.position;
		glm::vec2 dUV1 = v2.texture - v1.texture;
		glm::vec2 dUV2 = v3.texture - v1.texture;
		float f = 1.0f / (dUV1.x * dUV2.y - dUV1.y * dUV2.x);
		glm::vec3 tangent;
		tangent.x = f * (dUV2.y * edge1.x - dUV1.y * edge2.x);
		tangent.y = f * (dUV2.y * edge1.y - dUV1.y * edge2.y);
		tangent.z = f * (dUV2.y * edge1.z - dUV1.y * edge2.z);
		tangent = glm::normalize(tangent);
		v1.tangent = tangent;
		v2.tangent = tangent;
		v3.tangent = tangent;
	}
}