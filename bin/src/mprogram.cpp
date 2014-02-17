#include <iostream>
#include <mprogram.h>

MProgram::MProgram(MVertexShader aVertexShader, MFragmentShader aFragmentShader) : programHandle(0), programCreated(false) {
    if (!aVertexShader.isCreated() || !aFragmentShader.isCreated())
    	return;

    programHandle = glCreateProgram();

    programCreated = true;

    glAttachShader(programHandle, aVertexShader.getHandle());
    glAttachShader(programHandle, aFragmentShader.getHandle());
    glLinkProgram(programHandle);

    GLint testVal;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &testVal);

    if (testVal == GL_FALSE) {
    	char infoLog[1024];
    	glGetProgramInfoLog(programHandle, 1024, NULL, infoLog);
    	std::cerr << "The program:\n" << programHandle << "\n failed to link with the following error:\n"
    	          << infoLog << '\n';
    	glDeleteShader(programHandle);
    	programCreated = false;
    }
}

MProgram::~MProgram() {
	if (programCreated)
		glDeleteProgram(programHandle);
}

GLint MProgram::attributeLocation(const std::string aAttribName) {
	return 0;
}

void MProgram::enableAttributeArray(const GLint aAttribHandle) {}