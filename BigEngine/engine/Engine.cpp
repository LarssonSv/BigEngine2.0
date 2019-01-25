#include "Engine.h"
#include "Window.h"
#include "../files/LogHandler.h"
#include "ShaderProgram.h"
#include <assert.h>
#include "GL/glew.h"
#include <GLFW/glfw3.h>

Big::Engine::Engine()
{}

Big::Engine::~Engine()
{}

bool Big::Engine::Create()
{
	bool success = true;

	LogHandler* logHandler = LogHandler::CreateInstance(logPath);
	success &= logHandler->CreateLog(engineLog);
	if (!success)
	{ return false; }

	success &= Window::InitializeRenderSystem();
	if (!success)
	{
		LogHandler::DoLog("Failed to initialize render system.", LogFile::LogType::Error);
		return false;
	}

	Window::Settings windowSettings;
	windowSettings.width = 1024;
	windowSettings.height = 768;
	windowSettings.title = "Big Engine";
	windowSettings.backgroundColor = Color(1.0f, 0.0f, 1.0f);

	assert(window == nullptr);
	window = new Window();
	success &= window->Create(windowSettings);
	if (!success)
	{
		LogHandler::DoLog("Failed to create window.", LogFile::LogType::Error);
		return false;
	}

	shaderProgram = new ShaderProgram();
	success &= shaderProgram->Create();
	if (success)
	{
		success &= shaderProgram->LoadShader(deafultVertexShader,
			ShaderProgram::ShaderType::Vertex);
		success &= shaderProgram->LoadShader(deafultFragmentShader, 
			ShaderProgram::ShaderType::Fragment);
	}
	return success;
}

void Big::Engine::Destroy()
{

	if (shaderProgram)
	{
		shaderProgram->Destroy();
		delete shaderProgram;
		shaderProgram = nullptr;
	}


	if (window)
	{
		window->Destroy();
		delete window;
		window = nullptr;
	}

	Window::DeinitializeRenderSystem();
	LogHandler::DestroyInstance();
}

void Big::Engine::Run()
{
	GLfloat vertices[] = {
		// Position				Color
		0.0f,	0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	// Top, x, y, z
		0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	// Right
		-0.5f,	-0.5f,	0.0f,	0.0f, 0.0f, 1.0f	// Left
	};

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, nullptr);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (GLvoid*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(1);



	while (!window->Closing())
	{
		window->BeginRender();

		shaderProgram->Use();
		glBindVertexArray(vao);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);

		window->EndRender();

		// Todo: Create Input Handler.
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}
