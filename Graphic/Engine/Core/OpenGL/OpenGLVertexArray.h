#pragma once
#include "Core/vertexArray.h"

class OpenGLVertexArray : public VertexArray
{
public:
	OpenGLVertexArray();
	virtual ~OpenGLVertexArray();

	virtual void bind() const override;
	virtual void unbind() const override;

	virtual void addVertexBuffer(const OwnRef<VertexBuffer>& vertexBuffer) override;
	virtual void setIndexBuffer(const OwnRef<IndexBuffer>& indexBuffer) override;

	virtual const std::vector<OwnRef<VertexBuffer>>& getVertexBuffers() const override { return m_VertexBuffers; }
	virtual const OwnRef<IndexBuffer>& getIndexBuffer() const override { return m_IndexBuffer; }

private:
	uint32_t m_RendererId;
	uint32_t m_vertexBufferIndex = 0;
	std::vector<OwnRef<VertexBuffer>> m_VertexBuffers;
	OwnRef<IndexBuffer> m_IndexBuffer;
};
