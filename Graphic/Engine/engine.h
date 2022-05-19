#pragma once
#include "Core/renderer.h"
#include "Math/math.h"
#include "Scene/scene.h"
#include "Ecs/Systems/systems.h"
#include "Ecs/Components/components.h"

enum EngineMode
{
	EDITOR = 0,
	RUNTIME = 1,
};

class Engine
{
public:
	Engine();
	void run();
protected:
	virtual void onCreateEditor() = 0;
	virtual void onCreateRuntime() = 0;
	virtual void onUpdateEditor(float deltaTime) = 0;
	virtual void onUpdateRuntime(float deltaTime) = 0;
	virtual void processEventsEditor(float deltaTime) = 0;
	virtual void processEventsRuntime(float deltaTime) = 0;

	void drawModel(const OwnRef<Model>& model);
protected:
	KeyboardInputSystem m_KeyboardInputSystem;
	MouseInputSystem m_MouseInputSystem;
	CameraSystem m_CameraSystem;

	ModelsManager m_ModelsManager;
	MaterialsManager m_TexturesManager;


	//TODO: create timer class
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	float timeScale = 1.0f;

	Scene m_ActiveScene;

	EngineMode m_Mode = EngineMode::EDITOR;
};