#ifndef IBO_CLASS_H
#define IBO_CLASS_H

#include <GL/glew.h>
#include <vector>

class IndexBuffer
{
private:
	GLuint m_ID;
public:
	IndexBuffer();
	IndexBuffer(std::vector<GLuint>& indices);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	void Delete() const;
};
#endif