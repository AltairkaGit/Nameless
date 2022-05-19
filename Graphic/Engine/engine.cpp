#include "engine.h"

//TODO: remove all s_Directory

Engine::Engine()
{
	//screen resolution
	uint32_t SCREEN_WIDTH = 1000;
	uint32_t SCREEN_HEIGHT = 1000;
	Renderer::init(SCREEN_WIDTH, SCREEN_WIDTH, "Altairka's Engine");

	m_KeyboardInputSystem = KeyboardInputSystem(&m_ActiveScene);
	m_MouseInputSystem = MouseInputSystem(&m_ActiveScene);
	m_CameraSystem = CameraSystem(&m_ActiveScene);

	std::string scenePath = "./src/scenes/T/ship_pinnace_2k.gltf";
	SceneImporter sceneImporter;
	m_ActiveScene = SceneImporter::create(scenePath);
}

void Engine::run()
{
	while (!Renderer::getWindow()->getWindowData().m_ShouldClose)
	{
		switch (m_Mode)
		{
		case EngineMode::EDITOR:
			processEventsEditor(deltaTime);
			break;
		case EngineMode::RUNTIME:
			processEventsRuntime(deltaTime);
			break;
		}
		
		/** send to scene camera position and direction and
			get two queue 1. loading queue, 2. deleting queue
		*/

		//TODO: create timer
		{
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			deltaTime *= timeScale;
			lastFrame = currentFrame;
		}

		Renderer::clear();
		

		switch (m_Mode)
		{
		case EngineMode::EDITOR:
			onUpdateEditor(deltaTime);
			break;
		case EngineMode::RUNTIME:
			onUpdateRuntime(deltaTime);
			break;
		}

		Renderer::getWindow()->onUpdate();
	}
}

void Engine::drawModel(const OwnRef<Model>& model)
{
	for (const Mesh& mesh : model.get()->getMeshes())
	{
		mesh.getMaterial()->submitDataInShader(shader);
		Renderer::submit(shader, mesh.getVertexArray());
	}
}