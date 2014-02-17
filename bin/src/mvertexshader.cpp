#include <mvertexshader.h>
#include <iostream>

MVertexShader::MVertexShader(std::string aShaderCode) {
    shaderHandle = glCreateShader(GL_VERTEX_SHADER);
    shaderCreated = true;

    const GLchar *shaderCString = aShaderCode.c_str();
    glShaderSource(shaderHandle, 1, const_cast<GLchar **> (&shaderCString), NULL);
    glCompileShader(shaderHandle);

    GLint testVal;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &testVal);

    if (testVal == GL_FALSE) {
    	char infoLog[1024];
    	glGetShaderInfoLog(shaderHandle, 1024, NULL, infoLog);
    	std::cerr << "The vertex shader:\n" << aShaderCode << "\n failed to compile with the following error:\n"
    	          << infoLog << '\n';
    	glDeleteShader(shaderHandle);
    	shaderCreated = false;
    }
}