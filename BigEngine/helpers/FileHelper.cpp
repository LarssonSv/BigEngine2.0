#include "FileHelper.h"
#include "fstream"
#include "sstream"
#include "../files/LogHandler.h"

#ifdef _WINDOWS
#include "windows.h"

bool Big::FileHelper::DoesFolderExist(const std::string& path)
{
	DWORD fileAttributes = GetFileAttributesA(path.c_str());
	if (fileAttributes != INVALID_FILE_ATTRIBUTES)
	{
		return false;
	}

	if (fileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		return true;
	}

	return false;
}

bool Big::FileHelper::CreateFolder(const std::string& path)
{
	return CreateDirectoryA(path.c_str(), nullptr);
}

#endif

bool Big::FileHelper::GetFileContent(const std::string& uri, std::string& outContent)
{
	std::ifstream inStream;
	std::stringstream stringStream;

	inStream.open(uri.c_str());
	if (inStream.is_open())
	{
		stringStream << inStream.rdbuf();
		outContent = stringStream.str();
		return true;
	}

	else
	{
		LogHandler::DoLog("Failed to load " + uri, LogFile::LogType::Error);
		return false;
	}
}

	Big::FileHelper::FileHelper()
	{

	}

	Big::FileHelper::FileHelper(const FileHelper& fileHelper)
	{

	}

	Big::FileHelper::~FileHelper()
	{

	}
