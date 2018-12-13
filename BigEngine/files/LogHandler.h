#pragma once

#include "LogFile.h"

#include <string>
#include <map>

namespace Big
{
	class LogHandler
	{
	public:
		static LogHandler* InstancePointer();
		static LogHandler& Instance();

		static LogHandler* CreateInstance(const std::string& folderPath);
		static void DestroyInstance();

		bool CreateLog(const std::string name, bool doSupressFileOutput = false, bool doLogTimestamps = true);
		void DoLog(const std::string& name, const std::string& message, LogFile::LogType logType = LogFile::LogType::Info);
		static void DoLog(const std::string& message, LogFile::LogType logType = LogFile::LogType::Info);
	private:
		LogHandler();
		LogHandler(const std::string& pathToFiles);
		LogHandler(const LogHandler&);
		~LogHandler();

		LogHandler& operator=(const LogHandler&) {}

		static void glfwErrorCallBack(int error, const char* description);

		std::string basePath;
		std::map<std::string, LogFile*> logs;

		static LogHandler* instance;
		static LogFile* defaultLog;
	};
}
