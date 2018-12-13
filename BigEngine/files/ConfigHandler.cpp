#include "ConfigHandler.h"
#include "ConfigFile.h"

#include <assert.h>

// If this is set in the header we get already defined error.
Big::ConfigHandler* Big::ConfigHandler::instance = nullptr;	// Prevents C2864 https://docs.microsoft.com/en-us/cpp/error-messages/compiler-errors-2/compiler-error-c2864?view=vs-2017

Big::ConfigHandler::ConfigHandler()
{}

Big::ConfigHandler::ConfigHandler(const std::string& pathToFiles) : basePath(pathToFiles)
{}

Big::ConfigHandler::~ConfigHandler()
{}

Big::ConfigHandler* Big::ConfigHandler::InstancePointer()
{
	assert(instance != nullptr);
	return instance;
}

Big::ConfigHandler& Big::ConfigHandler::Instance()
{
	assert(instance != nullptr);
	return *instance;
}

Big::ConfigHandler* Big::ConfigHandler::CreateInstance(const std::string& folderPath)
{
	if (!instance)
	{
		instance = new ConfigHandler(folderPath);
	}
	return instance;
}

void Big::ConfigHandler::DestroyInstance()
{
	if (instance)
	{
		for (std::map<std::string, ConfigFile*>::iterator it = instance->configs.begin(); it != instance->configs.end(); ++it)
		{
			it->second->Destroy();
			delete it->second;
		}
		delete instance;
		instance = nullptr;
	}
}

bool Big::ConfigHandler::LoadConfigFile(const std::string& name, bool parseNow, ConfigFile** outConfigFile /*= nullptr*/)
{
	if (configs.find(name) == configs.end())
	{
		ConfigFile* config = new ConfigFile();
		if (config->Create(basePath + name, parseNow))
		{
			configs.insert(std::make_pair(name, config));
			*outConfigFile = config;
			return true;
		}
		return false;
	}
	return false;
}

bool Big::ConfigHandler::SaveConfigFile(const std::string& name)
{
	std::map<std::string, ConfigFile*>::iterator it = configs.find(name);
	if (it != configs.end())
	{
		return it->second->Save();
	}
	return false;
}

Big::ConfigFile* Big::ConfigHandler::GetConfigFile(const std::string& name)
{
	std::map<std::string, ConfigFile*>::iterator it = configs.find(name);
	if (it != configs.end())
	{
		return it->second;
	}
	return nullptr;
}
