#pragma once
#include "../Core/renderer.h"
#include "../Scene/scene.h"
#include "../Core/input.h"

struct UserInputSystem
{
public:
	virtual void onUpdate(float_t deltaTime) = 0;
	UserInputSystem() = default;
	UserInputSystem(UserInputSystem&) = delete;
	UserInputSystem(Scene* scene) : m_Scene(scene) {}
protected:
	Scene* m_Scene = nullptr;
};

struct MouseInputSystem : public UserInputSystem
{
	virtual void onUpdate(float_t deltaTime) override;

	MouseInputSystem() = default;
	MouseInputSystem(MouseInputSystem&) = delete;
	MouseInputSystem(Scene* scene) : UserInputSystem(scene)
	{}
};


struct KeyboardInputSystem : public UserInputSystem
{
	virtual void onUpdate(float_t deltaTime) override;

	KeyboardInputSystem() = default;
	KeyboardInputSystem(KeyboardInputSystem&) = delete;
	KeyboardInputSystem(Scene * scene) : UserInputSystem(scene)
	{}
};
