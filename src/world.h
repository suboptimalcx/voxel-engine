#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "chunk.h"
#include <vector>
#include <unordered_map>

//crazy hash function
struct ivec3_hash {
    std::size_t operator()(const glm::ivec3& v) const {
        return std::hash<int>()(v.x) ^ std::hash<int>()(v.y << 1) ^ std::hash<int>()(v.z << 2);
    }
};

class World{
public:
    World();
    ~World();
    void draw(const glm::vec3& cameraPos, Shader mainShader);
private:
    const static int WORLD_SIZE = 256;
    const static int RENDER_DISTANCE = 2;
    std::unordered_map<glm::ivec3, Chunk, ivec3_hash> chunks;
};