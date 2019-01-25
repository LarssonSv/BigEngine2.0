#pragma once

#include <string>

namespace Big
{
	class Window;
	class ShaderProgram;

	class Engine
	{
	public:
		Engine();
		~Engine();

		bool Create();
		void Destroy();
		void Run();

	private:
		Window* window = nullptr;
		ShaderProgram* shaderProgram = nullptr;

		const std::string logPath = "./logs/";
		const std::string engineLog = "engine.txt";
		const std::string& deafultVertexShader = "./data/shader/defaults.vert";
		const std::string& deafultFragmentShader = "./data/shader/defaults.frag";
	};
}
