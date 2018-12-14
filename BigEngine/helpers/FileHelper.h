#pragma once

#include "string"

namespace Big {

	class FileHelper
	{

	public:

		static bool DoesFolderExist(const std::string& path);
		static bool CreateFolder(const std::string& path);
		static bool GetFileContent(const std::string& uri, std::string& outContent);

	private:

		FileHelper();
		FileHelper(const FileHelper& fileHelper);
		~FileHelper();

	};

}