#ifndef UTIL_LINUX_PLATFORM_HPP
#define UTIL_LINUX_PLATFORM_HPP

#include "Platform/IPlatform.hpp"

namespace util
{
struct LinuxPlatform final : IPlatform
{
	LinuxPlatform();

	virtual void initialize(const sf::WindowHandle& inHandle) final;
	virtual void toggleFullscreen(const sf::WindowHandle& inHandle, const sf::State inState, const std::uint32_t inStyle, const bool inWindowed, const sf::Vector2u& inResolution) final;
	virtual float getScreenScalingFactor(const sf::WindowHandle& inHandle) final;
	virtual float getRefreshRate(const sf::WindowHandle& inHandle) final;
};
}

#endif // UTIL_LINUX_PLATFORM_HPP
