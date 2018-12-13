#pragma once

#include <string>

namespace Big
{
	class StringHelper
	{
	public:
		static bool StringToBool(const std::string& value);
		static int StringToInt(const std::string& value);

		static void BoolToString(bool value, std::string& outValue);
		static void IntToString(int value, std::string& outValue);

	private:
		StringHelper();
		~StringHelper();
	};
}
