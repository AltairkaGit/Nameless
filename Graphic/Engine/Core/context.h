#pragma once
#include "base.h"

class Context
{
public:
	virtual ~Context() = default;

	virtual void init() = 0;
	virtual void swapBuffers() = 0;

	static Scope<Context> Create(void* window);
};