#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 Normal;
out vec2 TexCoord;

float angle = radians(45.0);

mat4 rotationZ = mat4(
    cos(angle), -sin(angle), 0.0, 0.0,
    sin(angle),  cos(angle), 0.0, 0.0,
    0.0,         0.0,        1.0, 0.0,
    0.0,         0.0,        0.0, 1.0
);

mat4 rotationX = mat4(
    1.0, 0.0,        0.0,       0.0,
    0.0, cos(angle), -sin(angle), 0.0,
    0.0, sin(angle),  cos(angle), 0.0,
    0.0, 0.0,        0.0,       1.0
);

mat4 perspective(float fov, float aspect, float near, float far) {
    float tanHalfFOV = tan(fov / 2.0);
    return mat4(
        1.0 / (aspect * tanHalfFOV), 0.0, 0.0, 0.0,
        0.0, 1.0 / tanHalfFOV, 0.0, 0.0,
        0.0, 0.0, -(far + near) / (far - near), -1.0,
        0.0, 0.0, -(2.0 * far * near) / (far - near), 0.0
    );
}

void main()
{
    mat4 model = rotationX * rotationZ;
    mat4 proj = perspective(radians(45.0), 1.0, 0.1, 10.0);

    vec4 worldPos = model * vec4(aPos, 1.0);
    worldPos.z -= 3.0; // push cube into view

    gl_Position = proj * worldPos;

    Normal = mat3(model) * aNormal; // rotate normals too
    TexCoord = aTexCoord;
}
