#include "LogFile.h"

#include <time.h>
#include <iomanip>

Big::LogFile::LogFile()
{}

Big::LogFile::LogFile(const LogFile& logFile)
{}

Big::LogFile::~LogFile()
{}

bool Big::LogFile::Create(const std::string& filename, bool doSupressFileOutput /*= false*/, bool doLogTimeStamps /*= true*/)
{
	uri = filename;
	supressFileOutput = doSupressFileOutput;
	logTimestamps = doLogTimeStamps;

	if (!supressFileOutput)
	{
		filestream.open(uri);
		return filestream.is_open();
	}

	return false;
}

void Big::LogFile::Destroy()
{
	if (!supressFileOutput)
	{
		filestream.close();
	}
}

void Big::LogFile::DoLog(const std::string& message, LogType logType /* = Info */)
{
	if (!supressFileOutput)
	{
		if (logTimestamps)
		{
			time_t rawTime;
			tm timeInfo;
			time(&rawTime);
			localtime_s(&timeInfo, &rawTime);

			filestream << std::setw(2) << std::setfill('0') << timeInfo.tm_hour
				<< ':' << std::setw(2) << std::setfill('0') << timeInfo.tm_min
				<< ':' << std::setw(2) << std::setfill('0') << timeInfo.tm_sec
				<< " - ";
		}

		switch (logType)
		{
		case Big::LogFile::Info:
			filestream << "Info: ";
			break;
		case Big::LogFile::Warning:
			filestream << "Warning: ";
			break;
		case Big::LogFile::Error:
			filestream << "Error: ";
			break;
		default:
			break;
		}

		filestream << message << std::endl;
		filestream.flush();
	}
}
