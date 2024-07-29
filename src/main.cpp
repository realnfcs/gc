#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <filesystem>
#include "Mesh.h"

namespace fs = std::filesystem;

const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates
std::vector<Vertex> vertices = {
    // Front face
    {{ -0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Back face
    {{ -0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Left face
    {{ -0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{ -0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{ -0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Right face
    {{  0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{  0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Top face
    {{ -0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}, // Top-left

    // Bottom face
    {{ -0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 0.0f }}, // Bottom-left
    {{  0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 0.0f }}, // Bottom-right
    {{  0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {1.0f, 1.0f }}, // Top-right
    {{ -0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, -1.0f}, {0.83f, 0.70f, 0.44f},  {0.0f, 1.0f }}  // Top-left
};

// Indices for vertices order
std::vector<GLuint> indices = {
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
    if (Mix_PlayMusic(bgMusic, -1) == -1) {
        std::cerr << "Failed to play background music: " << Mix_GetError() << std::endl;
        Mix_FreeMusic(bgMusic);
        Mix_CloseAudio();
        SDL_Quit();
        return -1;
    }

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

    // Creates camera object
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Cria uma textura vazia
    Texture texture("../textures/brick.png", "diffuse", 0);
    std::vector<Texture> textures = { texture };

	// Cria o objeto Mesh para o cubo
    Mesh cubeMesh(vertices, indices, textures);

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        // Specify the color of the background
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        // Clean the back buffer and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Handles camera inputs
        camera.Inputs(window);
        // Updates and exports the camera matrix to the Vertex Shader
        camera.updateMatrix(45.0f, 0.1f, 1000.0f);

        // Desenha o cubo
        cubeMesh.Draw(shaderProgram, camera, glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::quat(), glm::vec3(1.0f, 1.0f, 1.0f));

        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        // Take care of all GLFW events
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
