cmake_minimum_required(VERSION 3.10)
project(Tutorial)

# Define a política CMP0072 para preferir GLVND
if (POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

# Define o padrão de compilação para C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adiciona os diretórios de cabeçalhos
include_directories(headers)
include_directories(libraries/include/glad/include)

# Adiciona os arquivos fonte
file(GLOB SOURCES "src/*.cpp" "libraries/include/glad/src/glad.c")

# Cria o executável
add_executable(Tutorial ${SOURCES})

# Adiciona o diretório da biblioteca estática GLFW
add_library(GLFW STATIC IMPORTED)
set_target_properties(GLFW PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libraries/lib/libglfw3.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/libraries/include"
)

# Encontra as bibliotecas OpenGL e SDL2
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

# Encontre a biblioteca SDL2_mixer
find_library(SDL2_MIXER_LIBRARY SDL2_mixer)

# Defina manualmente as variáveis para SDL2_mixer
set(SDL2_MIXER_INCLUDE_DIRS "/usr/include/SDL2")
set(SDL2_MIXER_LIBRARIES "/usr/lib/x86_64-linux-gnu/libSDL2_mixer.so")

# Inclui os diretórios para SDL2 e SDL2_mixer
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

# Linka as bibliotecas necessárias
target_link_libraries(Tutorial OpenGL::GL GLFW ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES} stdc++fs)

# Encontra e linka o OpenAL
find_package(OpenAL REQUIRED)
include_directories(${OPENAL_INCLUDE_DIR})
target_link_libraries(Tutorial ${OPENAL_LIBRARY})
