#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "chunk.h"
#include <vector>

class World{
public:
    World();
    ~World();
    const void draw(const glm::vec3& cameraPos, Shader mainShader);
private:
    const static int WORLD_SIZE = 16;
    const static int RENDER_DISTANCE = 2;
    std::vector<Chunk> chunks;
};