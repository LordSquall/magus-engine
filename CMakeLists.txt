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
)	

# subsystem - system
set(SubSystem_System_SourceFiles
	src/subsystems/systems/systemclass.cpp
)	

# subsystem - graphics
set(SubSystem_Graphics_SourceFiles
	src/subsystems/graphics/graphicsclass.cpp
	src/subsystems/graphics/rendererclass.cpp
)

# subsystem - input
set(SubSystem_Input_SourceFiles
src/subsystems/input/inputclass.cpp
)	

# subsystem - scenemanagement
set(SubSystem_SceneManagement_SourceFiles
	src/subsystems/scenemanagement/scenenodeclass.cpp
)	

#depending on OS add relevent source files
MESSAGE("CMAKE_SYSTEM_NAME:         " ${CMAKE_SYSTEM_NAME} )
if(WIN32)
	set(SubSystem_System_SourceFiles
		${SubSystem_System_SourceFiles}
		src/subsystems/systems/windowsclass.cpp
	)
	
	set(SubSystem_Graphics_SourceFiles
		${SubSystem_Graphics_SourceFiles}		
		src/subsystems/graphics/openglwindowsclass.cpp
	)
	
else()
	set(SubSystem_System_SourceFiles
		${SubSystem_System_SourceFiles}
		src/subsystems/systems/linuxclass.cpp
	)
	
	set(SubSystem_Graphics_SourceFiles
		${SubSystem_Graphics_SourceFiles}		
		src/subsystems/graphics/opengllinuxclass.cpp
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
	${SubSystem_System_SourceFiles}
	${SubSystem_Graphics_SourceFiles}
	${SubSystem_Input_SourceFiles}
	${SubSystem_SceneManagement_SourceFiles}
)

source_group("engine" FILES
	${Engine_SourceFiles}
)

source_group("subsystems\\systems" FILES
	${SubSystem_System_SourceFiles}
)

source_group("subsystems\\graphics" FILES
	${SubSystem_Graphics_SourceFiles}
)

source_group("subsystems\\input" FILES
	${SubSystem_Input_SourceFiles}
)

source_group("subsystems\\scenemanagement" FILES
	${SubSystem_SceneManagement_SourceFiles}
)