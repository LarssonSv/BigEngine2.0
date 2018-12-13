#pragma once

#include <string>
#include <map>

namespace Big
{
	class ConfigFile;

	class ConfigHandler
	{
	public:
		static ConfigHandler* InstancePointer();
		static ConfigHandler& Instance();

		static ConfigHandler* CreateInstance(const std::string& folderPath);
		static void DestroyInstance();

		bool LoadConfigFile(const std::string& name, bool parseNow, ConfigFile** outConfigFile = nullptr);
		bool SaveConfigFile(const std::string& name);

		ConfigFile* GetConfigFile(const std::string& name);

	private:
		ConfigHandler();
		ConfigHandler(const std::string& pathToFiles);
		ConfigHandler(const ConfigHandler&);
		~ConfigHandler();

		ConfigHandler& operator=(const ConfigHandler&) {}

		std::string basePath;
		std::map<std::string, ConfigFile*> configs;

		static ConfigHandler* instance;
	};
}
