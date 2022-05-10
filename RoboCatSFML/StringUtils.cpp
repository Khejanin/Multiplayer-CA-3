#include "RoboCatPCH.hpp"

#if !_WIN32
extern const char** __argv;
extern int __argc;
void OutputDebugString(const char* inString)
{
	printf("%s", inString);
}
#endif

string StringUtils::GetCommandLineArg(int inIndex)
{
	if (inIndex < __argc)
	{
		return string(__argv[inIndex]);
	}

	return string();
}


string StringUtils::Sprintf(const char* inFormat, ...)
{
	//not thread safe...
	static char temp[4096];

	va_list args;
	va_start(args, inFormat);

#if _WIN32
	_vsnprintf_s(temp, 4096, 4096, inFormat, args);
#else
	vsnprintf(temp, 4096, inFormat, args);
#endif
	return string(temp);
}


//Taken from https://stackoverflow.com/questions/9435385/split-a-string-using-c11
std::vector<std::string> StringUtils::Split(const std::string& s, char delim)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
		// elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
	}
	return elems;
}


// void StringUtils::Log( const char* inFormat )
// {
// 	OutputDebugString( inFormat );
// 	OutputDebugString( "\n" );
// }

void StringUtils::Log(const char* inFormat, ...)
{
	//not thread safe...
	static char temp[4096];

	va_list args;
	va_start(args, inFormat);

#if _WIN32
	_vsnprintf_s(temp, 4096, 4096, inFormat, args);
#else
	vsnprintf(temp, 4096, inFormat, args);
#endif
	OutputDebugString(temp);
	OutputDebugString("\n");
}
