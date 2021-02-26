cmake_minimum_required(VERSION 3.16)

project(OglBib)

add_executable(ogl_bib main.cpp)

target_include_directories(ogl_bib PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/glad/include")
target_sources(ogl_bib PRIVATE ${PROJECT_SOURCE_DIR}/glad/src/glad.c)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${PROJECT_SOURCE_DIR}/glfw)
target_link_libraries(ogl_bib glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(ogl_bib OpenGL::GL)

