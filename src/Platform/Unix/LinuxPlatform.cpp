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
void LinuxPlatform::setIcon(const sf::WindowHandle& inHandle)
{
	UNUSED(inHandle);
}

/******************************************************************************
 *
 *****************************************************************************/
void LinuxPlatform::toggleFullscreen(const sf::WindowHandle& inHandle, const sf::Uint32 inStyle, const bool inWindowed, const sf::Vector2u& inResolution)
{
	UNUSED(inHandle);
	UNUSED(inStyle);
	UNUSED(inWindowed);
	UNUSED(inResolution);
}

/******************************************************************************
 *
 *****************************************************************************/
float LinuxPlatform::getScreenScalingFactor(const sf::WindowHandle& inHandle)
{
	UNUSED(inHandle);

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
float LinuxPlatform::getRefreshRate(const sf::WindowHandle& inHandle)
{
	UNUSED(inHandle);
	return 59.0f;
}
}

#endif // __linux__
