#pragma once
#include "unifornBuffer.h"
#include "framebuffer.h"
#include "rendererAPI.h"
#include "vertexArray.h"
#include "texture.h"
#include "context.h"
#include "window.h"
#include "shader.h"

class Renderer
{
public:

	static void init(const uint32_t& ScreenWidth, const uint32_t& ScreenHeight, const std::string& name);
	static void shutdown();

	static void submit(const OwnRef<Shader>& shader, const OwnRef<VertexArray>& vertexArray, int32_t count = 0);
	static void clear();

	static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
	static Window* getWindow() { return s_Window.get(); }	
private:
	static Scope<RendererAPI> s_RendererAPI;
	static Scope<Window> s_Window;
};
