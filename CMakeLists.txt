CMAKE_MINIMUM_REQUIRED(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)

PROJECT(voxel-engine)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Add include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/core
    ${PROJECT_SOURCE_DIR}/src/graphics
    ${PROJECT_SOURCE_DIR}/src/world
    ${PROJECT_SOURCE_DIR}/src/external
)

ADD_EXECUTABLE(voxel-engine
    src/core/main.cpp
    src/core/application.cpp
    src/graphics/texture.cpp
    src/external/stb_image.h
    src/graphics/shader.h
    src/world/camera.h
    src/world/chunk.cpp
    src/world/world.cpp
    src/external/FastNoiseLite.h
)

target_link_libraries(voxel-engine PRIVATE glfw glad::glad glm::glm)