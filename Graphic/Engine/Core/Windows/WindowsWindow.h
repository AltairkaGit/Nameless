#pragma once
#include <GLFW/glfw3.h>
#include "Core/window.h"
#include "Core/context.h"

class WindowsWindow : public Window
{
public:
	WindowsWindow(const WindowProps& props);

	virtual void onUpdate() override;
	virtual void setShouldClose() override;
	virtual const WindowData& getWindowData() const override;

private:
	virtual bool init(const WindowProps& props);
	virtual void shutdown();

	GLFWwindow* m_Window;
	Scope<Context> m_Context;
	WindowData m_Data;
};