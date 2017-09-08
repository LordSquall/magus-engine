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

# subsystem - math
set(SubSystem_Math_SourceFiles
	src/subsystems/math/vector.cpp
	src/subsystems/math/matrix.cpp
)	

# subsystem - os
set(SubSystem_OS_SourceFiles
	# pure abstracted sub system
)	

# subsystem - graphics
set(SubSystem_Graphics_SourceFiles
	src/subsystems/graphics/graphics.cpp
	src/subsystems/graphics/shader.cpp
)

# subsystem - graphics - renderer
set(SubSystem_Graphics_Renderer_SourceFiles
	src/subsystems/graphics/renderers/renderer_software.cpp
)


# subsystem - graphics - renderer - software
set(SubSystem_Graphics_Renderer_Software_SourceFiles
	src/subsystems/graphics/renderers/software/sr_framebuffer.cpp
	src/subsystems/graphics/renderers/software/sr_scanbuffer.cpp
	src/subsystems/graphics/renderers/software/sr_bitmap.cpp
	src/subsystems/graphics/renderers/software/sr_vertex.cpp
)

# subsystem - input
set(SubSystem_Input_SourceFiles
src/subsystems/input/input.cpp
)	

# subsystem - scenemanagement
set(SubSystem_SceneManagement_SourceFiles
	src/subsystems/scenemanagement/scenenode.cpp
)

# subsystem - external
set(SubSystem_External_SourceFiles
	src/subsystems/external/tinyxml2/tinyxml2.cpp
)

#depending on OS add relevent source files
MESSAGE("CMAKE_SYSTEM_NAME:         " ${CMAKE_SYSTEM_NAME} )
if(WIN32)
	set(SubSystem_OS_SourceFiles
		${SubSystem_OS_SourceFiles}
		src/subsystems/os/os_windows.cpp
	)
	
	set(SubSystem_Graphics_Renderer_SourceFiles
		${SubSystem_Graphics_Renderer_SourceFiles}		
		src/subsystems/graphics/renderers/renderer_windows_opengl.cpp
	)
	
else()
	set(SubSystem_OS_SourceFiles
		${SubSystem_OS_SourceFiles}
		src/subsystems/os/os_linux.cpp
	)
	
	set(SubSystem_Graphics_Renderer_SourceFiles
		${SubSystem_Graphics_Renderer_SourceFiles}		
		src/subsystems/graphics/renderers/renderer_linux_opengl.cpp
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

# add the executable
add_executable(MagusEngine
	${Engine_SourceFiles}
	${SubSystem_Math_SourceFiles}
	${SubSystem_OS_SourceFiles}
	${SubSystem_Graphics_SourceFiles}
	${SubSystem_Graphics_Renderer_SourceFiles}
	${SubSystem_Graphics_Renderer_Software_SourceFiles}
	${SubSystem_Input_SourceFiles}
	${SubSystem_SceneManagement_SourceFiles}
	${SubSystem_External_SourceFiles}
)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MagusEngine)

source_group("engine" FILES
	${Engine_SourceFiles}
)

source_group("subsystems\\math" FILES
	${SubSystem_Math_SourceFiles}
)

source_group("subsystems\\os" FILES
	${SubSystem_OS_SourceFiles}
)

source_group("subsystems\\graphics" FILES
	${SubSystem_Graphics_SourceFiles}
)

source_group("subsystems\\graphics\\renderers" FILES
	${SubSystem_Graphics_Renderer_SourceFiles}
)

source_group("subsystems\\graphics\\renderers\\software" FILES
	${SubSystem_Graphics_Renderer_Software_SourceFiles}
)

source_group("subsystems\\input" FILES
	${SubSystem_Input_SourceFiles}
)

source_group("subsystems\\scenemanagement" FILES
	${SubSystem_SceneManagement_SourceFiles}
)

source_group("subsystems\\external" FILES
	${SubSystem_External_SourceFiles}
)