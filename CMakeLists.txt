cmake_minimum_required(VERSION 3.0)
project(mygame)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(mygame/vendor/glfw)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(mygame/vendor/assimp)

option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(mygame/include/
                    mygame/vendor/assimp/include/
                    mygame/vendor/glad/include/
                    mygame/vendor/glfw/include/
                    mygame/vendor/glm/
                    mygame/vendor/stb/)

file(GLOB VENDORS_SOURCES mygame/vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS mygame/include/*.hpp)
file(GLOB PROJECT_SOURCES mygame/src/*.cpp)
file(GLOB PROJECT_ASSETS  mygame/assets/*.comp
                          mygame/assets/*.frag
                          mygame/assets/*.geom
                          mygame/assets/*.vert
                          mygame/assets/*.bmp
                          mygame/assets/*.png)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          README.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("include" FILES ${PROJECT_HEADERS})
source_group("assets" FILES ${PROJECT_ASSETS})
source_group("src" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_ASSETS} ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES})
target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
