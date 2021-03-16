#ifndef UTIL_LINUX_PLATFORM_HPP
#define UTIL_LINUX_PLATFORM_HPP

#include "Platform/IPlatform.hpp"

namespace util
{
struct LinuxPlatform : IPlatform
{
	LinuxPlatform();

	void setIcon(const sf::WindowHandle& inHandle) final;
	void toggleFullscreen(const sf::WindowHandle& inHandle, const sf::Uint32 inStyle, const bool inWindowed, const sf::Vector2u& inResolution) final;
	float getScreenScalingFactor(const sf::WindowHandle& inHandle) final;
	int getRefreshRate(const sf::WindowHandle& inHandle) final;
};
}

#endif // UTIL_LINUX_PLATFORM_HPP
