#ifndef UTIL_WINDOWS_PLATFORM_HPP
#define UTIL_WINDOWS_PLATFORM_HPP

#include "Platform/IPlatform.hpp"

#include <array>

// TODO: WM_DISPLAYCHANGE event handling (multi-monitor support)

namespace util
{
struct WindowsPlatform final : IPlatform
{
	WindowsPlatform();

	virtual void setIcon(const sf::WindowHandle& inHandle) final;
	virtual void toggleFullscreen(const sf::WindowHandle& inHandle, const sf::Uint32 inStyle, const bool inWindowed, const sf::Vector2u& inResolution) final;
	virtual float getScreenScalingFactor(const sf::WindowHandle& inHandle) final;
	virtual float getRefreshRate(const sf::WindowHandle& inHandle) final;

private:
	PBYTE getIconDirectory(const int inResourceId);
	HICON getIconFromIconDirectory(PBYTE inIconDirectory, const uint inSize);
	DWORD sfmlWindowStyleToWin32WindowStyle(const sf::Uint32 inStyle);

	float m_screenScalingFactor = 0.0f;
};
}

#endif // UTIL_WINDOWS_PLATFORM_HPP
