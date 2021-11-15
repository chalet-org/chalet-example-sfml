#ifndef UTIL_MACOS_PLATFORM_HPP
#define UTIL_MACOS_PLATFORM_HPP

#include "Platform/IPlatform.hpp"

namespace util
{
struct MacOSPlatform final : IPlatform
{
	MacOSPlatform();

	virtual void setIcon(const sf::WindowHandle& inHandle) final;
	virtual void toggleFullscreen(const sf::WindowHandle& inHandle, const sf::Uint32 inStyle, const bool inWindowed, const sf::Vector2u& inResolution) final;
	virtual float getScreenScalingFactor(const sf::WindowHandle& inHandle) final;
	virtual float getRefreshRate(const sf::WindowHandle& inHandle) final;
};
}

#endif // UTIL_MACOS_PLATFORM_HPP
