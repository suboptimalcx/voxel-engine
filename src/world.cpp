#include "world.h"

//-------------------------------------------------------------------------------------
World::World() {}
//-------------------------------------------------------------------------------------
World::~World(){}
//-------------------------------------------------------------------------------------
void World::draw(const glm::vec3& cameraPos, Shader mainShader) {
    glm::ivec3 cameraChunkPos = glm::floor(cameraPos / (float)Chunk::CHUNK_SIZE);

    for (int x = -RENDER_DISTANCE; x <= RENDER_DISTANCE; x++) {
        for (int z = -RENDER_DISTANCE; z <= RENDER_DISTANCE; z++) {
            glm::ivec3 chunkCoord = glm::ivec3(cameraChunkPos.x + x, -1, cameraChunkPos.z + z);

            if (chunks.find(chunkCoord) == chunks.end()) {
                // insert new chunk only if it doesnt exist
                // ----------------------------------------------------
                chunks.emplace(chunkCoord, Chunk(chunkCoord.x, chunkCoord.y, chunkCoord.z));
            }

            Chunk& chunk = chunks.at(chunkCoord);

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
    unloadChunks(cameraPos, cameraChunkPos);
}
//-------------------------------------------------------------------------------------
void World::unloadChunks(const glm::vec3& cameraPos, glm::ivec3 cameraChunkPos) {
    std::vector<glm::ivec3> chunksToRemove;

    for (const auto& pair : chunks) {
        const glm::ivec3& coord = pair.first;
        glm::vec3 chunkCenter = glm::vec3(
            coord.x * Chunk::CHUNK_SIZE + Chunk::CHUNK_SIZE / 2.0f,
            coord.y * Chunk::CHUNK_SIZE + Chunk::CHUNK_SIZE / 2.0f,
            coord.z * Chunk::CHUNK_SIZE + Chunk::CHUNK_SIZE / 2.0f
        );

        float distance = glm::distance(cameraPos, chunkCenter);
        if (distance > UNLOAD_DISTANCE * Chunk::CHUNK_SIZE) {
            chunksToRemove.push_back(coord);
        }
    }

    for (const glm::ivec3& coord : chunksToRemove) {
        chunks.erase(coord);
    }
}