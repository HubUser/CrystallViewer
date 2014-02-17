#include <mshader.h>
#include <iostream>

GLuint MShader::getHandle() {
	return shaderHandle;
}

bool MShader::isCreated() {
	return shaderCreated;
}

MShader::~MShader() {
	if (shaderCreated)
		glDeleteShader(shaderHandle);
}