#pragma once
#include "Glm.h"

struct Resolutions {
    glm::ivec2 gBuffer;
    glm::ivec2 finalImage;
    glm::ivec2 ui;
    glm::ivec2 hair;
};

struct Vertex {
    Vertex() = default;
    Vertex(glm::vec3 pos) {
        position = pos;
    }
    Vertex(glm::vec3 pos, glm::vec3 norm) {
        position = pos;
        normal = norm;
    }
    Vertex(glm::vec3 pos, glm::vec3 norm, glm::vec2 texCoord) {
        position = pos;
        normal = norm;
        uv = texCoord;
    }
    glm::vec3 position = glm::vec3(0);
    glm::vec3 normal = glm::vec3(0);
    glm::vec2 uv = glm::vec2(0);
};

struct RenderItem {
    glm::mat4 modelMatrix = glm::mat4(1);
};

struct FileInfo {
    std::string path;
    std::string name;
    std::string ext;
    std::string dir;
};