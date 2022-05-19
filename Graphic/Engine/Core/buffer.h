#pragma once
#include <string>
#include <vector>
#include "base.h"
#include "Math/math.h"

enum class ShaderDataType
{
	None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4, Bool,
};

static uint32_t getShaderDataTypeSize(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::Float:	 return 4;
	case ShaderDataType::Float2: return 4 * 2;
	case ShaderDataType::Float3: return 4 * 3;
	case ShaderDataType::Float4: return 4 * 4;
	case ShaderDataType::Mat3:	 return 4 * 3 * 3;
	case ShaderDataType::Mat4:	 return 4 * 4 * 4;
	case ShaderDataType::Int:	 return 4;
	case ShaderDataType::Int2:	 return 4 * 2;
	case ShaderDataType::Int3:	 return 4 * 3;
	case ShaderDataType::Int4:	 return 4 * 4;
	case ShaderDataType::Bool:   return 1;
	}

	return 0;
}

struct BufferElement
{
	std::string m_Name;
	ShaderDataType m_Type;
	uint32_t m_Offset = 0;
	uint32_t m_Size = 0;
	bool m_Normalized;

	BufferElement() = default;

	BufferElement(const std::string& name, ShaderDataType type, bool normalized = 0)
		: m_Name(name), m_Type(type), m_Normalized(normalized)
	{
		m_Size = getShaderDataTypeSize(type);
	}

	uint32_t getComponentsCount() const
	{
		switch (m_Type)
		{
		case ShaderDataType::Float:	 return 1;
		case ShaderDataType::Float2: return 2;
		case ShaderDataType::Float3: return 3;
		case ShaderDataType::Float4: return 4;
		case ShaderDataType::Mat3:	 return 3;
		case ShaderDataType::Mat4:	 return 4;
		case ShaderDataType::Int:	 return 1;
		case ShaderDataType::Int2:	 return 2;
		case ShaderDataType::Int3:	 return 3;
		case ShaderDataType::Int4:	 return 4;
		case ShaderDataType::Bool:   return 1;
		}

		return 0;
	}
};

class BufferLayout
{
public:
	BufferLayout() = default;

	BufferLayout(std::initializer_list<BufferElement> elements)
		: m_Elements(elements)
	{
		for (auto& element : m_Elements)
		{
			element.m_Offset = m_Stride;
			m_Stride += element.m_Size;
		}
	}
	uint32_t getStride() const { return m_Stride; }
	const std::vector<BufferElement>& getElements() const { return m_Elements; }

	std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
	std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
	std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
private:
	std::vector<BufferElement> m_Elements;
	uint32_t m_Stride = 0;
};

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;
	glm::vec3 tangent;
};

class VertexBuffer
{
public:
	virtual ~VertexBuffer() = default;

	virtual void setData(const void* data, uint32_t size) = 0;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;	

	virtual const BufferLayout& getLayout() const = 0;
	virtual void setLayout(const BufferLayout& layout) = 0;

	static OwnRef<VertexBuffer> create(uint32_t size);
	static OwnRef<VertexBuffer> create(Vertex* vertices, uint32_t size);
	static OwnRef<VertexBuffer> create(const std::vector<Vertex>& vertices);	
};

class IndexBuffer
{
public:
	virtual ~IndexBuffer() = default;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	virtual uint32_t getCount() const = 0;

	static OwnRef<IndexBuffer> create(uint32_t* indices, uint32_t count);
	static OwnRef<IndexBuffer> create(const std::vector<uint32_t>& indices);
};