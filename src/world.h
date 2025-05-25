#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "chunk.h"

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
    void unloadChunks(const glm::vec3& cameraPos, glm::ivec3 cameraChunkPos);
private:
    const static int WORLD_SIZE = 256;
    const static int RENDER_DISTANCE = 2;
    const static int UNLOAD_DISTANCE = 4;
    std::unordered_map<glm::ivec3, Chunk, ivec3_hash> chunks;
};