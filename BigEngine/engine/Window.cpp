#include "Window.h"
#include "../files/LogHandler.h"
#include "../files/LogFile.h"
#include <GL/glew.h>	// Must include before glfw3.h
#include <GLFW/glfw3.h>

Big::Window::Window()
{}


Big::Window::~Window()
{}

bool Big::Window::InitializeRenderSystem()
{
	if (glfwInit())
	{
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		return true;
	}
	LogHandler::DoLog("Failed To initialize RenderSystem", LogFile::LogType::Error);
	return false;
}

void Big::Window::DeinitalizeRenderSystem()
{
	glfwTerminate();
}

bool Big::Window::Create(Settings setting)
{


	glWindow = glfwCreateWindow(setting.width, setting.height, setting.title.c_str(), nullptr, nullptr);
	if (!glWindow)
	{
		LogHandler::DoLog("Failed to create window", LogFile::LogType::Error);
		return false;
	}

	glfwMakeContextCurrent(glWindow);

	glewExperimental = GLEW_OK;
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		LogHandler::DoLog((const char*)glewGetErrorString(error), LogFile::LogType::Error);
		return false;
	}

	glClearColor(setting.backgroundColor[0], setting.backgroundColor[1], setting.backgroundColor[2],
		setting.backgroundColor[3]);

	return true;
}

void Big::Window::Destroy()
{
	if (glWindow)
	{
		glfwDestroyWindow(glWindow);
		glWindow = nullptr;
	}
}

bool Big::Window::Closing()
{
	return glfwWindowShouldClose(glWindow);
}

void Big::Window::BeginRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Big::Window::EndRender()
{
	glfwSwapBuffers(glWindow);
}

Big::Window::Settings::Settings(const Settings& copySettings)
{
	width = copySettings.width;
	height = copySettings.height;
	title = copySettings.title;
	backgroundColor = copySettings.backgroundColor;
}

Big::Window::Settings::Settings()
{

}
