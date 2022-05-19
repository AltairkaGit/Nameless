#include "window.h"
#include "Windows/WindowsWindow.h"

Scope<Window> Window::create(WindowProps props = WindowProps())
{
	switch (Window::platform)
	{
	case PLATFORM::None: return nullptr;
	case PLATFORM::Windows: return createScope<WindowsWindow>(props);
	}
	return nullptr;
}

