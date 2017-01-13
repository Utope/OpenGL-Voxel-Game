#pragma once
#include "Shader.h"
#include <fstream>
#include <assert.h>
#include <iostream>
//GLShader::GLShader() {}

//GLShader::~GLShader() {}

Shader::Shader(std::initializer_list<std::string> filePaths) {
	m_shaderFilePaths = filePaths;
}

void Shader::load() {
	for (unsigned int i = 0; i < m_shaderFilePaths.size(); i++) {
		m_shaderObjects.push_back(Shader::static_loadShaderFile(m_shaderFilePaths[i]));
	}
	m_shaderProgram = Shader::static_loadShaderProgram(m_shaderObjects);
}

void Shader::reload() {
	Shader::static_unloadShaderProgram(m_shaderProgram, m_shaderObjects);
	this->load();
}

void Shader::unload() {
	Shader::static_unloadShaderProgram(m_shaderProgram, m_shaderObjects);
}

void Shader::link() {
	GLint status;
	glLinkProgram(m_shaderProgram);
	glValidateProgram(m_shaderProgram);
	glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &status);
	if (GL_FALSE == status) {
		assert(false && "Failure to initilize shader");
	}
	else {
		m_linked = true;
	}

}

bool Shader::isLinked() {
	return m_linked;
}

void Shader::bind() {
	glUseProgram(m_shaderProgram);
	m_bound = true;
}

bool Shader::isBound() {
	return m_bound;
}

void Shader::unBind() {
	glUseProgram(0);
	m_bound = false;
}

std::vector<GLuint>& Shader::getShaderObjects() {
	return m_shaderObjects;
}

GLuint& Shader::getShaderProgram() {
	return m_shaderProgram;
}

void Shader::loadBoolean(GLuint location, bool value) {
	if (m_bound) {
		if (value) {
			glUniform1f(location, 1.0f);
		}
		else {
			glUniform1f(location, 0.0f);
		}
	}
}

void Shader::loadFloat(GLuint Location, float x) {
	if (m_bound) {
		glUniform1f(Location, x);
	}
}

void Shader::loadVector2D(GLuint location, float x, float y) {
	if (m_bound) {
		glUniform2f(location, x, y);
	}
}

void Shader::loadVector3D(GLuint location, float x, float y, float z) {
	if (m_bound) {
		glUniform3f(location, x, y, z);
	}
}

void Shader::loadVector2D(GLuint location, const glm::vec2& vector) {
	if (m_bound) {
		glUniform2fv(location, 1, &vector[0]);
	}
}

void Shader::loadVector3D(GLuint location, const glm::vec3& vector) {
	if (m_bound) {
		glUniform3fv(location, 1, &vector[0]);
	}
}

void Shader::loadVector4D(GLuint location, const glm::vec4& vector) {
	if (m_bound) {
		glUniform4fv(location, 1, &vector[0]);
	}
}

void Shader::loadMat3X3(GLuint location, const bool transpose, const glm::mat3& mat3) {
	if (m_bound) {
		if (transpose) {
			glUniformMatrix3fv(location, 1, GL_TRUE, &mat3[0][0]);
		}
		else {
			glUniformMatrix3fv(location, 1, GL_FALSE, &mat3[0][0]);
		}
	}
}

void Shader::loadMat4x4(GLuint location, const bool transpose, const glm::mat4& mat4) {
	if (m_bound) {
		if (transpose) {
			glUniformMatrix4fv(location, 1, GL_TRUE, &mat4[0][0]);
		}
		else {
			glUniformMatrix4fv(location, 1, GL_FALSE, &mat4[0][0]);
		}
	}
}

// STATIC METHODS

//Loading functions

GLenum Shader::static_shaderFileObjType(std::string filePath) {
	std::string fileType = filePath.substr(filePath.size() - 2);
	if (fileType == "vs") {
		return GL_VERTEX_SHADER;
	}
	else if (fileType == "fs") {
		return GL_FRAGMENT_SHADER;
	}
	else {
		return 0;
	}
}

GLuint Shader::static_loadShaderFile(const std::string fileName) {
	//Load shader from a file
	std::fstream shaderFile;
	shaderFile.open(fileName);
	GLenum shaderType = Shader::static_shaderFileObjType(fileName);

	std::string shaderCode;
	std::string line;
	if (shaderFile.is_open()) {
		while (shaderFile.good()) {
			getline(shaderFile, line);
			shaderCode.append(line + "\n");
		}
	}
	else {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}
	/// end load shader from file

	//allocate and compile shader
	GLuint shaderID = glCreateShader(shaderType);
	if (shaderID == 0) {
		std::cerr << "Error: Shader creation failed" << std::endl;
	}


	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = shaderCode.c_str();
	shaderSourceStringLengths[0] = shaderCode.length();

	glShaderSource(shaderID, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shaderID);

	Shader::static_checkShaderError(shaderID, GL_COMPILE_STATUS, false, "Error: Shader comilation failed: ");

	return shaderID;

}

GLuint Shader::static_loadShaderString(const std::string shaderCode, GLuint shaderType) {

	//allocate and compile shader
	GLuint shaderID = glCreateShader(shaderType);
	if (shaderID == 0) {
		std::cerr << "Error: Shader creation failed" << std::endl;
	}


	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = shaderCode.c_str();
	shaderSourceStringLengths[0] = shaderCode.length();

	glShaderSource(shaderID, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shaderID);

	Shader::static_checkShaderError(shaderID, GL_COMPILE_STATUS, false, "Error: Shader comilation failed: ");

	return shaderID;

}

void Shader::static_checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram) {
		glGetProgramiv(shader, flag, &success);
	}
	else {
		glGetShaderiv(shader, flag, &success);
	}

	if (success != GL_TRUE) {
		if (isProgram) {
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else {
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}

		std::cerr << errorMessage << ": " << error << "'" << std::endl;
	}
}

GLuint Shader::static_loadShaderProgram(std::vector<GLuint>& shaderObjs) {
	GLuint shaderProgram = glCreateProgram();

	for (unsigned int i = 0; i < shaderObjs.size(); i++) {
		glAttachShader(shaderProgram, shaderObjs[i]);
	}

	return shaderProgram;
}

void Shader::static_unloadShaderObject(GLuint shaderObject) {
	glDeleteShader(shaderObject);
}

void Shader::static_unloadShaderProgram(GLuint shaderProgram, std::vector<GLuint>& shaderObjs) {
	for (unsigned int i = 0; i < shaderObjs.size(); i++) {
		glDetachShader(shaderProgram, shaderObjs[i]);
		glDeleteShader(shaderObjs[i]);
	}
	glDeleteProgram(shaderProgram);
}

// ~~~~~ MISC SHADER FUNCTIONS ~~~~~

std::string Shader::static_getActiveAttribs(GLuint shaderProgram) {
	GLint numAttribs;
	glGetProgramInterfaceiv(shaderProgram, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numAttribs);

	std::string activeAttributesString = "";
	GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };

	activeAttributesString.append("Active Attributes\n");
	for (int i = 0; i < numAttribs; i++) {
		GLint results[3];
		glGetProgramResourceiv(shaderProgram, GL_PROGRAM_INPUT, i, 3, properties, 3, nullptr, results);

		GLint nameBufSize = results[0] + 1;
		char* name = new char[nameBufSize];
		glGetProgramResourceName(shaderProgram, GL_PROGRAM_INPUT, i, nameBufSize, nullptr, name);
		activeAttributesString.append(name, results[0]);
		activeAttributesString.append("\n");
		delete[] name;
	}

	return activeAttributesString;
}

std::string Shader::static_getActiveUniforms(GLuint shaderProgram) {
	GLint numUniforms = 0;
	glGetProgramInterfaceiv(shaderProgram, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);

	GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX };

	std::string activeUniformsString = "";
	activeUniformsString.append("Active Uniforms\n");
	for (int i = 0; i < numUniforms; i++) {
		GLint results[4];
		glGetProgramResourceiv(shaderProgram, GL_UNIFORM, i, 4, properties, 4, nullptr, results);

		if (results[3] != -1) {
			continue;
		}

		GLint nameBufSize = results[0] + 1;
		char* name = new char[nameBufSize];
		glGetProgramResourceName(shaderProgram, GL_UNIFORM, i, nameBufSize, nullptr, name);
		activeUniformsString.append(name, results[0]);
		activeUniformsString.append("\n");
		delete[] name;
	}

	return activeUniformsString;

}


// ~~~~~ SHADER UNIFORM LOADING ~~~~~
void Shader::static_bindShader(GLuint shaderProgram) {
	glUseProgram(shaderProgram);
}

void Shader::static_unBindShader() {
	glUseProgram(0);
}

void Shader::static_linkShaderProgram(GLuint shaderProgram) {
	GLint status;
	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (GL_FALSE == status) {
		assert(false && "Failure to initilize shader");
	}
}

void Shader::static_loadBoolean(GLuint location, bool value) {
	if (value) {
		glUniform1f(location, 1.0f);
	}
	else {
		glUniform1f(location, 0.0f);
	}
}

void Shader::static_loadFloat(GLuint Location, float x) {
	glUniform1f(Location, x);
}

void Shader::static_loadVector2D(GLuint location, float x, float y) {
	glUniform2f(location, x, y);
}

void Shader::static_loadVector3D(GLuint location, float x, float y, float z) {
	glUniform3f(location, x, y, z);
}

void Shader::static_loadVector2D(GLuint location, const glm::vec2& vector) {
	glUniform2fv(location, 1, &vector[0]);
}

void Shader::static_loadVector3D(GLuint location, const glm::vec3& vector) {
	glUniform3fv(location, 1, &vector[0]);
}

void Shader::static_loadVector4D(GLuint location, const glm::vec4& vector) {
	glUniform4fv(location, 1, &vector[0]);
}

void Shader::static_loadMat3X3(GLuint location, const bool transpose, const glm::mat3& mat3) {
	if (transpose) {
		glUniformMatrix3fv(location, 1, GL_TRUE, &mat3[0][0]);
	}
	else {
		glUniformMatrix3fv(location, 1, GL_FALSE, &mat3[0][0]);
	}
}

void Shader::static_loadMat4x4(GLuint location, const bool transpose, const glm::mat4& mat4) {
	if (transpose) {
		glUniformMatrix4fv(location, 1, GL_TRUE, &mat4[0][0]);
	}
	else {
		glUniformMatrix4fv(location, 1, GL_FALSE, &mat4[0][0]);
	}
}
