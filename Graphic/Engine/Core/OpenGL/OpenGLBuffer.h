#pragma once
#include "Core/buffer.h"

class OpenGLVertexBuffer : public VertexBuffer
{
public:
	OpenGLVertexBuffer(uint32_t size);
	OpenGLVertexBuffer(Vertex* vertices, uint32_t size);
	OpenGLVertexBuffer(const std::vector<Vertex>& vertices);
	~OpenGLVertexBuffer();

	virtual void bind() const override;
	virtual void unbind() const override;

	virtual void setData(const void* data, uint32_t size) override;

	virtual const BufferLayout& getLayout() const override { return m_Layout; }
	virtual void setLayout(const BufferLayout& layout) override { m_Layout = layout; }
private:
	BufferLayout m_Layout;
	uint32_t m_RendererID;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
	OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
	OpenGLIndexBuffer(const std::vector<uint32_t>& indices);
	~OpenGLIndexBuffer();

	virtual void bind() const override;
	virtual void unbind() const override;

	virtual uint32_t getCount() const override { return m_Count; }


private:
	uint32_t m_Count;
	uint32_t m_RendererID;
};