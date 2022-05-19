#include "game.h"

Model createTerrain(Material* material)
{
	bool randomLandscape = false;
	if (randomLandscape) srand(time(0));

	long long xSize = 32,
		ySize = xSize,
		xOffset = xSize / 2,
		yOffset = ySize / 2;

	//grid stuff
	std::vector<Vertex> grid((xSize + 1) * (ySize + 1));	
	float heightScale = 12.0f;
	std::vector<float> heightMap((xSize + 1) * (ySize + 1));
	glm::noise2d_fbm_map(heightMap, xSize + 1, 0.01f, 6);

	//making grid height and pos
	for (int x = 0; x <= xSize; x++)
	{
		for (int y = 0; y <= ySize; y++)
		{
			int n = x * (ySize + 1) + y;
			Vertex v;
			float h = heightMap[n];
			h *= heightScale;
			v.position = glm::vec3(x - xOffset, h, y - yOffset);
			v.normal = glm::vec3(0.0f, 0.0f, 0.0f);
			v.texture = glm::vec2(material->uvScale * x, material->uvScale * y);
			grid[n] = v;
		}
	}

	//making smooth normals
	for (int x = 0; x < xSize; x++)
	{
		for (int y = 0; y < ySize; y++)
		{
			Vertex
				&v1 = grid[x * (ySize + 1) + y],
				&v2 = grid[x * (ySize + 1) + y + 1],
				&v3 = grid[(x + 1) * (ySize + 1) + y];
			glm::vec3 
				v12 = glm::normalize(v1.position - v2.position),
				v32 = glm::normalize(v3.position - v2.position),
				n1 = glm::normalize(glm::cross(v32, v12));
			v1.normal = glm::normalize(v1.normal + n1);
			v2.normal = glm::normalize(v2.normal + n1);
			v3.normal = glm::normalize(v3.normal + n1);

			Vertex
				&v4 = grid[x * (ySize + 1) + y + 1],
				&v5 = grid[(x + 1) * (ySize + 1) + y],
				&v6 = grid[(x + 1) * (ySize + 1) + y + 1];
			glm::vec3 
				v64 = glm::normalize(v6.position - v4.position),
				n2 = glm::normalize(glm::cross(v64, v32));
			v4.normal = glm::normalize(v4.normal + n2);
			v5.normal = glm::normalize(v5.normal + n2);
			v6.normal = glm::normalize(v6.normal + n2);
		}
	}

	int vertSize = 6 * xSize * ySize;
	std::vector<unsigned int> inds(vertSize);
	
	for (int x = 0; x < xSize; x++)
	{
		for (int y = 0; y < ySize; y++)
		{
			int n = x * ySize + y;
			int ioffset = n * 6;
			n += x;
			inds[ioffset] = n;
			inds[ioffset + 1] = n + 1;
			inds[ioffset + 2] = n + ySize + 1;
			inds[ioffset + 3] = n + 1;
			inds[ioffset + 4] = n + ySize + 1;
			inds[ioffset + 5] = n + ySize + 2;
		}
	}

	Mesh terrain(std::move(grid), std::move(inds), material);
	terrain.calcTangents();

	return Model({ terrain });
}

void Game::onCreateEditor()
{
	Entity camera = m_ActiveScene.createEntity("EditorCamera");
	camera.addComponent<CameraComponent>();
	camera.addComponent<BasisComponent>();
	camera.getComponent<TransformComponent>().m_Translation = { 0.0f, 15.0f, 0.0f };
	m_ActiveScene.setActiveCamera(&camera.getComponent<CameraComponent>());

	m_ShaderLibrary.load("lighrShader.glsl");
	m_ShaderLibrary.load("lampShader.glsl");

	//materials creating
	Material material("forest_leaves_03");
	//lights creating
	Entity light = m_ActiveScene.createEntity("pointLight");
	light.addComponent<PointLightComponent>(PointLight({ 1.0f, 0.9f, 0.8f }, { 0.0f, 50.0f, 0.0f }, 1.0f, 0.05f, 0.005f));
	light.addComponent<ModelComponent>(Model("./src/models/lamp.obj"));
	//Terrain creating
	Entity terrain = m_ActiveScene.createEntity("Terrain");
	terrain.addComponent<ModelComponent>(createTerrain(&material));
	



}

void Game::onCreateRuntime()
{

}

void Game::onUpdateEditor(float deltaTime)
{
	glm::vec3 skyColors[] = {
		{ 0.823f, 0.733f, 0.576f },
		{ 0.634f, 0.7843f, 0.851f },
		{ 0.898f, 0.781f, 0.9176f },
	};
	//clear screen
	glm::vec3 skyColor = skyColors[2];
	glClearColor(skyColor.r, skyColor.g, skyColor.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Shader& lightShader = shaders.Get("lightShader");
	Shader& lampShader = shaders.Get("lampShader");

	lightShader.use();

	glm::mat4 modelm = glm::mat4(1.0f);
	modelm = glm::translate(modelm, glm::vec3(0.0f));
	modelm = glm::scale(modelm, glm::vec3(1.0f));

	//set shader uniform buffer

	//set point lights


	//draw models

	//light stuff
	lampShader.use();

	//set shader uniform buffer
	


}

void Game::onUpdateRuntime(float deltaTime)
{

}

void Game::processEventsEditor(float deltaTime)
{
	m_KeyboardInputSystem.onUpdate(deltaTime);
	m_MouseInputSystem.onUpdate(deltaTime);
	m_CameraSystem.onUpdate(deltaTime);
}

void Game::processEventsRuntime(float deltaTime)
{

}
