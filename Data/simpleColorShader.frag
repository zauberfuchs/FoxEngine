// Angabe der Version von OpenGL und dem Profil
// Hier 3.3 mit Core-Profile
#version 330 core

// Ausgangswert ist wieder eine Farbe, diesmal der Pixelwert
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 0.6, 0.0, 1.0);
}