#ifndef __MPROGRAM_H__
#    define __MPROGRAM_H__

#include <mvertexshader.h>
#include <mfragmentshader.h>

class MProgram {
public:
	MProgram(MVertexShader aVertexShader, MFragmentShader aFragmentShader);
    GLint attributeLocation(const std::string aAttribName);
    void enableAttributeArray(const GLint aAttribHandle);
    ~MProgram();
private:
	GLuint programHandle;
	bool programCreated;
};

#endif //__MPROGRAM_H__
