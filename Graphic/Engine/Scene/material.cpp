#include "material.h"


Material::Material(const OwnRef<Shader>& shader, const std::string& name, uint8_t resolution, const std::string ext = "jpg")
	: m_Name(name), m_Shader(shader)
{
	m_Textures.push_back(Texture2D::create(s_Directory + '/' + std::to_string(resolution) + "k/" + name + "/albedo." + ext));
	m_Textures.push_back(Texture2D::create(s_Directory + '/' + std::to_string(resolution) + "k/" + name + "/normal." + ext));
	m_Textures.push_back(Texture2D::create(s_Directory + '/' + std::to_string(resolution) + "k/" + name + "/depth." + ext));
	m_Textures.push_back(Texture2D::create(s_Directory + '/' + std::to_string(resolution) + "k/" + name + "/arm." + ext));
}

void Material::submitDataInShader()
{
	std::string name;

	uint32_t albedoNumber = 1,
			 normalNumber = 1,
			 depthNumber = 1,
			 armNumber = 1;
	uint32_t i = 0;
	for (auto& texture : m_Textures)
	{
		texture->bind(i);
		switch (texture->getType())
		{
		case TextureType::Albedo:
			name = "material.albedoMap" + std::to_string(albedoNumber++);
			break;
		case TextureType::Normal:
			name = "material.normalMap" + std::to_string(normalNumber++);
			break;
		case TextureType::Depth:
			name = "material.depthMap" + std::to_string(depthNumber++);
			break;
		case TextureType::Arm:
			name = "material.armMap" + std::to_string(armNumber++);
			break;
		}
		
		m_Shader->setInt(ShaderType::Fragment, name, i);
		i++;
	}
}