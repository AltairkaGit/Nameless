#pragma once
#include "base.h"

class UniformBuffer
{
public:
	virtual ~UniformBuffer() = default;

	virtual void setData(const void* data, uint32_t width, uint32_t offset = 0) = 0;

	static OwnRef<UniformBuffer> create(uint32_t size, uint32_t binding);
};