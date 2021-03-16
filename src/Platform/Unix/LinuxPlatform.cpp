#ifdef __linux__
	#include "Platform/Unix/LinuxPlatform.hpp"

	#include <X11/Xlib.h>

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
	return 1.0f;
}

/******************************************************************************
 *
 *****************************************************************************/
int LinuxPlatform::getRefreshRate(const sf::WindowHandle& inHandle)
{
	UNUSED(inHandle);
	return 59;
}
}

#endif // __linux__
