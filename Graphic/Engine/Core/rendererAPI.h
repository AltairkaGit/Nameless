#pragma once
#include "stb_image.h"
#include "Math/math.h"
#include "vertexArray.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "base.h"

class RendererAPI
{
public:
	enum class API { None = 0, OpenGL = 1 };

	virtual ~RendererAPI() = default;
	
	virtual void setClearColor(const glm::vec4 & color) = 0;
	virtual void clear() = 0;


	virtual void drawIndexed(const OwnRef<VertexArray>& vertexArray, int32_t count = 0) = 0;

	static API getAPI() { return s_API; }
	static Scope<RendererAPI> create();
private:
	virtual void init() = 0;
	glm::vec4 clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	static float s_AspectRatio;
	static API s_API;
};


