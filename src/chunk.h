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
    //variables
    static const int CHUNK_SIZE = 16;
    BlockType blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    int xCoord, yCoord, zCoord;

    //functions
    Chunk(int xcoord, int ycoord, int zcoord);
    ~Chunk();
    void draw(Shader mainShader) const; 
    BlockType getBlock(int x, int y, int z) const;
};
