#ifndef UTIL_PLATFORM_HPP
#define UTIL_PLATFORM_HPP

#if defined(__APPLE__)
	#include "Platform/MacOS/MacOSPlatform.hpp"
#elif defined(__linux__)
	#include "Platform/Unix/LinuxPlatform.hpp"
#elif defined(_WIN32)
	#include "Platform/Win32/WindowsPlatform.hpp"
#endif

namespace util
{
#if defined(__APPLE__)
using Platform = MacOSPlatform;
#elif defined(__linux__)
using Platform = LinuxPlatform;
#elif defined(_WIN32)
using Platform = WindowsPlatform;
#endif
}
#endif // UTIL_PLATFORM_HPP
