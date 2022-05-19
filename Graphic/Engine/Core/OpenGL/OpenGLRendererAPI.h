#pragma once
#include "Core/rendererAPI.h"

class OpenGLRendererAPI : public RendererAPI
{
public:
	OpenGLRendererAPI();	
	virtual void setClearColor(const glm::vec4& color) override;
	virtual void clear() override;

	virtual void drawIndexed(const OwnRef<VertexArray>& vertexArray, int32_t count = 0) override;
private:
	virtual void init() override;
};