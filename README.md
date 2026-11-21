# HomeDesignerApp

HomeDesignerApp is a cross-platform 2D study and home design tool written in
C++23 on SDL3. It draws an isometric room with floor and wall tiles. You can
place furniture from a catalogue onto a placement grid, move and zoom the camera,
and use a sprite-based UI layer (buttons, windows, labels).

## Requirements

- CMake 3.22 or newer
- A compiler with C++23 support
- Git and network access during the first configure. CMake fetches SDL3,
  SDL3_image and SDL3_ttf (with a bundled FreeType).
- For iOS builds: macOS, Xcode, and the Xcode command-line tools

## Desktop build

From the repository root, configure and build with CMake:

```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
```

The executable goes in the build directory, or in its per-configuration
subdirectory (for example `build/Debug/`) with a multi-config generator. After
each build, `assets/` is copied next to the executable. On Windows the required
runtime DLLs are copied there too.

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
with `CMAKE_OSX_SYSROOT=iphonesimulator` and an architecture your Xcode
installation supports. Don't reuse a desktop build directory for iOS.

## Controls

| Input              | Action                                  |
| ------------------ | --------------------------------------- |
| Arrow keys         | Pan the camera                          |
| Mouse wheel        | Zoom in / out                           |
| Tab                | Cycle the selected furniture (debug)    |
| Left click         | Place the selected furniture            |
| Esc                | Quit                                    |

## Source layout

```
src/
  main.cpp          SDL3 callback entry points (SDL_AppInit, SDL_AppEvent, ...)
  app/              App: SDL, window, renderer and text setup, plus the main loop
  core/             SDL-light helpers: isometric projection, hit testing, collision
  debug/            Debug logging and debug-only helpers (e.g. catalogue cycling)
  furniture/        Furniture definitions, footprints, the catalogue, placed instances
  graphics/         Texture, TextureManager and TextRenderer wrappers around SDL
  room/             Room model, tiles, floor/wall texture tables, build instructions
    placement/      Sub-tile placement grid and cell types
  scenes/           RoomScene (rendering + input for a room) and Camera
  ui/               UIManager, UIWrapper and the UI asset catalogue
    elements/       Individual UI elements: Button, Window, Label, Image, ...
assets/
  UI/               UI sprite sheets (16x16, 32x32, 48x48)
  debug/            Developer floor/wall textures
  fonts/            Fonts used by TextRenderer
  pixel_salvaje/    Furniture and tile art
```

## Conventions

- **File names:** `PascalCase` matching the main type they hold
  (`RoomScene.hpp`, `FurnitureCatalogue.hpp`). **Folder names:** lowercase.
- **Includes:** project headers are always included by their path from `src/`,
  in quotes: `#include "room/placement/PlacementGrid.hpp"`, never just
  `#include "PlacementGrid.hpp"`. `src/` is the only project include directory.
  Library and standard headers use angle brackets (`<SDL3/SDL.h>`, `<vector>`).
- **Debug code:** logging (`Core::Debug::log`) and debug-only helpers live in
  `src/debug/Debug.hpp` / `Debug.cpp`, not in the feature code that uses them.

## Runtime paths

Find bundled, read-only resources relative to `SDL_GetBasePath()`. Store
user-created layouts and other writable data relative to `SDL_GetPrefPath()`.
The app queries these SDL-managed paths during initialization.
