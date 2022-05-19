#include "OpenGLShader.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace ShaderUtils
{
	//TODO: add spirV in the project
	static GLenum getShaderType(const std::string& type)
	{
		if (type == "vertex")	return GL_VERTEX_SHADER;
		if (type == "fragment") return GL_FRAGMENT_SHADER;
		if (type == "pixel")	return GL_FRAGMENT_SHADER;
		return 0;
	}	
}

OpenGLShader::OpenGLShader(const std::string& filepath)
	: m_Path(filepath)
{
	std::string source = readFile(filepath);
	std::unordered_map<GLenum, std::string> sources = preprocessSources(source);
	createProgram(sources);
	//TODO: extract error log

	// Extract name from filepath
	auto lastSlash = filepath.find_last_of("/\\");
	lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
	auto lastDot = filepath.rfind('.');
	auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
	m_Name = filepath.substr(lastSlash, count);
}

void OpenGLShader::createProgram(std::unordered_map<GLenum, std::string>& sources)
{
	uint32_t pipe = 0;
	glCreateProgramPipelines(1, &pipe);
	
	uint32_t vertex = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, (const char**)&sources[GL_VERTEX_SHADER]);
	uint32_t fragment = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, (const char**)&sources[GL_FRAGMENT_SHADER]);
	m_OpenGLPrograms[ShaderType::Vertex] = vertex;
	m_OpenGLPrograms[ShaderType::Fragment] = fragment;

	glUseProgramStages(pipe, GL_VERTEX_SHADER_BIT, vertex);
	glUseProgramStages(pipe, GL_FRAGMENT_SHADER_BIT, fragment);

	m_RendererId = pipe;
}
		

std::string OpenGLShader::readFile(const std::string& filepath)
{
	std::string res;
	std::ifstream in(filepath, std::ios::in | std::ios::binary);
	if (!in)
	{
		std::cout << "Cannot open the file at path: " << filepath << '\n';
		return res;
	}
	in.seekg(0, std::ios::end);
	uint32_t size = in.tellg();
	if (size == -1)
	{
		std::cout << "Cannot read the file at path: " << filepath << '\n';
		return res;
	}
	res.resize(size);
	in.seekg(0, std::ios::beg);
	in.read(&res[0], size);
	return res;
}

//setting m_OpenGLSources
std::unordered_map<GLenum, std::string> OpenGLShader::preprocessSources(const std::string& source)
{
	std::unordered_map<GLenum, std::string> sources;

	const char* token = "#type";
	uint32_t tokenSize = strlen(token);
	uint32_t tokenPos = source.find(token);
	while (tokenPos != std::string::npos)
	{
		uint32_t eol = source.find_first_of("\r\n", tokenPos); //"#type SOMETYPE" line end
		uint32_t beg = tokenPos + tokenSize + 1; //"#type SOMETYPE" -> S position
		std::string type = source.substr(beg, eol - beg); //getting "SOMETYPE"
		if (!ShaderUtils::getShaderType(type)) std::cout << "Invalid shader type\n";
		uint32_t nextLine = source.find_first_not_of("\r\n", eol);
		tokenPos = source.find(token, nextLine);
		sources[ShaderUtils::getShaderType(type)] = source.substr(nextLine, tokenPos == std::string::npos ? source.size() : tokenPos - nextLine);
	}

	return sources;
}

OpenGLShader::~OpenGLShader()
{
	glDeleteProgramPipelines(1, &m_RendererId);
}

void OpenGLShader::bind() const
{
	glBindProgramPipeline(m_RendererId);
}

void OpenGLShader::unbind() const
{
	glBindProgramPipeline(0);
}


void OpenGLShader::setInt(ShaderType type, const std::string& name, const int& val)
{	
	uint32_t programId = m_OpenGLPrograms[type];
	GLint location = glGetUniformLocation(programId, name.c_str());
	glProgramUniform1i(programId, location, val);	
}
void OpenGLShader::setInt2(ShaderType type, const std::string& name, const glm::ivec2& val)
{	
	uint32_t programId = m_OpenGLPrograms[type];
	GLint location = glGetUniformLocation(programId, name.c_str());
	glProgramUniform2i(programId, location, val.x, val.y);	
}
void OpenGLShader::setInt3(ShaderType type, const std::string& name, const glm::ivec3& val)
{	
	uint32_t programId = m_OpenGLPrograms[type];
	GLint location = glGetUniformLocation(programId, name.c_str());
	glProgramUniform3i(programId, location, val.x, val.y, val.z);	
}
void OpenGLShader::setInt4(ShaderType type, const std::string& name, const glm::ivec4& val)
{	
	uint32_t programId = m_OpenGLPrograms[type];
	GLint location = glGetUniformLocation(programId, name.c_str());
	glProgramUniform4i(programId, location, val.x, val.y, val.z, val.w);	
}
void OpenGLShader::setIntArray(ShaderType type, const std::string& name, int* data, int count)
{	
	uint32_t programId = m_OpenGLPrograms[type];
	GLint location = glGetUniformLocation(programId, name.c_str());
	glProgramUniform1iv(programId, location, count, data);	
}
void OpenGLShader::setIntArrat(ShaderType type, const std::string& name, const std::vector<int>& data)
{	
	uint32_t programId = m_OpenGLPrograms[type];
	GLint location = glGetUniformLocation(programId, name.c_str());
	glProgramUniform1iv(programId, location, data.size(), data.data());	
}

void OpenGLShader::setFloat(ShaderType type, const std::string& name, const float& val)
{	
	uint32_t programId = m_OpenGLPrograms[type];
	GLint location = glGetUniformLocation(programId, name.c_str());
	glProgramUniform1f(programId, location, val);	
}
void OpenGLShader::setFloat2(ShaderType type, const std::string& name, const glm::vec2& val)
{	
	uint32_t programId = m_OpenGLPrograms[type];
	GLint location = glGetUniformLocation(programId, name.c_str());
	glProgramUniform2f(programId, location, val.x, val.y);	
}
void OpenGLShader::setFloat3(ShaderType type, const std::string& name, const glm::vec3& val)
{	
	uint32_t programId = m_OpenGLPrograms[type];
	GLint location = glGetUniformLocation(programId, name.c_str());
	glProgramUniform3f(programId, location, val.x, val.y, val.z);	
}
void OpenGLShader::setFloat4(ShaderType type, const std::string& name, const glm::vec4& val)
{
	uint32_t programId = m_OpenGLPrograms[type];
	GLint location = glGetUniformLocation(programId, name.c_str());
	glProgramUniform4f(programId, location, val.x, val.y, val.z, val.w);	
}

void OpenGLShader::setMat3(ShaderType type, const std::string& name, const glm::mat3& mat)
{
	uint32_t programId = m_OpenGLPrograms[type];
	GLint location = glGetUniformLocation(programId, name.c_str());
	glProgramUniform3fv(programId, location, GL_FALSE, glm::value_ptr(mat));	
}
void OpenGLShader::setMat4(ShaderType type, const std::string& name, const glm::mat4& mat)
{
	uint32_t programId = m_OpenGLPrograms[type];
	GLint location = glGetUniformLocation(programId, name.c_str());
	glProgramUniform4fv(programId, location, GL_FALSE, glm::value_ptr(mat));	
}
