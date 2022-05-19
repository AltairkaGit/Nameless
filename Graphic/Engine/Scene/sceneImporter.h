#pragma once
#include "scene.h"
#include "Core/base.h"
#include "SceneManager.h"
#include "Libs/stb_image.h"
#include "Core/dataStream.h"
#include "simdjson/simdjson.h"

class SceneImporter
{
public:
	SceneImporter() = default;

	Scene create(const std::string& path, const SceneManager& managers);
private:
	void setRoots(std::vector<uint32_t>& out);
	void setNodes(std::vector<SceneNode>& out);
	void parseGLTF(const std::string& path);
	void parseGLB(const std::string& path);
};