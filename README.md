# sfml-vscode-boilerplate
A cross-platform [SFML](https://www.sfml-dev.org) 2.5.1 & C++17 build environment for [Visual Studio Code](https://code.visualstudio.com/)

---

## Features

* Cross-platform build environments (Windows, Linux & MacOS)
* GCC & Clang Compiler Configuration
* Debugger support or standalone Debug build
* Unit testing (with Catch2)
* Static Profiler on Windows/Linux (gprof)
* Bash terminal integration
* Automated copying of dependencies
* Automated production build
* Automated app bundling on MacOS
* Basic app bundle on Linux
* Optionally auto-generate assembly from compiled objects (using objdump)
* Optional precompiled header (cross-platform as well)
* Optional Keybindings (F8, F9 & F10)
* Optionally build on Raspberry Pi! (see bottom of Readme)

---

## Prerequisites

### Windows
* [SFML 2.5.1 - GCC 7.3.0 MinGW (DW2) 32-bit (for Windows)](https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit.zip)
* [GCC 7.3.0 MinGW (DW2) 32-bit (for Windows)](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/i686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z/download)
* [Git Bash (for Windows) ](https://git-scm.com/downloads)

### MacOS
* [SFML 2.5.1 - Clang 64-bit](https://www.sfml-dev.org/files/SFML-2.5.1-macOS-clang.tar.gz)
* Command Line Tools / XCode (type "xcode-select --install" in terminal to trigger the installer)
* [Homebrew](https://brew.sh/) (for makeicns, or to optionally install SFML)

### Linux
* Get SFML 2.5.1 from your distro if it has it, or compile from source

### All
* [Visual Studio Code](https://code.visualstudio.com/download)
* Extensions (install from Extensions panel):
  * [Official C/C++ Extension (0.21.0+)](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
  * [Shader languages support for VS Code (Optional Syntax Highlighting)](https://marketplace.visualstudio.com/items?itemName=slevesque.shader)
  * [x86 and x86_64 Assembly (Optional Syntax Highlighting)](https://marketplace.visualstudio.com/items?itemName=13xforever.language-x86-64-assembly)
  * [Studio Icons (Optional Icon Theme)](https://marketplace.visualstudio.com/items?itemName=jtlowe.vscode-icon-theme)

---

## Installation

### Windows

1. Download & Extract SFML to **C:/SFML-2.5.1/** where the bin/lib/include folders are contained within
2. Download & Extract MinGW to **C:/mingw32/** where the bin/lib/include folders are contained within

### MacOS

1. Install "Command Line Tools" in MacOS if they're not already installed (type "xcode-select --install" in terminal)
2. Follow the "Installing SFML" directions here: https://www.sfml-dev.org/tutorials/2.5/start-osx.php#installing-sfml

### Linux
1. Ensure the GCC Toolchain is installed (**sudo apt install build-essential**)
2. Run **sudo apt install libsfml-dev**. The SFML version you got will vary depending on the distro. 2.5.1 is included in [Ubuntu 19.04 Disco Dingo](http://cdimage.ubuntu.com/daily-live/current/HEADER.html) for example.

### All

3. Download & Install Visual Studio Code if you don't already have it.
4. Install the official **C/C++** Extension, reload the window & wait for the dependencies to install.
5. If on Windows, install **Git Bash**, and ensure the **"terminal.integrated.shell.windows"** property in the project's **settings.json** is set to **bash.exe**'s correct location (default: C:/Program Files/Git/bin/bash.exe). We'll be using this for the terminal in our workspace so that the Makefile can run in both Windows, Mac & Linux
6. In **settings.json** Ensure **Path** in the **terminal.integrated.env.windows** object is set to the correct location of the compiler's executable (example: C:\\mingw32\\bin) and the SFML directory is correct as well. Keep in mind Paths should be separated by a semi-colon with no spaces between.

**Note:** You can manage the "Path" environment variable from Windows if you'd like, but I've found sandboxing it in VS Code is better for tracking things like .dll dependencies.

---

## Configuration

At this point, everything you need is installed

1. Open the **sfml-vscode-boilerplate** folder in VS Code. You should see an lime-green status bar at the bottom (color-picked from the SFML logo).
2. With Main.cpp (or any source file) open, check the lower-right to ensure "Win32/Mac/Linux" is the configuration set (this should be auto-selected by the C++ plugin). If it is not correct, hit **Ctrl+Shift+B** and select **C/Cpp: Select a configuration...** and choose the platform you're working on.
3. At this point you should be able to run a build task (**Ctrl+Shift+B** > **Build & Run**), but it'll be nicer to add keybindings for these tasks so you can build with 1 keypress.
4. Open the .vscode folder and click on the **\_keybindings.json** file. This is not an officially recognized file, but just contains the keybindings you can copy into the actual keybindings.json file.
5. Go into **File** > **Preferences** > **Keyboard Shortcuts** & click on the keybindings.json link at the top.
6. Copy the keybindings into this file. Feel free to change them if you don't like them later.
7. Hit the **F9** key to run the **Build & Run: Release** task. It should run the Makefile, find the compiler, build the Main.cpp into Main.o, and launch the sample SFML app. **Shift+F9** will launch the basic Debug build, and F8 will launch the actual Debugger alongside the Debug build.

---

## Adding Source Files

Source files and folders are automatically detected by the Makefile. It looks for them in the "src" folder, and at the moment builds from .c, .cpp, .cc & .rc files.

---

## Adding external libraries (the "lib" folder)

This build system assumes that any libraries includes in the "lib" folder are either pre-built or header-only. It's auto-included as one of the search directories in the Makefile. 

Usage example:

```
+ lib/
  + catch2/
    + catch.hpp
  + nlohmann_json/
    + json.hpp
  + XInput/
    + XInput.h
    + XInput.lib
```

test/test_someTest.cpp
```
#include <catch2/catch.hpp>
...
```

src/JsonImpl.hpp
```
#include <nlohmann_json/json.hpp>
...
```

src/InputManager.hpp
```
#include <XInput/XInput.h>
...
```

env/windows.all.mk
```makefile
LINK_LIBRARIES := \
  XInput
```

---

## Makefile Environment

The environment variables used by the Makefile are managed from the **env** folder in separate .mk (Make) files, organized by build type & platform, so you can customize which SFML libraries to include if you want, or pretty much anything without having to edit the tasks.json. Each file is outlined below:

    ./build.sh: Contains the build scripts that tasks.json calls

    ./env/.all.mk: All platforms & builds
    ./env/.debug.mk: All platforms, Debug build  
    ./env/.release.mk: All platforms, Release build  
    
    ./env/linux.all.mk: Linux, All builds  
    ./env/linux.debug.mk: Linux, Debug build  
    ./env/linux.release.mk: Linux, Release build

    ./env/osx.all.mk: MacOS, All builds  
    ./env/osx.debug.mk: MacOS, Debug build  
    ./env/osx.release.mk: MacOS, Release build

    ./env/rpi.release.mk: Linux (Raspberry Pi), Release build
    
    ./env/windows.all.mk: Windows, All builds  
    ./env/windows.debug.mk: Windows, Debug build  
    ./env/windows.release.mk: Windows, Release build 

Unit Tests use the same settings as the Release build.

The environment variables that can be added to each .mk file are outlined below. If you need a line-break anywhere simply add a **"\\"** character. You can set base variables in *.all.mk and then build specific variables using "VAR := $(VAR)" syntax in *.debug.mk or *.release.mk. The hierarchy goes:

    ./env/.all.mk
    ./env/.(build).mk
    ./env/(platform).all.mk
    ./env/(platform).(build).mk

---

## Environment Variables

**CFLAGS**:  
Compiler flags to use.

**MAX_PARALLEL_JOBS**:  
Max number of parallel jobs to run, based on number of cpus cores available

**CLEAN_OUTPUT**:  
If set to 'true', the build output will only show the path/filename of the source file being built as well as the linking step and a couple helpful messages. All other commands will be hidden (including assembly dumps)

**DUMP_ASSEMBLY**:  
If set to 'true', *.o.asm files will generate within the bin/(Build)/asm folder. The bin folder is hidden from VS Code by default, but you can open the asm folder in a separate instance and browse the assembly that way if you'd like to, or customize it from settings.json.

**PRECOMPILED_HEADER**:  
Define a precompiled header file (no extension). If this variable is not defined in the env files, then the precompiled header will not be used. This file will be excluded from Rebuild/Build tasks, but if the bin/(build) directory is removed, it will be as well.

If you're unfamiliar with how precompiled headers work, these speed up compile time by precompiling commonly used includes like standard libraries and the SFML includes. The PCH.hpp gets implicitly included in each cpp file, so you don't need to manually include it each time like with Visual Studio. When it actually compiles, it can be large, but it does not affect the size of the final binary (which would be the same size with or without the PCH). 
```makefile
PRECOMPILED_HEADER:=PCH
```

**LIB_DIRS**:  
Add any additional lib directories (full path)
```makefile
LIB_DIRS= \
  C:/sfeMovie/lib \
  C:/myLibraries/lib
```

**INCLUDE_DIRS**:  
Add any additional include directories (full path)
```makefile
INCLUDE_DIRS= \
  C:/sfeMovie/include \
  C:/myLibraries/include
```

**LINK_LIBRARIES**:  
Add any additional link libraries
```makefile
LINK_LIBRARIES= \
  XInput \
  user32 \
  something
```

**BUILD_FLAGS**:  
Additional compiler flags for the particular build (including prefix)
```makefile
BUILD_FLAGS= \
  -mwindows
```

**BUILD_MACROS**:  
Macros to include in the build
```makefile
BUILD_MACROS= \
  _DEBUG
```

**BUILD_DEPENDENCIES**:  
Dependency .dll/.so files to include in the bin/(build) folders
```makefile
BUILD_DEPENDENCIES= \
	C:/SFML-2.5.1/bin/openal32.dll
```

## MacOS-specific:

**MACOS_FRAMEWORK_PATHS**:  
Framework paths, other than /System/Library/Frameworks
```makefile
MACOS_FRAMEWORK_PATHS= \
	/Library/Frameworks
```

**MACOS_FRAMEWORKS**:
Frameworks to include, (no extension)
```makefile
MACOS_FRAMEWORKS= \
	CoreFoundation
```

---

## Build: Production

I thought it was important to include a build task that creates a final "build" folder and copies the files in the bin/Release folder, any dependency .dlls, and any other directories into it. It's accessed via (**Ctrl+Shift+B** > **Build: Production**) and uses a couple special environment variables:

**PRODUCTION_DEPENDENCIES**:  
Files & folders to copy into the "build" folder upon using the "Build: Production" task. In MacOS, this is anything going into the the app bundle's "Resources" folder.
```makefile
PRODUCTION_DEPENDENCIES= \
  C:/mingw32/bin/libgcc_s_dw2-1.dll \
  C:/mingw32/bin/libstdc++-6.dll \
  C:/mingw32/bin/libwinpthread-1.dll \
  C:/SFML-2.5.1/bin/openal32.dll \
  C:/SFML-2.5.1/bin/sfml-audio-2.dll \
  C:/SFML-2.5.1/bin/sfml-graphics-2.dll \
  C:/SFML-2.5.1/bin/sfml-network-2.dll \
  C:/SFML-2.5.1/bin/sfml-system-2.dll \
  C:/SFML-2.5.1/bin/sfml-window-2.dll \
  content
```

**PRODUCTION_EXCLUDE**:  
Files & extensions to exclude from the production build.
```makefile
PRODUCTION_EXCLUDE= \
  *.psd \
  *.rar \
  *.7z \
  Thumbs.db
```

**PRODUCTION_FOLDER**:  
The folder the production build will go into. This can be an absolute path or a relative path. Defaults to "build" if not defined.
```makefile
PRODUCTION_FOLDER=build
```

---

## Build: Production (MacOS)

Option 1: The "Build: Production" script creates a bundle & a basic .dmg image, but it does no code signing whatsoever! You must do that yourself (for now). There's a lot to document about, but to start, it requires a MacOS/MacHelper.cpp file to ensure the working directory is looking for resources inside the bundle's Resource folder. There's an Info.plist.json that gets compiled to the binary Info.plist, and an icon that gets compiled to an *.icns file. See osx.all.mk for additional production environment variables. Be aware some of it is still pretty experimental. The variables are outlined below.

Option 2: Use Xcode to bundle your final build! It's as simple as that. Follow the rest of the directions outlined [HERE](https://www.sfml-dev.org/tutorials/2.5/start-osx.php), copy your code-base in the Xcode project folder, and go from there.

**PRODUCTION_MACOS_ICON**:  
The app bundle's icon (.png, no extension)
```makefile
PRODUCTION_MACOS_ICON := sfml
```

**PRODUCTION_MACOS_BUNDLE_DEVELOPER**:  
Your name, company, etc.
```makefile
PRODUCTION_MACOS_BUNDLE_DEVELOPER := developer
```

**PRODUCTION_MACOS_BUNDLE_DISPLAY_NAME**:  
App's display name (used everywhere)
```makefile
PRODUCTION_MACOS_BUNDLE_DISPLAY_NAME := SFML Boilerplate
```

**PRODUCTION_MACOS_BUNDLE_NAME**:  
Internal app name (used somewhere by MacOS... ???)
```makefile
PRODUCTION_MACOS_BUNDLE_NAME := SFML Boilerplate
```

**PRODUCTION_MACOS_MAKE_DMG**:  
set to "true" to make a .dmg image 
```makefile
PRODUCTION_MACOS_MAKE_DMG := true
```

**PRODUCTION_MACOS_BACKGROUND**:  
Background image file (.png) to use in the .dmg image. A "...@2x.png" file is also expected
```makefile
PRODUCTION_MACOS_BACKGROUND := dmg-background
```

**PRODUCTION_MACOS_DYLIBS**:  
Dynamically linked libraries to include in the final build.
```makefile
PRODUCTION_MACOS_DYLIBS := \
	/usr/local/lib/libsfml-graphics.2.5 \
	/usr/local/lib/libsfml-audio.2.5 \
	/usr/local/lib/libsfml-network.2.5 \
	/usr/local/lib/libsfml-window.2.5 \
	/usr/local/lib/libsfml-system.2.5
```

**PRODUCTION_MACOS_FRAMEWORKS**:  
Any frameworks to add to the app bundle's "Frameworks" folder. (Path, no extension)
```makefile
PRODUCTION_MACOS_FRAMEWORKS :=
  /Library/Frameworks/ogg
```

---

## Build: Production (Linux/Ubuntu)

A default Ubuntu app build is included, but beyond that, you're on your own. The App's configuration is set in env/linux/exec.desktop. Similar to MacOS build these are the linux specific variables:

**PRODUCTION_LINUX_ICON**:  
The app icon (.png, no extension)
```makefile
PRODUCTION_LINUX_ICON := sfml
```

**PRODUCTION_LINUX_APP_NAME**:  
The app's name
```makefile
PRODUCTION_LINUX_APP_NAME := SFML Boilerplate
```

**PRODUCTION_LINUX_APP_COMMENT**:  
The app's description
```makefile
PRODUCTION_LINUX_APP_COMMENT := My SFML Game
```

---

## Build & Run: Tests

Unit Testing uses [Catch2](https://github.com/catchorg/Catch2). 

One can build & run the unit tests with the appropriately named "Build & Run: Tests" task in vscode. The Unit tests are a slightly different build target. You create tests in the **test/** directory, and they get built alongside the "Release" build target. Refer to the Catch2 docs to build your test cases. 

How you write your unit tests will obviously depend on how you write your engine code, but here are some examples:

* Tests for any non-rendering functions (bezier curves, rngs, utility classes, etc)
* Tests for rendering functions that create & display a window briefly
* Tests for implementations of any external libraries

---

## Profile: Debug

Running the **Profile: Debug** task will build the Debug target (if necessary) and generate a **profiler_analysis.stats** file from a **gmon.out** file using gcc's "gprof" profiler. You can then examine the stats file in the workspace.

---

## Include directories & .vscode folder

If you need to add additional external libraries, these are a couple different places to keep in mind.

* **.vscode/c\_cpp\_properties.json** - You'll see **compilerPath** & **includePath**. The compilerPath includes all the compiler's directories so, the includePath only needs the root project directory and any additional libraries you want to include. SFML is included as well in this boilerplate. See details below.

  * **compilerPath** - Path to the compiler's binary to use (in our case, it's MinGW GCC.
  * **includePath** - Used by the C/C++ extension for additional include directories. The relative project directory is included by default. You can also add directories recursively with **/****

* **.vscode/settings.json** - Contain all of your workspace settings & overrides VS Code's main settings.json. Here are some settings of interest:

  * **files.exclude** - Add any filetypes you want to exclude from the folder panel. By default, some of the build files are excluded from VS Code, so that one can focus on just coding.
  * **files.encoding** - This has been set to **utf8** by default, but you may want to use **windows1252** instead if you want less headaches. Feel free to change this to suit your needs.
  * **editor.fontFamily** - Set to Courier by default. Change/remove this line if you want to stick to VS Code's default (Consolas), or your own preference. I'm a big fan of [Courier Prime Code](https://quoteunquoteapps.com/courierprime/).
  * **terminal.integrated.env.(platform)** - Environment variables for use when the terminal runs. Note: These purposefully override the OS defaults so you can have an isolated environment.

* **.vscode/launch.json** - Used to store the configuration to launch the debugger.
* **.vscode/tasks.json** - Used to store the task definitions (Build & Run commands, etc.).
* **.vscode/_keybindings.json** - As mentioned before, this is used purely to store handy keybindings that one can add themselves, and not recognized by VS Code.

---

## Creating an application icon on Windows

There's some interesting nuances to creating Windows icons, so I've included two easy-to-use shell scripts that will create an icon for you from .png files:
```
win-make_icon_from_all.sh
win-make_icon_from256.sh
```
They only require you to install ImageMagick, available here:
https://www.imagemagick.org/script/download.php#windows (top-most binary)

The "win-make_icon_from_all.sh" script looks for 4 files: icon_16.png, icon_32.png, icon_48.png & icon_256.png. Edit them in the program of your choice & run the script using git bash and you'll get an app.ico file that you can import in ```src/Win32/Icon.rc```. The ```WindowsHelper``` class will read all the icons from the .ico file, and pick out the 16x16 & 32x32 ones for use as the application icon, while windows uses the other sizes for explorer.

The "win-make_icon_from256.sh" script is even simpler. You make one icon - icon_256.png, and it will generate the other sizes for you and output the app.ico file.

You can obviously modify these scripts to support other sizes used in edge cases (scaling factors use 20, 40, 64 & 96 for instance), but the 4 included are the most widely used.

---

## Multiple Projects

Recently, I wanted to avoid duplicate Makefiles in my various projects, so I found a nice little solution to do this.

1. Start by creating a folder structure where something like **SFML** is your root folder for SFML projects, and the **sfml-vscode-boilerplate** is contained within. We'll rename it to **sfml-project1**.
2. Copy the Makefile from **sfml-project1** to the root **SFML** directory
3. Edit the Makefile in **sfml-project1**, replace the entire contents to simply have:
  ```
  include ../Makefile
  ```
4. Copy the build.sh from **sfml-project1** to the root **SFML** directory
5. Edit the build.sh in **sfml-project1**, replace the entire contents to simply have:
  ```
  #!/bin/bash
  bash ../build.sh $1 $2 $3 $4
  ```
6. Make a copy of **sfml-project1** and call it **sfml-project2**
7. Open either project in vscode, and they should each should compile! Voila! You can now use a shared Makefile between projects this way

---

## Multiple Targets (experimental)

Multiple targets (dynamic libraries + 1 executable) are supported at the moment, although there's a couple setup changes you'll need.

1. Place all the files in **src** into a new folder called **main**. "main" is a special target that will compile the main executable
2. Create a new folder in **src** with your library's name. Place the code of that target within that folder.
3. Optionally, add the same folder name in the **env** folder & add any .mk files (same patterns) into that folder. For instance, you might have a library & a main target that depends on that library. You would need to supply the main target with "LINK_LIBRARIES := my_lib" that way, but can still use the main .mk files to configure both targets.
4. Now, you just need to supply build.sh with the target names. You can do this 2 ways. If you only plan on editing & building inside of vscode, you can add this to .vscode/tasks.json:
  ```json
  "options": {
      "env": {
          "BUILD_TARGETS": "target1 target2 main"
      }
  }
  ```
**BUILD_TARGETS** is a simple list of the folders, which then get output as the library name. For instance, "target1" would build out to "target1.dll" in Release, and "target1-d.dll" in Debug. "main" triggers the main target, and outputs "(root folder).exe" as it does w/o multiple targets.

Note: Ordered from first built to last built (main must be last if it's included)

6. However, if you want to build outside of vscode, you just need to add that as an environment variable. The best place for it is at the top of build.sh (which stays nice and clean if you followed the multiple projects step). That version would look like:
  ```bash
  #!/bin/bash
  export BUILD_TARGETS='target1 target2 main'

  bash ../build.sh $1 $2 $3 $4
  ```
7. At this point, you can build away, and you'll notice some extra verbiage related to multiple targets in the build output.


---

## Notes

* This configuration assumes all source files are contained within the **src** folder, but uses the **root** as the working directory for assets & things referenced in your project. It also includes a **content** folder if you'd like to contain those asset files further (recommended).
* By default, this configuration uses C++17. You can change the compiler flags in **env/\<platform\>.all.mk** under **CFLAGS**.

This will be an ongoing project that I'll try to update as new SFML versions come out. Updating SFML releases should be relatively painless as I'll keep the pre-reqs up to date as well. Feel free to offer suggestions/report issues if there's anything I missed, or could do better.

That should be all you need to get started. Happy game making and/or programming!

---

## Build Without VS Code (experimental)

If you have a reason to build your project without Code (on Raspbian or something), you can run build.sh the following way:

1. Use any bash terminal (Git Bash if Windows).
2. Run a variation of the following:
  ```
  bash build.sh (build|buildrun|rebuild|run|buildprod|profile) (Debug|Release) (executable commmand line options)
  ```

For instance, to build & run the Release build, you'd use:
  ```
  bash build.sh buildrun Release
  ```

If you run the script without any parameters, it's the same as the following:
  ```
  bash build.sh buildprod Release
  ```

To build & run the unit tests, use:
  ```
  bash build.sh buildrun Tests vscode '-w NoTests -s'
  ```
  (The last parameter contains Catch2 command line options)

If the build mode is not Debug or Release, it will default to Release. If you need to, change the "Path" variables within the build.sh file in the "if [[ $VSCODE != 'vscode' ]] ; then" block.

---

## Build on Raspberry Pi (experimental)

I'll maybe make a full guide for this, but I'd recommend doing your development on another machine, and then just pulling the project via git and building it on the Pi with the build script in the previous section. Raspbian Lite (as of 1/6/2019) only comes with GCC 6.x, so you'll want to add GCC 8.x via **[this guide](https://solarianprogrammer.com/2017/12/08/raspberry-pi-raspbian-install-gcc-compile-cpp-17-programs/)** and compile SFML 2.5.1 from source. Once your app/game is compiled, you can launch it via startx & matchbox-window-manager (after enabling OpenGL from raspi-config).

In the precompiled header (src/PCH.hpp), I added an extra SFML define for the Pi aptly named **SFML_SYSTEM_PI** so you can conditionalize parts of your code for PI specific things (think "kiosk mode"). From there, you're in the wild west.

---

## MSYS2 (on Windows) (or changing the mingw version)

GCC 7.3.0 is still probably the most stable GCC build on Windows, but if you want to try out newer versions, you can use [MSYS2](https://www.msys2.org/).

Start with a clean install from here:
* [MSYS2 (64-bit, 5/24/2019 stable)](http://repo.msys2.org/distrib/x86_64/msys2-x86_64-20190524.exe)

1. Install to `C:/msys64` (default)
2. Run `pacman -Syu` & restart Msys2 when it tells you do.
3. Run `pacman -Su` to update packages
4. Run the following command:
```
pacman -S mingw-w64-i686-toolchain mingw-w64-x86_64-toolchain mingw-w64-i686-openal mingw-w64-x86_64-openal
```
5. That will install both x86 & x64 versions (so you can try both) of GCC 10.1.0 (as of 5/16/20). It may take a while, but once finished, exit msys2.
6. Build SFML. To start with, install CMake & doxygen (64 bit version). Then download [this script](https://gist.github.com/andrew-r-king/5f8ea0eda064cbfb33f4f5d373011e0b) and edit the GCC_DIR line to either "/c/msys64/mingw64/bin" or "/c/msys64/mingw32/bin" depending on which architecture you want to target. Run the script, and if all goes well, you should have a compiled version of SFML in C:/SFML/2.5.1. You can also build from "master" instead by calling the script with that as a parameter.
7. rename that folder so its architecture specific. For my own build, I did "C:/SFML-2.5.1-gcc-10.1.0/mingw64"
8. Open sfml-vscode-boilerplate in VS Code, go into settings.json and comment out ".vscode/launch.json in "files.exclude", because we need to edit it. Also comment out "build.sh"
9. Also in settings.json, go down to "terminal.integrated.env.windows" and change it to "C:/msys64/mingw64/bin;C:/SFML-2.5.1-gcc-10.1.0/mingw64/bin" (the new paths)
10. In ".vscode/c_cpp_properties.json", go to the Win32 configuration and change the "compilerPath" to "C:/msys64/mingw64/bin/gcc.exe" and the SFML "includePath" to "C:/SFML-2.5.1-gcc-10.1.0/mingw64/include"
11. In ".vscode/launch.json", go to the "windows" configuration and change "miDebuggerPath" to "C:/msys64/mingw64/bin/gdb.exe"
12. Finally, in env/windows.all.mk, change _MINGW & _SFML (arbitrary variables) to:
```makefile
_MINGW := C:/msys64/mingw64/bin
_SFML := C:/SFML-2.5.1-gcc-10.1.0/mingw64
```

13. Finally, in build.sh, line 44, (windows path if running the script outside vscode), change to 'export PATH="/c/SFML-2.5.1/bin:/c/mingw32/bin:$PATH"', or alternatively if you're building without vscode (described above), you can add this snippet of in build.sh above "bash ../build.sh $1 $2 $3 $4":
```shell
if [[ $1 == '' && $2 == '' ]]; then
	if [[ $OSTYPE == 'msys' || $OSTYPE == 'win32' ]]; then
		export PATH="/c/SFML-2.5.1-gcc-10.1.0/mingw64/bin:/c/msys64/mingw64/bin:$PATH"
		bash ../build.sh buildprod Release vscode
		exit 0
	fi
fi
```

Run any build task (from scratch) and you should be good to go!

