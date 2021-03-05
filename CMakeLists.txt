cmake_minimum_required(VERSION 3.16)

project(OglBib)
file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

set(TARGET_NAME ogl_bib)

add_executable(${TARGET_NAME} ${SOURCES})
target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)

target_include_directories(${TARGET_NAME} PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/libs/glad/include")

target_sources(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/libs/glad/src/glad.c)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${PROJECT_SOURCE_DIR}/libs/glfw)
target_link_libraries(${TARGET_NAME} glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(${TARGET_NAME} OpenGL::GL)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
