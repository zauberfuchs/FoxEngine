cmake_minimum_required(VERSION 3.8)


project(FoxEngine)

set(CMAKE_CXX_STANDARD 11)

include_directories("../common")


set(HEADER_FILES 	
	"../common/utils.h"
	"../common/IndexBuffer.h"
	"../common/VertexBuffer.h"
	"../common/VertexBufferLayout.h"
	"../common/Texture.h"
	"../common/Shader.h"
	"../common/VertexArray.h"
	"../common/Framebuffer.h"
	"../common/Renderbuffer.h"
	"../common/Cube.h"
	"../common/CubeMap.h"
	"../common/Mesh.h"
	"../common/IMesh.h"
	"../common/Square.h"
	"../common/Camera.h"
	"../common/Model.h"
	"../common/ISceneObject.h"
	)

set(DATA_SRC "../../Data")

# Find *all* shaders.
file(GLOB_RECURSE SHADERS
	"${DATA_SRC}/*.frag"
	"${DATA_SRC}/*.vert"
	)

##file(GLOB ROOT_NAT ../util/glm.natvis)

# Separate filter for shaders.
source_group("Shaders" FILES ${SHADERS})

set(SOURCE_FILES
	"src/main.cpp"	
	"../common/IndexBuffer.cpp"
	"../common/VertexBuffer.cpp"
	"../common/Cube.cpp"
	"../common/CubeMap.cpp"
	"../common/Square.cpp"
	"../common/Texture.cpp"
	"../common/Mesh.cpp"
	"../common/Shader.cpp"
	"../common/VertexArray.cpp"
	"../common/Framebuffer.cpp"
	"../common/Renderbuffer.cpp"
	"../common/Camera.cpp"
	"../common/Model.cpp"
	)

set(OPEN_GL_FILES 	
	glu32
	opengl32
	)
find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

# Build and link executable.
add_executable(
	${PROJECT_NAME}
	${SHADERS}
	${HEADER_FILES}
	${SOURCE_FILES}
	../common/utils/glm.natvis
	)

if(WIN32)
	target_link_libraries(${PROJECT_NAME}
		PRIVATE glm::glm
		PRIVATE GLEW::GLEW
		PRIVATE glfw
		PRIVATE imgui::imgui
		${OPEN_GL_FILES}
		PRIVATE assimp::assimp
		)
		
else()
	target_link_libraries(${PROJECT_NAME}
		PRIVATE glm::glm
		PRIVATE GLEW::GLEW
		PRIVATE glfw
		PRIVATE imgui::imgui
		PRIVATE assimp::assimp
		GL
		GLU		
		)
	
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD				# Adds a post-build event to MyTest
	COMMAND ${CMAKE_COMMAND} -E copy_if_different					# which executes "cmake - E copy_if_different..."
		"../../../vcpkg/installed/x64-windows/bin/glew32.dll"		# <--this is in-file
		"../../../bin")												# <--this is out-file path

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD				# Adds a post-build event to MyTest
	COMMAND ${CMAKE_COMMAND} -E copy_if_different					# which executes "cmake - E copy_if_different..."
		"../../../vcpkg/installed/x64-windows/bin/glfw3.dll"		# <--this is in-file
		"../../../bin")												# <--this is out-file path


## set working directory to bin directory
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "../../../bin")

## set the startup project to the current project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
