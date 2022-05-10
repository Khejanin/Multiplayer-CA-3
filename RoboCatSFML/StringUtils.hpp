namespace StringUtils
{
	string GetCommandLineArg(int inIndex);

	string Sprintf(const char* inFormat, ...);

	std::vector<std::string> Split(const std::string& s, char delim);

	void	Log(const char* inFormat);
	void	Log(const char* inFormat, ...);
}

#define LOG( ... ) StringUtils::Log( __VA_ARGS__ );

