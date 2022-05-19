#pragma once
#include <vector>
#include <string>
#include "Math/math.h"
#include "Core/shader.h"
#include "Core/texture.h"
#include "assets.h"

struct Material
{
public:
	Material() = default;
	Material(const Material&) = default;

	Material(const OwnRef<Shader>& shader, const std::string& name, uint8_t resolution = 2, const std::string ext = "jpg");
	Material(const std::string& filename);

	void submitDataInShader();

public:
	std::vector<OwnRef<Texture2D>> m_Textures;
	OwnRef<Shader> m_Shader;
	std::string m_Name = "";

	
private:
	bool doubleSided = 0;
	
	
};