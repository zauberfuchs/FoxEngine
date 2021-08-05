
#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{ 
    FragColor = vec4(vec3(texture(screenTexture, TexCoords))*clamp(sinh(0.5f),0.0f,0.2f), 1.0);
    //FragColor = vec4(vec3(1.0 - texture(screenTexture, TexCoords))*sinh(0.9f), 1.0);
}