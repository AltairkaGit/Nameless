#include "SceneImporter.h"


Scene SceneImporter::create(const std::string& path, const SceneManager& managers)
{
	uint32_t point = path.find_last_of('.');
	std::string ext = path.substr(point + 1);
	std::vector<SceneNode> nodes
	if (ext == "gltf") 

	

}

void SceneImporter::parseGLTF(const std::string& scenePath)
{
	simdjson::ondemand::parser parser;
	simdjson::padded_string json = simdjson::padded_string::load(scenePath);
	simdjson::ondemand::document gltf= parser.iterate(json);

	auto buffers = gltf["buffers"].get_array();
	auto bufferViews = gltf["bufferViews"].get_array();
	auto accessors = gltf["accessors"].get_array();

	auto images = gltf["images"].get_array();
	auto samplers = gltf["samplers"].get_array();
	auto materials = gltf["materials"].get_array();
	auto textures = gltf["textures"].get_array();

	auto meshes = gltf["meshes"].get_array();
	auto nodes = gltf["nodes"].get_array();	
	auto scenes = gltf["scenes"].get_array();

	auto scene = gltf["scene"].get_object();

	for (const auto& image : images)
	{
		
	}
}

void SceneImporter::parseGLB(const std::string& scenePath)
{
	simdjson::ondemand::parser parser;
	simdjson::padded_string json = simdjson::padded_string::load(scenePath);
}