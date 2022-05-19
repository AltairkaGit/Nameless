#pragma once
#include "base.h"
#include "buffer.h"

class VertexArray
{
public:
	virtual ~VertexArray() = default;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	virtual void addVertexBuffer(const OwnRef<VertexBuffer>& vertexBuffer) = 0;
	virtual void setIndexBuffer(const OwnRef<IndexBuffer>& indexBuffer) = 0;

	virtual const std::vector<OwnRef<VertexBuffer>>& getVertexBuffers() const = 0;
	virtual const OwnRef<IndexBuffer>& getIndexBuffer() const = 0;

	static OwnRef<VertexArray> create();
};