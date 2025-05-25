#include "chunk.h"

//-------------------------------------------------------------------------------------
Chunk::Chunk(int xcoord, int ycoord, int zcoord) {
    xCoord = xcoord; yCoord = ycoord; zCoord = zcoord;

    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetSeed(2137); 
    noise.SetFrequency(0.05f);

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                float worldX = xCoord * CHUNK_SIZE + x;
                float worldY = yCoord * CHUNK_SIZE + y;
                float worldZ = zCoord * CHUNK_SIZE + z;

                float noiseValue = noise.GetNoise(worldX, worldY, worldZ);
                noiseValue > 0.0f ? blocks[x][y][z] = Solid : blocks[x][y][z] = Air;
            }
        }
    }
}
//-------------------------------------------------------------------------------------
Chunk::~Chunk(){} //add cleanup if chunks will have vaos vbos (which they propably wont lol)
//-------------------------------------------------------------------------------------
BlockType Chunk::getBlock(int x, int y, int z) const {
    if (x < 0 || x >= 16 || y < 0 || y >= 16 || z < 0 || z >= 16) // oob 
        return Air; 
    return blocks[x][y][z];
}
//-------------------------------------------------------------------------------------
//!  this function treats everything outside of this chunk as Air, will have to fix when adding face culling
void Chunk::draw(Shader mainShader) const {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                // Only draw blocks adjacent to Air
                if (blocks[x][y][z] == Air) continue;

                if (!(getBlock(x + 1, y, z) == Air ||
                      getBlock(x - 1, y, z) == Air ||
                      getBlock(x, y + 1, z) == Air ||
                      getBlock(x, y - 1, z) == Air ||
                      getBlock(x, y, z + 1) == Air ||
                      getBlock(x, y, z - 1) == Air)) {
                    continue;
                }

                glm::vec3 worldPos = glm::vec3(
                    xCoord * CHUNK_SIZE + x,
                    yCoord * CHUNK_SIZE + y,
                    zCoord * CHUNK_SIZE + z
                );

                glm::mat4 model = glm::translate(glm::mat4(1.0f), worldPos);
                mainShader.setMat4("model", model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
    }
}
//-------------------------------------------------------------------------------------