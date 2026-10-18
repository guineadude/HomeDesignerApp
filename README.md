# HomeDesignerApp

HomeDesignerApp is a C++23 starter project for a cross-platform 2D study and
home design tool. Its initial structure keeps the layout model independent of
SDL, with SDL-specific input and application startup in separate targets.
Rendering and the editor UI are not implemented yet.

## Requirements

- CMake 3.22 or newer
- A compiler with C++23 support
- Git and network access during the first configure (SDL3 is fetched by CMake)
- For iOS builds: macOS, Xcode, and the Xcode command-line tools

## Desktop build

From the repository root, configure and build with CMake:

```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
```

Use a recent C++23-capable toolchain on Windows, macOS, or Linux. The
executable is placed in the build directory (or its configuration-specific
subdirectory when using a multi-configuration generator).

## iOS build with Xcode

Run these commands on macOS to generate an Xcode project for a physical iOS
device:

```sh
cmake -S . -B build-ios -G Xcode \
  -DCMAKE_SYSTEM_NAME=iOS \
  -DCMAKE_OSX_SYSROOT=iphoneos \
  -DCMAKE_OSX_ARCHITECTURES=arm64 \
  -DCMAKE_OSX_DEPLOYMENT_TARGET=15.0
cmake --build build-ios --config Debug
```

Open `build-ios/HomeDesignerApp.xcodeproj` in Xcode to select a signing team
and run on a device. For the simulator, configure a separate build directory
with `CMAKE_OSX_SYSROOT=iphonesimulator` and an architecture supported by the
local Xcode installation. Do not reuse a desktop build directory for iOS.

## Source layout

- `assets/rooms/` — room assets.
- `src/app/` — SDL3 application entry point and input integration.
- `src/graphics/` — graphics code.
- `src/scenes/` — SDL-independent layout and room data.

Bundled, read-only resources should be located relative to `SDL_GetBasePath()`.
User-created layouts and other writable data should be stored relative to
`SDL_GetPrefPath()`. These SDL-managed paths are queried during app
initialization.
