#ifdef __linux__
	#include "Platform/Unix/LinuxPlatform.hpp"

	#include <X11/Xatom.h>
	#include <X11/Xlib.h>
	#include <X11/Xresource.h>

namespace util
{
/******************************************************************************
 *
 *****************************************************************************/
LinuxPlatform::LinuxPlatform()
{
	// TODO: Investigate further
	XInitThreads();
}

/******************************************************************************
 *
 *****************************************************************************/
void LinuxPlatform::initialize(const sf::WindowHandle&)
{
}

/******************************************************************************
 *
 *****************************************************************************/
void LinuxPlatform::toggleFullscreen(const sf::WindowHandle&, const sf::State, const std::uint32_t, const bool, const sf::Vector2u&)
{
}

/******************************************************************************
 *
 *****************************************************************************/
float LinuxPlatform::getScreenScalingFactor(const sf::WindowHandle&)
{
	// technique from: https://github.com/glfw/glfw/issues/1019

	Display* dpy;
	char* displayname = nullptr;
	dpy = XOpenDisplay(displayname);
	if (dpy != nullptr)
	{
		char* resourceString = XResourceManagerString(dpy);
		XrmDatabase db;
		XrmValue value;
		char* type = nullptr;
		double dpi = 1.0;

		XrmInitialize();
		db = XrmGetStringDatabase(resourceString);

		if (resourceString && XrmGetResource(db, "Xft.dpi", "String", &type, &value) == 1 && value.addr)
		{
			dpi = atof(value.addr);
		}

		XCloseDisplay(dpy);

		return static_cast<float>(dpi / 96.0);
	}
	else
	{
		return 1.0f;
	}
}

/******************************************************************************
 *
 *****************************************************************************/
float LinuxPlatform::getRefreshRate(const sf::WindowHandle&)
{
	return 59.0f;
}
}

#endif // __linux__
