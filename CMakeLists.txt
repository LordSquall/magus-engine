cmake_minimum_required (VERSION 2.6)

project (MagusEngine)

# includes
include (${CMAKE_ROOT}/Modules/FindOpenGL.cmake)

# The Version Number
set (MagusEngine_VERSION_MAJOR 1)
set (MagusEngine_VERSION_MINOR 0)
if(WIN32)
set (MagusEngine_OS_VERSION \"Windows\")
else()
set (MagusEngine_OS_VERSION \"Linux\")
endif()


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/external/modules/")

link_directories(${CMAKE_SOURCE_DIR}/external/lib)

find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

find_package (Threads REQUIRED)

if(WIN32)
  set(LIBS glfw3 opengl32 assimp)
elseif(UNIX AND NOT APPLE)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
  find_package(OpenGL REQUIRED)
  add_definitions(${OPENGL_DEFINITIONS})
  find_package(X11 REQUIRED)
  # note that the order is important for setting the libs
  # use pkg-config --libs $(pkg-config --print-requires --print-requires-private glfw3) in a terminal to confirm
  set(LIBS ${GLFW3_LIBRARY} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread assimp dl)
elseif(APPLE)
  INCLUDE_DIRECTORIES(/System/Library/Frameworks)
  FIND_LIBRARY(COCOA_LIBRARY Cocoa)
  FIND_LIBRARY(OpenGL_LIBRARY OpenGL)
  FIND_LIBRARY(IOKit_LIBRARY IOKit)
  FIND_LIBRARY(CoreVideo_LIBRARY CoreVideo)
  MARK_AS_ADVANCED(COCOA_LIBRARY OpenGL_LIBRARY)
  SET(APPLE_LIBS ${COCOA_LIBRARY} ${IOKit_LIBRARY} ${OpenGL_LIBRARY} ${CoreVideo_LIBRARY})
  SET(APPLE_LIBS ${APPLE_LIBS} ${GLFW3_LIBRARY} ${ASSIMP_LIBRARY})
  set(LIBS ${LIBS} ${APPLE_LIBS})
else()
  set(LIBS )
endif(WIN32)

# configure a header file to pass some of the Cmake settings to the source code
configure_file(
  "${PROJECT_SOURCE_DIR}/src/magusversion.h.in"
  "${PROJECT_BINARY_DIR}/magusversion.h"
)

# add source files to variables
# engine
set(Engine_SourceFiles
	src/main.cpp
	src/framework.cpp
)	

# subsystem - external
set(SubSystem_External_SourceFiles
	src/subsystems/external/tinyxml2/tinyxml2.cpp
	src/subsystems/external/lodepng/lodepng.cpp
	src/subsystems/external/poly2tri/common/shapes.cc
	src/subsystems/external/poly2tri/sweep/advancing_front.cc
	src/subsystems/external/poly2tri/sweep/cdt.cc
	src/subsystems/external/poly2tri/sweep/sweep.cc
	src/subsystems/external/poly2tri/sweep/sweep_context.cc
)

# subsystem - graphics
set(SubSystem_Graphics_SourceFiles
	src/subsystems/graphics/graphics.cpp
	src/subsystems/graphics/graphic2d.cpp
	src/subsystems/graphics/graphic3d.cpp
	src/subsystems/graphics/vg.cpp
)

# subsystem - primitives
set(SubSystem_Graphics_Primitives_SourceFiles
	src/subsystems/graphics/primitives/rectangle.cpp
	src/subsystems/graphics/primitives/line.cpp
	src/subsystems/graphics/primitives/text.cpp
	src/subsystems/graphics/primitives/ellipse.cpp
	src/subsystems/graphics/primitives/path.cpp
)

# subsystem - graphics - renderer
set(SubSystem_Graphics_Renderer_SourceFiles
	src/subsystems/graphics/renderers/renderer_interface.cpp
)

# subsystem - graphics - renderer - software
set(SubSystem_Graphics_Renderer_Software_SourceFiles
	src/subsystems/graphics/renderers/software/renderer_software.cpp
	src/subsystems/graphics/renderers/software/renderer_software_initialise_visitor.cpp
	src/subsystems/graphics/renderers/software/renderer_software_render_visitor.cpp
	src/subsystems/graphics/renderers/software/sr_framebuffer.cpp
	src/subsystems/graphics/renderers/software/sr_scanbuffer.cpp
	src/subsystems/graphics/renderers/software/sr_edge.cpp
	src/subsystems/graphics/renderers/software/sr_varier.cpp
	src/subsystems/graphics/renderers/software/sr_pipeline.cpp
)

# subsystem - graphics - renderer - windows
set(SubSystem_Graphics_Renderer_Windows_SourceFiles
	src/subsystems/graphics/renderers/windows/renderer_windows_opengl.cpp
	src/subsystems/graphics/renderers/windows/renderer_windows_initialise_visitor.cpp
	src/subsystems/graphics/renderers/windows/renderer_windows_render_visitor.cpp
	src/subsystems/graphics/renderers/windows/graphics_blender.cpp
)

# subsystem - graphics - renderer - linux
set(SubSystem_Graphics_Renderer_Linux_SourceFiles
	src/subsystems/graphics/renderers/linux/renderer_linux_opengl.cpp
	src/subsystems/graphics/renderers/linux/renderer_linux_initialise_visitor.cpp
	src/subsystems/graphics/renderers/linux/renderer_linux_render_visitor.cpp
	src/subsystems/graphics/renderers/linux/graphics_blender.cpp
)

# subsystem - input
set(SubSystem_Input_SourceFiles
src/subsystems/input/input.cpp
)	

# subsystem - IO
set(SubSystem_IO_SourceFiles
	src/subsystems/io/SceneParser.cpp
	src/subsystems/io/FontParser.cpp
	src/subsystems/io/OBJParser.cpp
)

# subsystem - logging
set(SubSystem_Logging_SourceFiles
	src/subsystems/logging/logger.cpp
)


# subsystem - math
set(SubSystem_Math_SourceFiles
	src/subsystems/math/vector.cpp
	src/subsystems/math/matrix.cpp
	src/subsystems/math/vertex.cpp
)	

# subsystem - os
set(SubSystem_OS_SourceFiles
	# populate later to platform specific files
)	

# subsystem - resources
set(SubSystem_Resources_SourceFiles
	src/subsystems/resources/bitmap.cpp
	src/subsystems/resources/color.cpp
	src/subsystems/resources/font.cpp
	src/subsystems/resources/hashtable.cpp
	src/subsystems/resources/material.cpp
	src/subsystems/resources/mesh.cpp
	src/subsystems/resources/resources.cpp
	src/subsystems/resources/shader.cpp
	src/subsystems/resources/texture.cpp
)

# subsystem - scenemanagement
set(SubSystem_SceneManagement_SourceFiles
	src/subsystems/scenemanagement/scene.cpp
	src/subsystems/scenemanagement/scenenode.cpp
)

# subsystem - datamodel
set(SubSystem_DataModel_SourceFiles
	src/subsystems/datamodel/datamodel.cpp
	src/subsystems/datamodel/altimeter_dm.cpp
)

# subsystem - behaviour
set(SubSystem_Behaviour_SourceFiles
	src/subsystems/behaviour/behaviour_visitor.cpp
)

# subsystem - network
set(SubSystem_Network_SourceFiles
	src/subsystems/network/network_interface.cpp
)


set(FinalPlatformRenderer_SourceFiles)

#depending on OS add relevent source files
MESSAGE("CMAKE_SYSTEM_NAME:         " ${CMAKE_SYSTEM_NAME} )
if(WIN32)
	set(SubSystem_OS_SourceFiles
		${SubSystem_OS_SourceFiles}
		src/subsystems/os/os_windows.cpp
	)
	
	set(SubSystem_Network_SourceFiles
		${SubSystem_Network_SourceFiles}
		src/subsystems/network/windows_network.cpp
	)
	
	set(FinalPlatformRenderer_SourceFiles
		${SubSystem_Graphics_Renderer_Windows_SourceFiles}
	)
		
else()
	set(SubSystem_OS_SourceFiles
		${SubSystem_OS_SourceFiles}
		src/subsystems/os/os_linux.cpp
	)
	
	set(SubSystem_Network_SourceFiles
		${SubSystem_Network_SourceFiles}
		src/subsystems/network/linux_network.cpp
	)
	
	
	set(FinalPlatformRenderer_SourceFiles
		${SubSystem_Graphics_Renderer_Linux_SourceFiles}
	)

	find_package(X11 REQUIRED)
	link_libraries(${X11_LIBRARIES})
	include_directories(${X11_INCLUDE_DIR})

	link_libraries(${OPENGL_gl_LIBRARY})
	link_libraries(${OPENGL_glu_LIBRARY})
	include_directories(${OpenGL_INCLUDE_DIR})

endif()


MESSAGE("SourceFiles:         " ${SourceFiles} )

# add the binary tree to the search path for include files
# so that we will find MagusVersion.h
include_directories("${PROJECT_BINARY_DIR}")

# add relavent libraries
add_library(GLAD "${CMAKE_SOURCE_DIR}/external/src/glad.c")
if(WIN32)
  set(LIBS ${LIBS} GLAD)
elseif(UNIX AND NOT APPLE)
  set(LIBS ${LIBS} GLAD ld)
else()
  set(LIBS )
endif(WIN32)

# add the executable
add_executable(MagusEngine
	${Engine_SourceFiles}
	${SubSystem_External_SourceFiles}
	${SubSystem_Graphics_SourceFiles}
	${SubSystem_Graphics_Primitives_SourceFiles}
	${SubSystem_Graphics_Renderer_SourceFiles}
	${SubSystem_Graphics_Renderer_Software_SourceFiles}
	${FinalPlatformRenderer_SourceFiles}
	${SubSystem_Input_SourceFiles}
	${SubSystem_IO_SourceFiles}
	${SubSystem_Logging_SourceFiles}
	${SubSystem_Math_SourceFiles}
	${SubSystem_OS_SourceFiles}
	${SubSystem_Resources_SourceFiles}
	${SubSystem_SceneManagement_SourceFiles}
	${SubSystem_DataModel_SourceFiles}
	${SubSystem_Behaviour_SourceFiles}
	${SubSystem_Network_SourceFiles}
)

 target_link_libraries(MagusEngine ${LIBS})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MagusEngine)

source_group("engine" FILES
	${Engine_SourceFiles}
)

source_group("subsystems\\external" FILES
	${SubSystem_External_SourceFiles}
)

source_group("subsystems\\graphics" FILES
	${SubSystem_Graphics_SourceFiles}
)

source_group("subsystems\\graphics\\primitives" FILES
	${SubSystem_Graphics_Primitives_SourceFiles}
)

source_group("subsystems\\graphics\\renderers" FILES
	${SubSystem_Graphics_Renderer_SourceFiles}
)

if(WIN32)
	source_group("subsystems\\graphics\\renderers\\windows\\" FILES
		${SubSystem_Graphics_Renderer_Windows_SourceFiles}
	)
else()
	source_group("subsystems\\graphics\\renderers\\linux\\" FILES
		${SubSystem_Graphics_Renderer_Linux_SourceFiles}
	)
endif()

source_group("subsystems\\graphics\\renderers\\software" FILES
	${SubSystem_Graphics_Renderer_Software_SourceFiles}
)

source_group("subsystems\\input" FILES
	${SubSystem_Input_SourceFiles}
)

source_group("subsystems\\io" FILES
	${SubSystem_IO_SourceFiles}
)

source_group("subsystems\\logging" FILES
	${SubSystem_Logging_SourceFiles}
)

source_group("subsystems\\math" FILES
	${SubSystem_Math_SourceFiles}
)

source_group("subsystems\\os" FILES
	${SubSystem_OS_SourceFiles}
)

source_group("subsystems\\resources" FILES
	${SubSystem_Resources_SourceFiles}
)

source_group("subsystems\\scenemanagement" FILES
	${SubSystem_SceneManagement_SourceFiles}
)

source_group("subsystems\\datamodel" FILES
	${SubSystem_DataModel_SourceFiles}
)

source_group("subsystems\\behaviour" FILES
	${SubSystem_Behaviour_SourceFiles}
)

source_group("subsystems\\network" FILES
	${SubSystem_Network_SourceFiles}
)


include_directories(${CMAKE_SOURCE_DIR}/external/includes)
