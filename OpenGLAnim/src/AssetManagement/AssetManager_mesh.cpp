#include "AssetManager.h"

namespace AssetManager {

    int g_nextVertexInsert = 0;
    int g_nextIndexInsert = 0;

	int CreateMesh(const std::string& name, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, glm::vec3 aabbMin, glm::vec3 aabbMax, int parentIndex, glm::mat4 localTransform, glm::mat4 inverseBindTransform)
	{
        std::vector<Mesh>& meshes = GetMeshes();
        std::vector<Vertex>& allVertices = GetVertices();
        std::vector<uint32_t>& allIndices = GetIndices();

        Mesh& mesh = meshes.emplace_back();
        mesh.baseVertex = g_nextVertexInsert;
        mesh.baseIndex = g_nextIndexInsert;
        mesh.vertexCount = (uint32_t)vertices.size();
        mesh.indexCount = (uint32_t)indices.size();
        mesh.SetName(name);
        mesh.aabbMin = aabbMin;
        mesh.aabbMax = aabbMax;
        mesh.extents = aabbMax - aabbMin;
        mesh.boundingSphereRadius = std::max(mesh.extents.x, std::max(mesh.extents.y, mesh.extents.z)) * 0.5f;
        mesh.parentIndex = parentIndex;
        mesh.localTransform = localTransform;
        mesh.inverseBindTransform = inverseBindTransform;

        allVertices.reserve(allVertices.size() + vertices.size());
        allVertices.insert(std::end(allVertices), std::begin(vertices), std::end(vertices));
        allIndices.reserve(allIndices.size() + indices.size());
        allIndices.insert(std::end(allIndices), std::begin(indices), std::end(indices));
        g_nextVertexInsert += mesh.vertexCount;
        g_nextIndexInsert += mesh.indexCount;

        return meshes.size() - 1;
	}

    int CreateMesh(const std::string& name, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
        // Initialize AABB min and max with first vertex
        glm::vec3 aabbMin = vertices[0].position;
        glm::vec3 aabbMax = vertices[0].position;

        // Calculate AABB by iterating over all vertices
        for (const Vertex& v : vertices) {
            aabbMin = glm::min(aabbMin, v.position);
            aabbMax = glm::max(aabbMax, v.position);
        }

        return CreateMesh(name, vertices, indices, aabbMin, aabbMax, -1, glm::mat4(1.0f), glm::mat4(1.0f));
    }
}