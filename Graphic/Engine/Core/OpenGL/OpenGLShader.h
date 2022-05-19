#pragma once
#include "Math/math.h"
#include <unordered_map>
#include <glad/glad.h>
#include "Core/shader.h"
#include <string>

class OpenGLShader : public Shader
{
public:
	OpenGLShader(const std::string& filepath);
	virtual ~OpenGLShader();

	void bind() const override;
	void unbind() const override;

	virtual void setInt(ShaderType type, const std::string& name, const int& val) override;
	virtual void setInt2(ShaderType type, const std::string& name, const glm::ivec2& val) override;
	virtual void setInt3(ShaderType type, const std::string& name, const glm::ivec3& val) override;
	virtual void setInt4(ShaderType type, const std::string& name, const glm::ivec4& val) override;
	virtual void setIntArray(ShaderType type, const std::string& name, int* data, int count) override;
	virtual void setIntArrat(ShaderType type, const std::string& name, const std::vector<int>& data) override;

	virtual void setFloat(ShaderType type, const std::string& name, const float& val) override;
	virtual void setFloat2(ShaderType type, const std::string& name, const glm::vec2& val) override;
	virtual void setFloat3(ShaderType type, const std::string& name, const glm::vec3& val) override;
	virtual void setFloat4(ShaderType type, const std::string& name, const glm::vec4& val) override;

	virtual void setMat3(ShaderType type, const std::string& name, const glm::mat3& mat) override;
	virtual void setMat4(ShaderType type, const std::string& name, const glm::mat4& mat) override;

	virtual const std::string& getName() const override { return m_Name; };
private:
	std::string readFile(const std::string& filepath);
	std::unordered_map<GLenum, std::string> preprocessSources(const std::string& source);

	void createProgram(std::unordered_map<GLenum, std::string>& sources);
	//TODO: add spirV in the project
	//void reflect(GLenum stage, const std::vector<uint32_t>& shaderData);
private:
	uint32_t m_RendererId;
	std::string m_Path;
	std::string m_Name;
	
	std::unordered_map<ShaderType, uint32_t> m_OpenGLPrograms;
};
