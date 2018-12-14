#include "ShaderProgram.h"
#include "../helpers/FileHelper.h"
#include "../files/LogHandler.h"
#include "assert.h"
#include "gl/glew.h"


Big::ShaderProgram::ShaderProgram()
{
}

Big::ShaderProgram::~ShaderProgram()
{
}

void Big::ShaderProgram::Destroy()
{
	glDeleteProgram(handle);
	handle = 0;
}

void Big::ShaderProgram::Use()
{
	assert(handle > 0);
	glUseProgram(handle);
}

bool Big::ShaderProgram::LoadShader(const std::string& uri, ShaderType shaderType)
{	
	std::string source;
	GLuint shaderHandle = 0;

	if (FileHelper::GetFileContent(uri, source))
	{
		switch (shaderType)
		{
		case ShaderType::Vertex:
			shaderHandle = glCreateShader(GL_VERTEX_SHADER);
			break;

		case ShaderType::Fragment:
			shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		default:
			return false;
		}

		const GLchar* glSource = source.c_str();
		glShaderSource(shaderHandle, 1, &glSource, nullptr);
		glCompileShader(shaderHandle);

		if (!CheckShaderError(handle))
		{
			glAttachShader(handle, shaderHandle);
			glLinkProgram(handle);
			return !CheckProgramError();
		}
	}
	
	return false;
}

bool Big::ShaderProgram::Create()
{
	handle = glCreateProgram();
	return true;
}

bool Big::ShaderProgram::CheckShaderError(unsigned int shader)
{

	GLint status;
	glGetShaderiv(handle, GL_COMPILE_STATUS, &status);

	if (!status)
	{
		GLint messageLength = 0;
		glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &messageLength);
		std::string errorMessage(messageLength, ' ');
		glGetShaderInfoLog(handle, messageLength, &messageLength, &errorMessage[0]);
		LogHandler::DoLog("Shader failed to compile shader: " + errorMessage, LogFile::LogType::Error);
		return false;
	}

	return true;
}

bool Big::ShaderProgram::CheckProgramError()
{
	GLint status;
	glGetProgramiv(handle, GL_LINK_STATUS, &status);

	if (!status)
	{
		GLint messageLength = 0;
		glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &messageLength);
		std::string errorMessage(messageLength, ' ');
		glGetProgramInfoLog(handle, messageLength, &messageLength, &errorMessage[0]);
		LogHandler::DoLog("Shader Program failed to link shader: " + errorMessage, LogFile::LogType::Error);
		return false;
	}

	return true;
}
