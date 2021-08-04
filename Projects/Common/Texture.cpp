#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"


Texture::Texture(const std::string& path, const std::string& type)
	: m_FilePath(path), m_type(type)
{
	Load();
}

Texture::Texture()
{

}

void Texture::Load()
{
	stbi_set_flip_vertically_on_load(1); // flipt die Texture damit es von unten anfängt
	m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_Components, 0);

	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLenum format, internal_format;
	if (m_Components == 1)
	{
		format = GL_R;
		internal_format = GL_R8;
	}
	else if (m_Components == 3)
	{
		format = GL_RGB;
		internal_format = GL_RGB;
	}
	else if (m_Components == 4)
	{
		format = GL_RGBA;
		internal_format = GL_RGBA;
	}
	else
	{
		std::cout << "Texture loading not implemented for this number of compenents.\n";
		exit(1);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

void Texture::LoadModelTexture(const std::string& path, const std::string& type)
{
	m_FilePath = path;
	m_type = type;

	glGenTextures(1, &m_ID);

	m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_Components, 0);
	if (m_LocalBuffer)
	{
		GLenum format;
		if (m_Components == 1)
			format = GL_RED;
		else if (m_Components == 3)
			format = GL_RGB;
		else if (m_Components == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(m_LocalBuffer);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << m_FilePath << std::endl;
		stbi_image_free(m_LocalBuffer);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_ID);
}

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0 + slot); // der Texture Slot hier 0 = erster
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
