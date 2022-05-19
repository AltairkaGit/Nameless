#pragma once
#include "Math/math.h"
#include <unordered_map>
#include <string>
#include "base.h"

enum class ShaderType
{
	None = 0, Vertex, Fragment, Geometry, Compute,
};

class Shader
{
public:
	virtual ~Shader() = default;

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	virtual void setInt(ShaderType type, const std::string& name, const int& val) = 0;
	virtual void setInt2(ShaderType type, const std::string& name, const glm::ivec2& val) = 0;
	virtual void setInt3(ShaderType type, const std::string& name, const glm::ivec3& val) = 0;
	virtual void setInt4(ShaderType type, const std::string& name, const glm::ivec4& val) = 0;
	virtual void setIntArray(ShaderType type, const std::string& name, int* data, int count) = 0;
	virtual void setIntArrat(ShaderType type, const std::string& name, const std::vector<int>& data) = 0;

	virtual void setFloat(ShaderType type, const std::string& name, const float& val) = 0;
	virtual void setFloat2(ShaderType type, const std::string& name, const glm::vec2& val) = 0;
	virtual void setFloat3(ShaderType type, const std::string& name, const glm::vec3& val) = 0;
	virtual void setFloat4(ShaderType type, const std::string& name, const glm::vec4& val) = 0;

	virtual void setMat3(ShaderType type, const std::string& name, const glm::mat3& mat) = 0;
	virtual void setMat4(ShaderType type, const std::string& name, const glm::mat4& mat) = 0;

	virtual const std::string& getName() const = 0;

	static OwnRef<Shader> create(const std::string& filepath);
};

class ShaderLibrary
{
public:
	ShaderLibrary() = default;
	ShaderLibrary(ShaderLibrary&) = delete;

	void add(const std::string& name, const OwnRef<Shader>& shader);
	void add(const OwnRef<Shader>& shader);
	const OwnRef<Shader>& load(const std::string& name, const std::string& filename);
	const OwnRef<Shader>& load(const std::string& filename);
	const OwnRef<Shader>& get(const std::string& name);
	bool exists(const std::string& name) const;
private:
	std::unordered_map<std::string, OwnRef<Shader>> m_Shaders;
};