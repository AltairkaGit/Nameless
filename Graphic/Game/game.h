#pragma once
#include "../Engine/engine.h"

class Game : public Engine
{
public:
	Game() = default;
	Game(const Game&) = delete;
protected:
	void onCreateEditor() override;
	void onCreateRuntime() override;
	void onUpdateEditor(float deltaTime) override;
	void onUpdateRuntime(float deltaTime) override;
	void processEventsEditor(float deltaTime) override;
	void processEventsRuntime(float deltaTime) override;
};