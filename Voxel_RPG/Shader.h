#pragma once
#include <vector>
#include <initializer_list>
#include <string>
#include "GL\glew.h"
#include "glm\glm.hpp"

class Shader {
public:

	Shader(std::initializer_list<std::string> filePaths);

	std::vector<GLuint>& getShaderObjects();
	GLuint& getShaderProgram();

	void bind();
	void unBind();
	bool isBound();
	void link();
	bool isLinked();

	void load();
	void unload();
	void reload();

	void loadBoolean(GLuint location, bool value);
	void loadFloat(GLuint Location, float x);
	void loadVector2D(GLuint location, float x, float y);
	void loadVector3D(GLuint location, float x, float y, float z);
	void loadVector2D(GLuint location, const glm::vec2& vector);
	void loadVector3D(GLuint location, const glm::vec3& vector);
	void loadVector4D(GLuint location, const glm::vec4& vector);
	void loadMat3X3(GLuint location, const bool transpose, const glm::mat3& mat3);
	void loadMat4x4(GLuint location, const bool transpose, const glm::mat4& mat4);

	//Static Methods
	static void static_bindShader(GLuint shaderProgram);
	static void static_unBindShader();
	static void static_linkShaderProgram(GLuint shaderProgram);

	static GLenum static_shaderFileObjType(std::string shaderFilePath);

	static GLuint static_loadShaderFile(const std::string fileName);
	static GLuint static_loadShaderString(const std::string shaderCode, GLuint shaderType);
	static GLuint static_loadShaderProgram(std::vector<GLuint>& shaderObjs);
	static void static_unloadShaderObject(GLuint shader);
	static void static_unloadShaderProgram(GLuint program, std::vector<GLuint>& shaderObjs);

	static void static_loadBoolean(GLuint location, bool value);
	static void static_loadFloat(GLuint Location, float x);
	static void static_loadVector2D(GLuint location, float x, float y);
	static void static_loadVector3D(GLuint location, float x, float y, float z);
	static void static_loadVector2D(GLuint location, const glm::vec2& vector);
	static void static_loadVector3D(GLuint location, const glm::vec3& vector);
	static void static_loadVector4D(GLuint location, const glm::vec4& vector);
	static void static_loadMat3X3(GLuint location, const bool transpose, const glm::mat3& mat3);
	static void static_loadMat4x4(GLuint location, const bool transpose, const glm::mat4& mat4);

	static std::string static_getActiveAttribs(GLuint shaderProgram);
	static std::string static_getActiveUniforms(GLuint shaderProgram);

	static void static_checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage);

private:
	std::vector<GLuint> m_shaderObjects;
	std::vector<std::string> m_shaderFilePaths;
	bool m_linked;
	bool m_bound;
	bool m_loaded;
	GLuint m_shaderProgram;
};