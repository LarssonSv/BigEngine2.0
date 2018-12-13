#include "ConfigFile.h"
#include "../third/tixml2ex.h"
#include "../helpers/StringHelper.h"

#include <assert.h>

Big::ConfigFile::ConfigFile()
{}

Big::ConfigFile::~ConfigFile()
{}

bool Big::ConfigFile::Create(const std::string& fileWithPath, bool parseNow /*= true*/)
{
	uri = fileWithPath;
	if (parseNow)
	{
		return Parse();
	}
	return true;
}

void Big::ConfigFile::Destroy()
{
	if (document)
	{
		delete document;
		document = nullptr;
	}
}

bool Big::ConfigFile::Parse()
{
	if (document)
	{
		delete document;
	}

	document = new tinyxml2::XMLDocument();
	tinyxml2::XMLError error = document->LoadFile(uri.c_str());
	if (error != tinyxml2::XML_SUCCESS)
	{
		// Todo: Log error message here.
		return false;
	}
	return true;
}

bool Big::ConfigFile::Save()
{
	assert(document != nullptr);
	tinyxml2::XMLError error = document->SaveFile(uri.c_str());
	if (error == tinyxml2::XML_SUCCESS)
	{
		return true;
	}
	return false;
}

bool Big::ConfigFile::GetString(const std::string& uri, std::string& outValue, const std::string& defaultValue /*= ""*/)
{
	assert(document != nullptr);

	size_t attributePosition = uri.find_last_of('/');
	const tinyxml2::XMLElement* element = tinyxml2::find_element(document->RootElement(), uri.substr(0, attributePosition).c_str());
	if (element)
	{
		outValue = element->Attribute(uri.substr(attributePosition + 1).c_str());
		return true;
	}
	outValue = defaultValue;
	return false;
}
