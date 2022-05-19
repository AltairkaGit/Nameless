#pragma once
#include "base.h"
#include <string>

struct WindowProps
{
	std::string m_Name;
	uint32_t m_Width;
	uint32_t m_Height;
	WindowProps(const std::string& name = "Altairka's Engine",
		uint32_t width = 1000,
		uint32_t height = 1000) 
		: m_Name(name), m_Width(width), m_Height(height)
	{
	}
};

struct WindowData
{
	std::string m_Name;
	uint32_t m_Height;
	uint32_t m_Width;
	uint32_t m_Xpos;
	uint32_t m_Ypos;
	uint32_t m_Xoffset;
	uint32_t m_Yoffset;
	float_t m_AspectRatio;
	bool m_IsMouseCaptured;
	bool m_ShouldClose;
};

enum class PLATFORM { None = 0, Windows = 1 };

class Window
{
public:
	virtual ~Window() = default;
	virtual void onUpdate() = 0;
	virtual void setShouldClose() = 0;
	virtual const WindowData& getWindowData() const = 0;

	static Scope<Window> create(WindowProps props = WindowProps());
	static PLATFORM platform;
};