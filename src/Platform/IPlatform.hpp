#ifndef UTIL_IPLATFORM_HELPER_HPP
#define UTIL_IPLATFORM_HELPER_HPP

namespace util
{
struct IPlatform
{
	virtual ~IPlatform() = default;
	virtual void setIcon(const sf::WindowHandle& inHandle) = 0;
	virtual void toggleFullscreen(const sf::WindowHandle& inHandle, const sf::Uint32 inStyle, const bool inWindowed, const sf::Vector2u& inResolution) = 0;
	virtual int getRefreshRate(const sf::WindowHandle& inHandle) = 0;
	virtual float getScreenScalingFactor(const sf::WindowHandle& inHandle) = 0;
};
}

#endif // UTIL_IPLATFORM_HELPER_HPP
