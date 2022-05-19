#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace VertexArrayUtils
{
	static GLenum getOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:	 return GL_FLOAT;
		case ShaderDataType::Float2: return GL_FLOAT;
		case ShaderDataType::Float3: return GL_FLOAT;
		case ShaderDataType::Float4: return GL_FLOAT;
		case ShaderDataType::Mat3:	 return GL_FLOAT;
		case ShaderDataType::Mat4:	 return GL_FLOAT;
		case ShaderDataType::Int:	 return GL_INT;
		case ShaderDataType::Int2:	 return GL_INT;
		case ShaderDataType::Int3:	 return GL_INT;
		case ShaderDataType::Int4:	 return GL_INT;
		case ShaderDataType::Bool:   return GL_BOOL;
		}
		return 0;
	}
}

OpenGLVertexArray::OpenGLVertexArray()
{
	glCreateVertexArrays(1, &m_RendererId);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	glDeleteVertexArrays(1, &m_RendererId);
}

void OpenGLVertexArray::bind() const
{
	glBindVertexArray(m_RendererId);
}

void OpenGLVertexArray::unbind() const
{
	glBindVertexArray(0);
}

void OpenGLVertexArray::addVertexBuffer(const OwnRef<VertexBuffer>& vertexBuffer)
{
	const auto& layout = vertexBuffer->getLayout();
	if (!layout.getElements().size())
	{
		std::cout << "buffes has no layout" << '\n';
		return;
	}

	glBindVertexArray(m_RendererId);
	vertexBuffer->bind();

	for (auto& element : layout)
	{
		switch (element.m_Type)
		{
		case ShaderDataType::Float:	 
		case ShaderDataType::Float2: 
		case ShaderDataType::Float3: 
		case ShaderDataType::Float4:
		{
			glEnableVertexAttribArray(m_vertexBufferIndex);
			glVertexAttribPointer(m_vertexBufferIndex,
				element.getComponentsCount(),
				VertexArrayUtils::getOpenGLBaseType(element.m_Type),
				element.m_Normalized ? 1 : 0,
				layout.getStride(),
				(const void*)element.m_Offset
			);
			m_vertexBufferIndex++;
			break;
		}		
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
		case ShaderDataType::Bool:
		{
			glEnableVertexAttribArray(m_vertexBufferIndex);
			glVertexAttribIPointer(m_vertexBufferIndex,
				element.getComponentsCount(),
				VertexArrayUtils::getOpenGLBaseType(element.m_Type),
				layout.getStride(),
				(const void*)element.m_Offset
			);
			m_vertexBufferIndex++;
			break;
			break;
		}
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:
		{
			uint32_t count = element.getComponentsCount();
			for (uint32_t i = 0; i < count; i++)
			{
				glEnableVertexAttribArray(m_vertexBufferIndex);
				glVertexAttribPointer(m_vertexBufferIndex,
					count,
					VertexArrayUtils::getOpenGLBaseType(element.m_Type),
					element.m_Normalized ? 1 : 0,
					layout.getStride(),
					(const void*)(element.m_Offset + sizeof(float) * i * count)
				);
			}			
			m_vertexBufferIndex++;
			break;
		}
		}
	}
	m_VertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::setIndexBuffer(const OwnRef<IndexBuffer>& indexBuffer)
{
	glBindVertexArray(m_RendererId);
	indexBuffer->bind();
	m_IndexBuffer = indexBuffer;
}