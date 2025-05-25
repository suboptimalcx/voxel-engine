#include "chunk.h"

//-------------------------------------------------------------------------------------
Chunk::Chunk(int xcoord, int ycoord, int zcoord) {
    xCoord = xcoord; yCoord = ycoord; zCoord = zcoord;  
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
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
//-------------------------------------------------------------------------------------
void Chunk::draw(Shader mainShader) const {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                if (!(getBlock(x+1,y,z)==Air ||
                      getBlock(x-1,y,z)==Air ||
                      getBlock(x,y+1,z)==Air ||
                      getBlock(x,y-1,z)==Air ||
                      getBlock(x,y,z+1)==Air ||
                      getBlock(x,y,z-1)==Air))
                    continue;

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