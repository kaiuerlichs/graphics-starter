cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 17)


project(app)


set(SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        src/shaders/basic.vert
        src/shaders/basic.frag
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/src/wrapper_glfw.cpp
)

add_executable(app ${SOURCE_FILES})


set(SHADER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders)
set(SHADER_DEST_DIR ${CMAKE_BINARY_DIR}/shaders)
add_custom_target(shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADER_SOURCE_DIR} ${SHADER_DEST_DIR}
)
add_dependencies(app shaders)


find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)


add_library(glad STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/src/glad.c
)
target_include_directories(glad PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include/glad
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include/KHR
)
target_link_libraries(glad PRIVATE
    ${OPENGL_LIBRARIES}
)


target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include/glad
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include/KHR
    ${OPENGL_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS}
)

target_link_libraries(app PRIVATE
    glad
    glfw
    glm::glm
    ${OPENGL_LIBRARIES}
)