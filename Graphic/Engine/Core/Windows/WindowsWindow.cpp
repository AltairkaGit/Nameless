#include "WindowsWindow.h"

static uint32_t s_WindowCout = 0;

WindowsWindow::WindowsWindow(const WindowProps& props)
{
	init(props);
}

WindowsWindow::~WindowsWindow()
{
	shutdown();
}


void WindowsWindow::onUpdate()
{
	m_Context->swapBuffers();
	glfwPollEvents();
}

const WindowData& WindowsWindow::getWindowData() const
{
	return m_Data;
}

bool WindowsWindow::init(const WindowProps& props)
{
	m_Data.m_Name = props.m_Name;
	m_Data.m_Width = props.m_Width;
	m_Data.m_Height = props.m_Height;
	m_Data.m_ShouldClose = 0;
	m_Data.m_IsMouseCaptured = 0;
	m_Data.m_AspectRatio = (float_t)m_Data.m_Width / m_Data.m_Height;

	if (s_WindowCout == 0)
	{
		int success = glfwInit();
	}

	m_Window = glfwCreateWindow(m_Data.m_Width, m_Data.m_Height, m_Data.m_Name.c_str(), NULL, NULL);
	m_Context = Context::Create(m_Window);
	m_Context->init();

	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//mouse capture
	glfwSetWindowUserPointer(m_Window, &m_Data);
	glfwSwapInterval(1);//VSync

	if (m_Window == nullptr)
	{
		std::cout << "Failed creating a window" << std::endl;
		return 0;
	}

	//TODO: create event system
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.m_Height = height;
		data.m_Width = width;
		float_t ratio = (float_t)width / height;
		data.m_AspectRatio = ratio / data.m_AspectRatio;
		glViewport(0, 0, data.m_Width, data.m_Height);		
	});
	
	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
	{
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		if (!data.m_IsMouseCaptured)
		{
			data.m_Xpos = xpos;
			data.m_Ypos = ypos;
			data.m_IsMouseCaptured = 1;
		}

		data.m_Xoffset = xpos - data.m_Xpos;
		data.m_Yoffset = data.m_Ypos - ypos;

		data.m_Xpos = xpos;
		data.m_Ypos = ypos;
	});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				
				break;
			}
			case GLFW_RELEASE:
			{
				
				break;
			}
			case GLFW_REPEAT:
			{
				
				break;
			}
			}
		});


	return 1;
}

void WindowsWindow::shutdown()
{
	glfwDestroyWindow(m_Window);
	s_WindowCout--;

	if (s_WindowCout == 0)
	{
		glfwTerminate();
	}
}

void WindowsWindow::setShouldClose()
{
	m_Data.m_ShouldClose = 1;
}
