#include "AssetManager.h"

namespace AssetManager {


    Model* CreateModel(const std::string& name) {
        std::vector<Model>& models = GetModels();
        models.emplace_back();
        Model* model = &models[models.size() - 1];
        model->SetName(name);
        return model;
    }

    void BuildPrimitives() {
        Model* model = CreateModel("Primitives");

        ///* Quad */ {
        //    std::vector<Vertex> vertices = {
        //        // Position               Normal               UV
        //        {{-0.5f, -0.5f, 0.0f},    {0.0f, 0.0f, 1.0f},  {0.0f, 0.0f}}, // Bottom-left
        //        {{ 0.5f, -0.5f, 0.0f},    {0.0f, 0.0f, 1.0f},  {1.0f, 0.0f}}, // Bottom-right
        //        {{ 0.5f,  0.5f, 0.0f},    {0.0f, 0.0f, 1.0f},  {1.0f, 1.0f}}, // Top-right
        //        {{-0.5f,  0.5f, 0.0f},    {0.0f, 0.0f, 1.0f},  {0.0f, 1.0f}}  // Top-left
        //    };

        //    std::vector<uint32_t> indices = { 0, 1, 2, 2, 3, 0 };

        //    int meshIndex = CreateMesh("Quad", vertices, indices);
        //    model->AddMeshIndex(meshIndex);
        //}

        /* Cube */ {
            std::vector<Vertex> cubeVertices = {
                // FRONT FACE
                {{-0.5f, -0.5f,  0.5f}, { 0, 0, 1}, {0, 0}},
                {{ 0.5f, -0.5f,  0.5f}, { 0, 0, 1}, {1, 0}},
                {{ 0.5f,  0.5f,  0.5f}, { 0, 0, 1}, {1, 1}},
                {{-0.5f,  0.5f,  0.5f}, { 0, 0, 1}, {0, 1}},

                // BACK FACE
                {{ 0.5f, -0.5f, -0.5f}, { 0, 0, -1}, {0, 0}},
                {{-0.5f, -0.5f, -0.5f}, { 0, 0, -1}, {1, 0}},
                {{-0.5f,  0.5f, -0.5f}, { 0, 0, -1}, {1, 1}},
                {{ 0.5f,  0.5f, -0.5f}, { 0, 0, -1}, {0, 1}},

                // LEFT FACE
                {{-0.5f, -0.5f, -0.5f}, {-1, 0, 0}, {0, 0}},
                {{-0.5f, -0.5f,  0.5f}, {-1, 0, 0}, {1, 0}},
                {{-0.5f,  0.5f,  0.5f}, {-1, 0, 0}, {1, 1}},
                {{-0.5f,  0.5f, -0.5f}, {-1, 0, 0}, {0, 1}},

                // RIGHT FACE
                {{ 0.5f, -0.5f,  0.5f}, { 1, 0, 0}, {0, 0}},
                {{ 0.5f, -0.5f, -0.5f}, { 1, 0, 0}, {1, 0}},
                {{ 0.5f,  0.5f, -0.5f}, { 1, 0, 0}, {1, 1}},
                {{ 0.5f,  0.5f,  0.5f}, { 1, 0, 0}, {0, 1}},

                // TOP FACE
                {{-0.5f,  0.5f,  0.5f}, { 0, 1, 0}, {0, 0}},
                {{ 0.5f,  0.5f,  0.5f}, { 0, 1, 0}, {1, 0}},
                {{ 0.5f,  0.5f, -0.5f}, { 0, 1, 0}, {1, 1}},
                {{-0.5f,  0.5f, -0.5f}, { 0, 1, 0}, {0, 1}},

                // BOTTOM FACE
                {{-0.5f, -0.5f, -0.5f}, { 0,-1, 0}, {0, 0}},
                {{ 0.5f, -0.5f, -0.5f}, { 0,-1, 0}, {1, 0}},
                {{ 0.5f, -0.5f,  0.5f}, { 0,-1, 0}, {1, 1}},
                {{-0.5f, -0.5f,  0.5f}, { 0,-1, 0}, {0, 1}}
            };

            std::vector<uint32_t> cubeIndices = {
                0, 1, 2,  2, 3, 0,      // Front face
                4, 5, 6,  6, 7, 4,      // Back face
                8, 9, 10, 10, 11, 8,    // Left face
                12, 13, 14, 14, 15, 12, // Right face
                16, 17, 18, 18, 19, 16, // Top face
                20, 21, 22, 22, 23, 20  // Bottom face
            };

            int meshIndexCube = CreateMesh("Cube", cubeVertices, cubeIndices);
            model->AddMeshIndex(meshIndexCube);
        }
        model->SetLoadingState(LoadingState::LOADING_COMPLETE);
    }
}