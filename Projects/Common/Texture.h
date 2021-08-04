#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <GL/glew.h>
#include <stb_image.h>
#include <string>
#include <iostream>

class Texture
{
public:
	GLuint m_ID;
	std::string m_type;
	std::string m_FilePath;
private:
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_Components;

public:
	Texture();
	Texture(const std::string& path, const std::string& type);
	~Texture();

	void Load();
	void LoadModelTexture(const std::string& path, const std::string& type);

	void Bind(unsigned int slot = 0) const; // optionaler parameter wenn man nichts eingibt = 0 /man hat begrenzte texture slots
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeigth() const { return m_Height; }
};
#endif
