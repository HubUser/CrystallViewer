#ifndef __MSHADER_H__
#    define __MSHADER_H__

#include <string>
#include <glut/glut.h>

class MShader {
public:
    MShader() : shaderHandle(0), shaderCreated(false) {}
	GLuint getHandle();
    bool isCreated();
	virtual ~MShader();

protected:
	GLuint shaderHandle;
	bool shaderCreated;
};

#endif //__MSHADER_H__
