#include "chunk.h"

//-------------------------------------------------------------------------------------
Chunk::Chunk() {
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            for (int z = 0; z < 16; z++) {
                blocks[x][y][z] = Solid; 
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
//!hard coded for a single chunk 
//todo: FIX!!!!! 
//-------------------------------------------------------------------------------------
void Chunk::draw(Shader mainShader) {
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            for (int z = 0; z < 16; z++) {
                bool isExposed = 
                    getBlock(x+1, y, z) == Air ||
                    getBlock(x-1, y, z) == Air ||
                    getBlock(x, y+1, z) == Air ||
                    getBlock(x, y-1, z) == Air ||
                    getBlock(x, y, z+1) == Air ||
                    getBlock(x, y, z-1) == Air;
                if (!isExposed) continue;

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(x, y , z));
                mainShader.setMat4("model", model);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
    }
}
//-------------------------------------------------------------------------------------