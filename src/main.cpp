#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <filesystem>
#include "Mesh.h"
#include "Model.h"
#include <stack>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::stack<glm::mat4> matrixStack;

void pushMatrix(const glm::mat4& matrix) {
    matrixStack.push(matrix);
}

glm::mat4 popMatrix() {
    glm::mat4 top = matrixStack.top();
    matrixStack.pop();
    return top;
}

namespace fs = std::filesystem;

const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates
std::vector<Vertex> verticesPlan = {
    // Front face
    //       posição             vetor normal            cor                 textura
    {{ -10.0f, -1.0f,  -10.0f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  10.0f, -1.0f,  -10.0f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  10.0f,  0.0f,  10.0f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -10.0f,  0.0f,  10.0f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

};

// Indices for vertices order
std::vector<GLuint> indicesPlan = {
    // Front face
    0, 1, 2,
    0, 2, 3,
};


// Peitoral
std::vector<Vertex> verticesChest = {
    // Front face
    //       posição             vetor normal            cor                 textura
    {{ -1.5f, 2.0f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  1.5f, 2.0f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  1.5f,  3.5f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.5f,  3.5f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Back face
    {{ -1.5f, 2.0f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  1.5f, 2.0f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  1.5f,  3.5f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.5f,  3.5f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Left face
    {{ -1.5f, 2.0f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{ -1.5f, 2.0f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{ -1.5f,  3.5f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.5f,  3.5f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Right face
    {{  1.5f, 2.0f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  1.5f, 2.0f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  1.5f,  3.5f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{  1.5f,  3.5f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Top face
    {{ -1.5f,  3.5f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  1.5f,  3.5f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  1.5f,  3.5f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.5f,  3.5f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Bottom face
    {{ -1.5f, 2.0f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  1.5f, 2.0f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  1.5f, 2.0f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.5f, 2.0f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}  // Top-left
};

// Indices for vertices order
std::vector<GLuint> indicesChest = {
    // Front face
    0, 1, 2,
    0, 2, 3,
    // Back face
    4, 5, 6,
    4, 6, 7,
    // Left face
    8, 9, 10,
    8, 10, 11,
    // Right face
    12, 13, 14,
    12, 14, 15,
    // Top face
    16, 17, 18,
    16, 18, 19,
    // Bottom face
    20, 21, 22,
    20, 22, 23
};

// 'barriga' -> refazer quase o mesmo que foi feito acima
std::vector<Vertex> verticesHead = {
    // Front face
    //       posição             vetor normal            cor                 textura
    {{ -0.5f, 3.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.5f, 3.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.5f,  4.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -0.5f,  4.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Back face
    {{ -0.5f, 3.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.5f, 3.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.5f,  4.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -0.5f,  4.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Left face
    {{ -0.5f, 3.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{ -0.5f, 3.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{ -0.5f,  4.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -0.5f,  4.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Right face
    {{  0.5f, 3.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.5f, 3.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.5f,  4.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{  0.5f,  4.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Top face
    {{ -0.5f,  4.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.5f,  4.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.5f,  4.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -0.5f,  4.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Bottom face
    {{ -0.5f, 3.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.5f, 3.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.5f, 3.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -0.5f, 3.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}  // Top-left
};

std::vector<GLuint> indicesHead = {
    // Front face
    0, 1, 2,
    0, 2, 3,
    // Back face
    4, 5, 6,
    4, 6, 7,
    // Left face
    8, 9, 10,
    8, 10, 11,
    // Right face
    12, 13, 14,
    12, 14, 15,
    // Top face
    16, 17, 18,
    16, 18, 19,
    // Bottom face
    20, 21, 22,
    20, 22, 23
};

// pescoço

// 'barriga' -> refazer quase o mesmo que foi feito acima
std::vector<Vertex> verticesStomach = {
    // Front face
    //       posição             vetor normal            cor                 textura
    {{ -1.3f, -0.5f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  1.3f, -0.5f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  1.3f,  2.0f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.3f,  2.0f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Back face
    {{ -1.3f, -0.5f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  1.3f, -0.5f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  1.3f,  2.0f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.3f,  2.0f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Left face
    {{ -1.3f, -0.5f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{ -1.3f, -0.5f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{ -1.3f,  2.0f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.3f,  2.0f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Right face
    {{  1.3f, -0.5f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  1.3f, -0.5f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  1.3f,  2.0f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{  1.3f,  2.0f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Top face
    {{ -1.3f,  2.0f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  1.3f,  2.0f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  1.3f,  2.0f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.3f,  2.0f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Bottom face
    {{ -1.3f, -0.5f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  1.3f, -0.5f, -0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  1.3f, -0.5f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.3f, -0.5f,  0.75f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}  // Top-left
};

std::vector<GLuint> indicesStomach = {
    // Front face
    0, 1, 2,
    0, 2, 3,
    // Back face
    4, 5, 6,
    4, 6, 7,
    // Left face
    8, 9, 10,
    8, 10, 11,
    // Right face
    12, 13, 14,
    12, 14, 15,
    // Top face
    16, 17, 18,
    16, 18, 19,
    // Bottom face
    20, 21, 22,
    20, 22, 23
};

// braço esquerdo
std::vector<Vertex> verticesLeftArm1 = {
    // Front face
    //       posição             vetor normal            cor                 textura
    {{ 1.5f, 1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  2.25f, 1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  2.25f,  3.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.5f,  3.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Back face
    {{  1.5f, 1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  2.25f, 1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  2.25f,  3.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{  1.5f,  3.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Left face
    {{ 1.5f, 1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{ 1.5f, 1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{ 1.5f,  3.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.5f,  3.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Right face
    {{  2.25f, 1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  2.25f, 1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  2.25f,  3.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{  2.25f,  3.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Top face
    {{ 1.5f,  3.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  2.25f,  3.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  2.25f,  3.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.5f,  3.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Bottom face
    {{ 1.5f, 1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  2.25f, 1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  2.25f, 1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.5f, 1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}  // Top-left
};

std::vector<GLuint> indicesLeftArm1 = {
    // Front face
    0, 1, 2,
    0, 2, 3,
    // Back face
    4, 5, 6,
    4, 6, 7,
    // Left face
    8, 9, 10,
    8, 10, 11,
    // Right face
    12, 13, 14,
    12, 14, 15,
    // Top face
    16, 17, 18,
    16, 18, 19,
    // Bottom face
    20, 21, 22,
    20, 22, 23
};

std::vector<Vertex> verticesLeftArm2 = {
    // Front face
    //       posição             vetor normal            cor                 textura
    {{ 1.5f, 0.0f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  2.25f, 0.0f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  2.25f,  1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.5f,  1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Back face
    {{  1.5f, 0.0f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  2.25f, 0.0f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  2.25f,  1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{  1.5f,  1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Left face
    {{ 1.5f, 0.0f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{ 1.5f, 0.0f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{ 1.5f,  1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.5f,  1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Right face
    {{  2.25f, 0.0f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  2.25f, 0.0f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  2.25f,  1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{  2.25f,  1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Top face
    {{ 1.5f,  0.0f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  2.25f,  0.0f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  2.25f,  0.0f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.5f,  0.0f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Bottom face
    {{ 1.5f, 1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  2.25f, 1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  2.25f, 1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.5f, 1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}  // Top-left
};

std::vector<GLuint> indicesLeftArm2 = {
    // Front face
    0, 1, 2,
    0, 2, 3,
    // Back face
    4, 5, 6,
    4, 6, 7,
    // Left face
    8, 9, 10,
    8, 10, 11,
    // Right face
    12, 13, 14,
    12, 14, 15,
    // Top face
    16, 17, 18,
    16, 18, 19,
    // Bottom face
    20, 21, 22,
    20, 22, 23
};

// braço direito
std::vector<Vertex> verticesRightArm1 = {
    // Front face
    //       posição             vetor normal            cor                 textura
    {{ -1.5f, 1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -2.25f, 1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -2.25f,  3.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.5f,  3.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Back face
    {{  -1.5f, 1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -2.25f, 1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -2.25f,  3.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{  -1.5f,  3.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Left face
    {{ -1.5f, 1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{ -1.5f, 1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{ -1.5f,  3.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.5f,  3.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Right face
    {{  -2.25f, 1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -2.25f, 1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -2.25f,  3.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{  -2.25f,  3.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Top face
    {{ -1.5f,  3.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -2.25f,  3.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -2.25f,  3.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.5f,  3.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Bottom face
    {{ -1.5f, 1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -2.25f, 1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -2.25f, 1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.5f, 1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}  // Top-left
};

std::vector<GLuint> indicesRightArm1 = {
    // Front face
    0, 1, 2,
    0, 2, 3,
    // Back face
    4, 5, 6,
    4, 6, 7,
    // Left face
    8, 9, 10,
    8, 10, 11,
    // Right face
    12, 13, 14,
    12, 14, 15,
    // Top face
    16, 17, 18,
    16, 18, 19,
    // Bottom face
    20, 21, 22,
    20, 22, 23
};

std::vector<Vertex> verticesRightArm2 = {
    // Front face
    //       posição             vetor normal            cor                 textura
    {{ -1.5f, 0.0f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -2.25f, 0.0f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -2.25f,  1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.5f,  1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Back face
    {{  -1.5f, 0.0f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -2.25f, 0.0f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -2.25f,  1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{  -1.5f,  1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Left face
    {{ -1.5f, 0.0f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{ -1.5f, 0.0f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{ -1.5f,  1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.5f,  1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Right face
    {{  -2.25f, 0.0f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -2.25f, 0.0f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -2.25f,  1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{  -2.25f,  1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Top face
    {{ -1.5f,  0.0f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -2.25f,  0.0f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -2.25f,  0.0f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.5f,  0.0f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Bottom face
    {{ -1.5f, 1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -2.25f, 1.5f, -0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -2.25f, 1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.5f, 1.5f,  0.35f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}  // Top-left
};

std::vector<GLuint> indicesRightArm2 = {
    // Front face
    0, 1, 2,
    0, 2, 3,
    // Back face
    4, 5, 6,
    4, 6, 7,
    // Left face
    8, 9, 10,
    8, 10, 11,
    // Right face
    12, 13, 14,
    12, 14, 15,
    // Top face
    16, 17, 18,
    16, 18, 19,
    // Bottom face
    20, 21, 22,
    20, 22, 23
};

// perna direita
std::vector<Vertex> verticesRightLeg1 = {
    // Front face
    //       posição             vetor normal            cor                 textura
    {{ -1.3f, -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -0.2f, -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -0.2f,  -0.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.3f,  -0.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Back face
    {{ -1.3f, -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -0.2f, -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -0.2f,  -0.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.3f,  -0.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left
    
    // Left face
    {{ -1.3f, -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{ -1.3f, -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{ -1.3f,  -0.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.3f,  -0.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Right face
    {{  -0.2f, -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -0.2f, -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -0.2f,  -0.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{  -0.2f,  -0.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Top face
    {{ -1.3f,  -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -0.2f,  -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -0.2f,  -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.3f,  -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Bottom face
    {{ -1.3f, -0.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -0.2f, -0.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -0.2f, -0.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.3f, -0.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}  // Top-left
};

std::vector<GLuint> indicesRightLeg1 = {
    // Front face
    0, 1, 2,
    0, 2, 3,
    // Back face
    4, 5, 6,
    4, 6, 7,
    
    // Left face
    8, 9, 10,
    8, 10, 11,
    // Right face
    12, 13, 14,
    12, 14, 15,
    // Top face
    16, 17, 18,
    16, 18, 19,
    // Bottom face
    20, 21, 22,
    20, 22, 23
};

std::vector<Vertex> verticesRightLeg2 = {
    // Front face
    //       posição             vetor normal            cor                 textura
    {{ -1.3f, -5.0f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -0.2f, -5.0f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -0.2f,  -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.3f,  -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Back face
    {{ -1.3f, -5.0f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -0.2f, -5.0f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -0.2f,  -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.3f,  -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left
    
    // Left face
    {{ -1.3f, -5.0f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{ -1.3f, -5.0f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{ -1.3f,  -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.3f,  -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Right face
    {{  -0.2f, -5.0f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -0.2f, -5.0f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -0.2f,  -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{  -0.2f,  -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Top face
    {{ -1.3f,  -5.0f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -0.2f,  -5.0f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -0.2f,  -5.0f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.3f,  -5.0f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Bottom face
    {{ -1.3f, -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  -0.2f, -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  -0.2f, -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -1.3f, -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}  // Top-left
};

std::vector<GLuint> indicesRightLeg2 = {
    // Front face
    0, 1, 2,
    0, 2, 3,
    // Back face
    4, 5, 6,
    4, 6, 7,
    
    // Left face
    8, 9, 10,
    8, 10, 11,
    // Right face
    12, 13, 14,
    12, 14, 15,
    // Top face
    16, 17, 18,
    16, 18, 19,
    // Bottom face
    20, 21, 22,
    20, 22, 23
};


//perna esquerda
std::vector<Vertex> verticesLeftLeg1 = {
    // Front face
    //       posição             vetor normal            cor                 textura
    {{ 1.3f, -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.2f, -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.2f,  -0.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.3f,  -0.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Back face
    {{ 1.3f, -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.2f, -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.2f,  -0.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.3f,  -0.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left
    
    // Left face
    {{ 1.3f, -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{ 1.3f, -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{ 1.3f,  -0.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.3f,  -0.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Right face
    {{  0.2f, -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.2f, -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.2f,  -0.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{  0.2f,  -0.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Top face
    {{ 1.3f,  -0.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  1.3f,  -0.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  1.3f,  -0.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.3f,  -0.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Bottom face
    {{ 1.3f, -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.2f, -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.2f, -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.3f, -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}  // Top-left
};

std::vector<GLuint> indicesLeftLeg1 = {
    // Front face
    0, 1, 2,
    0, 2, 3,
    // Back face
    4, 5, 6,
    4, 6, 7,
    
    // Left face
    8, 9, 10,
    8, 10, 11,
    // Right face
    12, 13, 14,
    12, 14, 15,
    // Top face
    16, 17, 18,
    16, 18, 19,
    // Bottom face
    20, 21, 22,
    20, 22, 23
};

std::vector<Vertex> verticesLeftLeg2 = {
    // Front face
    //       posição             vetor normal            cor                 textura
    {{ 1.3f, -5.0f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.2f, -5.0f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.2f,  -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.3f,  -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Back face
    {{ 1.3f, -5.0f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.2f, -5.0f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.2f,  -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.3f,  -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left
    
    // Left face
    {{ 1.3f, -5.0f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{ 1.3f, -5.0f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{ 1.3f,  -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.3f,  -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Right face
    {{  0.2f, -5.0f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.2f, -5.0f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.2f,  -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{  0.2f,  -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Top face
    {{ 1.3f,  -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  1.3f,  -2.5f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  1.3f,  -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.3f,  -2.5f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Bottom face
    {{ 1.3f, -5.0f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.2f, -5.0f, -0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.2f, -5.0f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ 1.3f, -5.0f,  0.7f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}  // Top-left
};

std::vector<GLuint> indicesLeftLeg2 = {
    // Front face
    0, 1, 2,
    0, 2, 3,
    // Back face
    4, 5, 6,
    4, 6, 7,
    
    // Left face
    8, 9, 10,
    8, 10, 11,
    // Right face
    12, 13, 14,
    12, 14, 15,
    // Top face
    16, 17, 18,
    16, 18, 19,
    // Bottom face
    20, 21, 22,
    20, 22, 23
};




int main()
{
	
    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Load music
    Mix_Music* bgMusic = Mix_LoadMUS("../audios/terror_music.wav"); // Altere para o caminho do seu arquivo de áudio
    if (!bgMusic) {
        std::cerr << "Failed to load background music: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }

    // Play music
	/*
    if (Mix_PlayMusic(bgMusic, -1) == -1) {
        std::cerr << "Failed to play background music: " << Mix_GetError() << std::endl;
        Mix_FreeMusic(bgMusic);
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }
	*/

    // Initialize GLFW
    glfwInit();

    // Tell GLFW what version of OpenGL we are using 
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
    GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
    // Error check if the window fails to create
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current context
    glfwMakeContextCurrent(window);

    // Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, width, height);

    // Generates Shader object using shaders default.vert and default.frag
    Shader shaderProgram("../shaders/default.vert", "../shaders/default.frag");

    // Take care of all the light related things
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    shaderProgram.Activate();
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    // Enables the Depth Buffer
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

    // Creates camera object
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	std::string parentDir = (fs::current_path().fs::path::parent_path()).string();
	std::string groundPath = "/models/ground/scene.gltf";
	std::string treesPath = "/models/trees/scene.gltf";

	// Load in models
	Model ground((parentDir + groundPath).c_str());
	Model trees((parentDir + treesPath).c_str());

	// Cria uma textura vazia
    Texture texture("../textures/brick.png", "diffuse", 0);
    std::vector<Texture> textures = { texture };

    Texture texture2("../textures/planks.png","diffuse", 0);
    std::vector<Texture> textures2 = {texture2};

	// Cria o objeto Mesh para o cubo
    Mesh chest(verticesChest, indicesChest, textures); // aqui posso criar os outros objetos
    Mesh stomach(verticesStomach, indicesStomach, textures);
    Mesh plan(verticesPlan, indicesPlan, textures2);
    Mesh head(verticesHead, indicesHead, textures2);
    Mesh leftArm1(verticesLeftArm1, indicesLeftArm1, textures2);
    Mesh leftArm2(verticesLeftArm2, indicesLeftArm2, textures2);
    Mesh rightArm1(verticesRightArm1, indicesRightArm1, textures2);
    Mesh rightArm2(verticesRightArm2, indicesRightArm2, textures2);
    Mesh rightLeg1(verticesRightLeg1, indicesRightLeg1, textures2);
    Mesh rightLeg2(verticesRightLeg2, indicesRightLeg2, textures2);
    Mesh leftLeg1(verticesLeftLeg1, indicesLeftLeg1, textures2);
    Mesh leftLeg2(verticesLeftLeg2, indicesLeftLeg2, textures2);

	float angleChest = 0.0f;
    float angleRightArm = 0.0f;
    float angleLeftArm = 0.0f;

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.85f, 0.85f, 0.90f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 1000.0f);

        glm::mat4 model = glm::mat4(1.0f);

        // Atualiza ângulos
        angleChest += 0.1f;
        angleRightArm += 0.02f;
        angleLeftArm -= 0.02f;

        // Desenha o chão
        // plan.Draw(shaderProgram, camera, model, glm::vec3(0.0f, -3.0f, 0.0), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));

		// Draw models
		ground.Draw(shaderProgram, camera);
		trees.Draw(shaderProgram, camera);

        // Desenha o corpo (peito) com rotação
        pushMatrix(model);
        model = glm::rotate(model, glm::radians(angleChest), glm::vec3(0.0f, 1.0f, 0.0f));
        chest.Draw(shaderProgram, camera, model, glm::vec3(0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));

        // Desenha a cabeça
        pushMatrix(model);
        // Posição relativa à rotação do peito
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        head.Draw(shaderProgram, camera, model, glm::vec3(0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
        model = popMatrix();

        // Desenha os braços como filhos do peito
        pushMatrix(model);

        // Desenha o braço esquerdo com rotação
        pushMatrix(model);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Ajuste a posição relativa ao peito
        model = glm::rotate(model, glm::radians(angleLeftArm), glm::vec3(0.0f, 0.0f, 1.0f));
        leftArm1.Draw(shaderProgram, camera, model, glm::vec3(0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
        leftArm2.Draw(shaderProgram, camera, model, glm::vec3(0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
        model = popMatrix();

        // Desenha o braço direito com rotação
        pushMatrix(model);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Ajuste a posição relativa ao peito
        model = glm::rotate(model, glm::radians(angleRightArm), glm::vec3(0.0f, 0.0f, 1.0f));
        rightArm1.Draw(shaderProgram, camera, model, glm::vec3(0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
        rightArm2.Draw(shaderProgram, camera, model, glm::vec3(0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
        model = popMatrix();

        model = popMatrix();

        // Desenha a barriga
        pushMatrix(model);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        stomach.Draw(shaderProgram, camera, model, glm::vec3(0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));

        // Desenha as pernas como filhas da barriga
        pushMatrix(model);

        // Desenha a perna direita
        pushMatrix(model);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Ajuste a posição relativa à barriga
        rightLeg1.Draw(shaderProgram, camera, model, glm::vec3(0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
        rightLeg2.Draw(shaderProgram, camera, model, glm::vec3(0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
        model = popMatrix();

        // Desenha a perna esquerda
        pushMatrix(model);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // Ajuste a posição relativa à barriga
        leftLeg1.Draw(shaderProgram, camera, model, glm::vec3(0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
        leftLeg2.Draw(shaderProgram, camera, model, glm::vec3(0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));
        model = popMatrix();

        model = popMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Delete all the objects we've created
    shaderProgram.Delete();
    // Delete window before ending the program
    glfwDestroyWindow(window);
    // Terminate GLFW before ending the program
    glfwTerminate();

    // Free resources and quit SDL
    Mix_FreeMusic(bgMusic);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
