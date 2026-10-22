cmake_minimum_required(VERSION 3.22)

project(HomeDesignerApp
    VERSION 0.1.0
    DESCRIPTION "A cross-platform 2D study and home design tool"
    LANGUAGES CXX
)

include(FetchContent)

set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TESTS OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_INSTALL OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_AVIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_WEBP OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.2.10
    GIT_SHALLOW    TRUE
)
FetchContent_Declare(
    SDL3_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG        release-3.2.4
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(SDL3 SDL3_image)

add_executable(HomeDesignerApp
    src/main.cpp
    src/app/app.cpp
    src/graphics/Texture.cpp
    src/room/Room.cpp
    src/scenes/RoomScene.cpp
)
target_include_directories(HomeDesignerApp
    PRIVATE
        src
        debug
        src/core
        src/furniture
        src/graphics
        src/room
        src/room/placement
        src/scenes
)
target_compile_features(HomeDesignerApp PRIVATE cxx_std_23)
target_link_libraries(HomeDesignerApp
    PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
)
add_custom_command(TARGET HomeDesignerApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:HomeDesignerApp>/assets"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:HomeDesignerApp>
        $<TARGET_FILE_DIR:HomeDesignerApp>
    COMMAND_EXPAND_LISTS
)

if(CMAKE_SYSTEM_NAME STREQUAL "iOS")
    set_target_properties(HomeDesignerApp PROPERTIES
        MACOSX_BUNDLE TRUE
        XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.example.homedesignerapp"
        XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET "15.0"
    )
endif()

if(MSVC)
    target_compile_options(HomeDesignerApp PRIVATE /W4 /permissive-)
else()
    target_compile_options(HomeDesignerApp PRIVATE -Wall -Wextra -Wpedantic)
endif()
