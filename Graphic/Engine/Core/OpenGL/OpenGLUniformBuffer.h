#pragma once
#include "Core/unifornBuffer.h"

class OpenGLUniformBuffer : public UniformBuffer
{
public:
	OpenGLUniformBuffer(uint32_t size, uint32_t binding);
	~OpenGLUniformBuffer();

	virtual void setData(const void* data, uint32_t size, uint32_t offset = 0) override;
private:
	uint32_t m_RendererId;

};