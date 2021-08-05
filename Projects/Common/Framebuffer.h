#ifndef FRAMEBUFFER_CLASS_H
#define FRAMEBUFFER_CLASS_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include "Renderbuffer.h"

class Framebuffer
{
private:
	GLuint m_ID;
	GLuint m_ColorTextureID;
	GLuint m_DepthTextureID;

	unsigned int m_Width;
	unsigned int m_Height;
public:
	Framebuffer(const int& width, const int& height);
	~Framebuffer();

	void Bind() const;
	void Unbind() const;
	void createColorTexture();
	void createDepthView();
	GLuint getColorTextureID();
	void attachRenderBuffer(GLuint rbo_ID);
};
#endif