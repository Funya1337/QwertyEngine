#version 460 core
out vec4 FragColor;

in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    vec3 color = normalize(Normal) * 0.5 + 0.5;
    FragColor = vec4(color, 1.0);
    //FragColor = vec4(color, 1.0) * texture(ourTexture, TexCoord);
    //FragColor = texture(ourTexture, TexCoord);
}
