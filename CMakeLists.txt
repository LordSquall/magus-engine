cmake_minimum_required (VERSION 2.6)
project (MagusEngine)

# The Version Number
set (MagusEngine_VERSION_MAJOR 1)
set (MagusEngine_VERSION_MINOR 0)

# configure a header file to pass some of the Cmake settings to the source code
configure_file(
  "${PROJECT_SOURCE_DIR}/src/magusversion.h.in"
  "${PROJECT_BINARY_DIR}/magusversion.h"
)

# add the binary tree to the search path for include files
# so that we will find MagusVersion.h
include_directories("${PROJECT_BINARY_DIR}")

# add the executable
add_executable(MagusEngine
src/subsystems/systems/systemclass.cpp
src/subsystems/systems/windowsclass.cpp
src/subsystems/graphics/graphicsclass.cpp
src/subsystems/graphics/rendererclass.cpp
src/subsystems/graphics/openglclass.cpp
src/subsystems/input/inputclass.cpp
src/main.cpp
)

source_group("subsystems\\systems" FILES
src/subsystems/systems/systemclass.cpp
src/subsystems/systems/windowsclass.cpp
)

source_group("subsystems\\graphics" FILES
src/subsystems/graphics/graphicsclass.cpp
src/subsystems/graphics/rendererclass.cpp
src/subsystems/graphics/openglclass.cpp
)

source_group("subsystems\\input" FILES
src/subsystems/input/inputclass.cpp
)