#pragma once

#include "../math/Color.h"

#include <string>

struct GLFWwindow;

namespace Big
{
	class Window
	{
	public:
		Window();
		~Window();

		struct Settings
		{
			Settings();
			Settings(const Settings& copySettings);
			int width;
			int height;
			std::string title;
			Color backgroundColor;
		};

		static bool InitializeRenderSystem();
		static void DeinitializeRenderSystem();

		bool Create(Settings windowSettings);
		void Destroy();
		bool Closing();

		void BeginRender();
		void EndRender();

	private:
		GLFWwindow* glWindow;

		Settings settings;
	};
}
