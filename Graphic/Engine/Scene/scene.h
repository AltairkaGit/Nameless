#pragma once
#include "Core/base.h"
#include "assets.h"
#include "node.h"
#include "model.h"

template<class T>
struct Octree
{
	Octree(uint32_t levels);
	~Octree() = default;



	T* data = 0;
};


class Scene
{
public:
	/** Do NOT use this constructor
		To create the instance!
		To create use SceneImporter
	*/
	Scene() = default;

private:
	/** Use this to traverse the trees	
	*/
	std::vector<uint32_t> m_Roots;
	std::vector<SceneNode> m_Nodes;
};