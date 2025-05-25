#include "world.h"

//-------------------------------------------------------------------------------------
World::World() {
    for (int x = -WORLD_SIZE/2; x < WORLD_SIZE/2; x++) {
        for (int z = -WORLD_SIZE/2; z < WORLD_SIZE/2; z++) {
            chunks.emplace_back(x, -1, z);
        }
    }
}
//-------------------------------------------------------------------------------------
World::~World(){}
//-------------------------------------------------------------------------------------
const void World::draw(const glm::vec3& cameraPos, Shader mainShader) {
    for (const Chunk& chunk : chunks) {
        // center pos
        // ----------
        glm::vec3 chunkCenter = glm::vec3(
            chunk.xCoord * Chunk::CHUNK_SIZE + Chunk::CHUNK_SIZE / 2.0f,
            chunk.yCoord * Chunk::CHUNK_SIZE + Chunk::CHUNK_SIZE / 2.0f,
            chunk.zCoord * Chunk::CHUNK_SIZE + Chunk::CHUNK_SIZE / 2.0f
        );

        float distance = glm::distance(cameraPos, chunkCenter);

        if (distance <= RENDER_DISTANCE * Chunk::CHUNK_SIZE) {
            chunk.draw(mainShader);
        }
    }
}
//-------------------------------------------------------------------------------------