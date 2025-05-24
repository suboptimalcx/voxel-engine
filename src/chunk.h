#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

enum BlockType {
    Air,
    Solid
};

class Chunk {
public:
    Chunk(int xcoord, int ycoord, int zcoord);
    ~Chunk();
    void draw(Shader mainShader);
    BlockType getBlock(int x, int y, int z) const;

private:
    static const unsigned int CHUNK_SIZE = 16;
    BlockType blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    int xCoord, yCoord, zCoord;
};
