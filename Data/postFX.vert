#version 330 core
// Positions/Coordinates
layout (location = 0) in vec3 vPos;
// Normals
layout (location = 1) in vec3 vNormal;
// Texture Coordinates
layout (location = 2) in vec2 vTex;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(vPos.x, vPos.y, 0.0, 1.0); 
    TexCoords = vTex;
} 