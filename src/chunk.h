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
    Chunk();
    ~Chunk();
    void draw(Shader mainShader);
    BlockType getBlock(int x, int y, int z) const;

private:
    BlockType blocks[16][16][16];
};
