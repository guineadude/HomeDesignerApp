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

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.2.10
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(SDL3)

add_library(homedesigner_core STATIC
    src/Core/LayoutModel.cpp
)
add_library(HomeDesigner::Core ALIAS homedesigner_core)
target_include_directories(homedesigner_core
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_compile_features(homedesigner_core PUBLIC cxx_std_23)

add_library(homedesigner_input STATIC
    src/Engine/InputManager.cpp
)
add_library(HomeDesigner::Input ALIAS homedesigner_input)
target_include_directories(homedesigner_input
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_compile_features(homedesigner_input PUBLIC cxx_std_23)
target_link_libraries(homedesigner_input
    PUBLIC
        SDL3::SDL3
)

add_executable(HomeDesignerApp
    src/main.cpp
)
target_compile_features(HomeDesignerApp PRIVATE cxx_std_23)
target_link_libraries(HomeDesignerApp
    PRIVATE
        HomeDesigner::Core
        HomeDesigner::Input
        SDL3::SDL3
)

if(CMAKE_SYSTEM_NAME STREQUAL "iOS")
    set_target_properties(HomeDesignerApp PROPERTIES
        MACOSX_BUNDLE TRUE
        XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "com.example.homedesignerapp"
        XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET "15.0"
    )
endif()

if(MSVC)
    foreach(target IN ITEMS homedesigner_core homedesigner_input HomeDesignerApp)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    endforeach()
else()
    foreach(target IN ITEMS homedesigner_core homedesigner_input HomeDesignerApp)
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    endforeach()
endif()
