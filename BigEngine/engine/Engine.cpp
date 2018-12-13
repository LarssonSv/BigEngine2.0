#include "Engine.h"
#include "Window.h"
#include "../files/LogHandler.h"
#include <assert.h>
#include "GL/glew.h"
#include <GLFW/glfw3.h>


Big::Engine::Engine()
{

}

Big::Engine::~Engine()
{

}

bool Big::Engine::Create()
{
	bool success = true;

	LogHandler* logHandler = LogHandler::CreateInstance(logPath);
	success &= logHandler->CreateLog(engineLog);

	if (!success)
	{

		return false;
	}

	success &= Window::InitializeRenderSystem();
	if (!success)
	{
		LogHandler::DoLog("Failed to initialize render system.", LogFile::LogType::Error);
		return false;
	}

	Window::Settings windowSettings;
	windowSettings.width = 1280;
	windowSettings.height = 720;
	windowSettings.title = "Big Engine";
	windowSettings.backgroundColor = Color::Green;

	assert(window == nullptr);
	window = new Window();
	return window->Create(windowSettings);
}

void Big::Engine::Destroy()
{
	if (window)
	{
		delete window;
		window = nullptr;
	}
	Window::DeinitalizeRenderSystem();
	LogHandler::DestroyInstance();
}

void Big::Engine::Run()
{
	GLfloat vertices[] = {
		//Position				//Color
		0.0f, 0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	//top x,y, z
		0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	//right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, 1.0f	//left
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, nullptr);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (GLvoid*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);
	
	const GLchar* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec3 pos;"
		"layout (location = 1) in vec3 color;"
		"out vec3 vert_color;"
		"void main()"
		"{"
		"vert__color = color;"
		"gl_Position = vec4(pos.x, pos.y, pos.z);"
		"}";

	const GLchar* fragmentShaderSource =
		"#version 330 core\n"
		"in vec3 vert_color;"
		"out vec4 frag_color;"
		"void main()"
		"{"
		"frag_color = vec4(vert_color, 1.0f);"
		"}";


	//Vertex Shader
	GLuint  vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	GLint result;
	GLchar info[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(vertexShader, sizeof(info), nullptr, info);
		LogHandler::DoLog(info, LogFile::LogType::Error);
	}

	//FragmentShader
	GLuint  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(info), nullptr, info);
		LogHandler::DoLog(info, LogFile::LogType::Error);
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(info), nullptr, info);
		LogHandler::DoLog(info, LogFile::LogType::Error);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	while (!window->Closing())
	{
		// Todo: Create Input Handler.

		window->BeginRender();

		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		window->EndRender();

		glfwPollEvents();
	}

	glDeleteProgram(shaderProgram);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

}
