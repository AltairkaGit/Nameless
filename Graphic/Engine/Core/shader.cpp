#include  "shader.h"
#include "renderer.h"
#include "OpenGL/OpenGLShader.h"

OwnRef<Shader> Shader::create(const std::string& filepath)
{
	switch (Renderer::getAPI())
	{
	case RendererAPI::API::None: return nullptr;
	case RendererAPI::API::OpenGL: return createOwnRef<OpenGLShader>(filepath);
	}
	return nullptr;
}

const OwnRef<Shader>& ShaderLibrary::load(const std::string& filename)
{
	auto shader = Shader::create(s_Directory + '/' + filename);
	add(shader);
	return shader;
}

const OwnRef<Shader>& ShaderLibrary::load(const std::string& name, const std::string& filename)
{
	auto shader = Shader::create(s_Directory + '/' + filename);
	add(name, shader);
	return shader;
}

const OwnRef<Shader>& ShaderLibrary::get(const std::string& name)
{
	if (exists(name)) return m_Shaders[name];
	return nullptr;
}

void ShaderLibrary::add(const std::string& name, const OwnRef<Shader>& shader)
{
	if (exists(name)) return;
	m_Shaders[name] = shader;
}

void ShaderLibrary::add(const OwnRef<Shader>& shader)
{
	auto& name = shader->getName();
	if (exists(name)) return;
	add(name, shader);
}

bool ShaderLibrary::exists(const std::string& name) const 
{
	return m_Shaders.count(name);
}