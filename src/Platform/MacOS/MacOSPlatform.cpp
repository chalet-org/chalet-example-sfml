#ifdef __APPLE__
	#include "Platform/MacOS/MacOSPlatform.hpp"

	#include <CoreFoundation/CoreFoundation.h>
	#include <CoreGraphics/CGDisplayConfiguration.h>

namespace util
{
/******************************************************************************
 *
 *****************************************************************************/
MacOSPlatform::MacOSPlatform()
{
	// This function ensures the working directory is set inside of the bundle if in production mode
	CFBundleRef mainBundle = CFBundleGetMainBundle();
	CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
	char path[PATH_MAX];
	bool pathSet = CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8*)path, PATH_MAX);

	// This is a copy, so we release it here
	CFRelease(resourcesURL);

	// Actually do the check here
	if (pathSet)
	{
		std::string pathStr = path;
		if (pathStr.find(".app") != std::string::npos)
			chdir(path);
	}
}

/******************************************************************************
 *
 *****************************************************************************/
void MacOSPlatform::setIcon(const sf::WindowHandle& inHandle)
{
	UNUSED(inHandle);
}

/******************************************************************************
 *
 *****************************************************************************/
void MacOSPlatform::toggleFullscreen(const sf::WindowHandle& inHandle, const sf::Uint32 inStyle, const bool inWindowed, const sf::Vector2u& inResolution)
{
	UNUSED(inHandle);
	UNUSED(inStyle);
	UNUSED(inWindowed);
	UNUSED(inResolution);
}

/******************************************************************************
 *
 *****************************************************************************/
float MacOSPlatform::getScreenScalingFactor(const sf::WindowHandle& inHandle)
{
	UNUSED(inHandle);

	CGDirectDisplayID mainDisplayId = CGMainDisplayID();
	size_t width = CGDisplayPixelsWide(mainDisplayId);
	size_t height = CGDisplayPixelsHigh(mainDisplayId);

	CGDisplayModeRef displayMode = CGDisplayCopyDisplayMode(mainDisplayId);
	size_t pwidth = CGDisplayModeGetPixelWidth(displayMode);
	size_t pheight = CGDisplayModeGetPixelHeight(displayMode);
	CGDisplayModeRelease(displayMode);

	float factorX = static_cast<float>(pwidth) / static_cast<float>(width);
	float factorY = static_cast<float>(pheight) / static_cast<float>(height);

	float factor = (factorX + factorY) * 0.5f;

	return factor;
}

/******************************************************************************
 *
 *****************************************************************************/
int MacOSPlatform::getRefreshRate(const sf::WindowHandle& inHandle)
{
	UNUSED(inHandle);
	return 59;
}
}

#endif // __APPLE__