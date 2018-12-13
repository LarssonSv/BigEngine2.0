#pragma once

#include <string>

namespace tinyxml2
{
	class XMLDocument;
}

namespace Big
{
	class ConfigFile
	{
	public:
		ConfigFile();
		~ConfigFile();

		bool Create(const std::string& fileWithPath, bool parseNow = true);
		void Destroy();

		// If document is loaded it will be reloaded.
		bool Parse();
		bool Save();

		bool GetString(const std::string& uri, std::string& outValue, const std::string& defaultValue = "");

	private:
		std::string uri;
		tinyxml2::XMLDocument* document;
	};
}
