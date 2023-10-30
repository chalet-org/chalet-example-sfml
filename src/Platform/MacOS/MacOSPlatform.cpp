#ifdef __APPLE__
	#include "Platform/MacOS/MacOSPlatform.hpp"

	#include <array>

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
	std::array<char, PATH_MAX> path;
	bool pathSet = CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8*)path.data(), path.size());

	// This is a copy, so we release it here
	CFRelease(resourcesURL);

	// Actually do the check here
	if (pathSet)
	{
		std::string pathStr = path.data();
		if (pathStr.find(".app") != std::string::npos)
			chdir(path.data());
	}
}

/******************************************************************************
 *
 *****************************************************************************/
void MacOSPlatform::initialize(const sf::WindowHandle& inHandle)
{
	UNUSED(inHandle);

	// Not applicable on MacOS
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

	// Not applicable on MacOS
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
float MacOSPlatform::getRefreshRate(const sf::WindowHandle& inHandle)
{
	UNUSED(inHandle);

	CGDirectDisplayID mainDisplayId = CGMainDisplayID();
	CGDisplayModeRef displayMode = CGDisplayCopyDisplayMode(mainDisplayId);
	double refresh = CGDisplayModeGetRefreshRate(displayMode);
	CGDisplayModeRelease(displayMode);

	return static_cast<float>(refresh);
}
}

#endif // __APPLE__