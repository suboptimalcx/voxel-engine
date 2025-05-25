CMAKE_MINIMUM_REQUIRED(VERSION 3.30)

set(CMAKE_CXX_STANDARD 17)

PROJECT(voxel-engine)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

ADD_EXECUTABLE(voxel-engine
    src/main.cpp
    src/application.cpp
    src/texture.cpp
    src/stb_image.h
    src/shader.h
    src/camera.h
    src/chunk.cpp
    src/world.cpp
    src/FastNoiseLite.h
)

target_link_libraries(voxel-engine PRIVATE glfw glad::glad glm::glm)