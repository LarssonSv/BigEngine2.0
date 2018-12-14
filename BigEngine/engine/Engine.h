#pragma once

#include <string>

namespace Big
{
	class Window;

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

		const std::string logPath = "./logs/";
		const std::string engineLog = "engine.txt";
	};
}
