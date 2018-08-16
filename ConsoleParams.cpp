#include "stdafx.h"
#include "ConsoleParams.h"

std::string GetExeFileName()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	return std::string(buffer);
}

std::string GetExePath()
{
	std::string f = GetExeFileName();
	return f.substr(0, f.find_last_of("\\/"));
}

bool printUsageStrings(int argc, _TCHAR* argv[])
{
	if (argc <= 1)
	{
		std::cout << "CAOReport is a program for generation HTML OB-FG reports" << std::endl;
		std::cout << "usage: " << argv[0] << " Y=yyyy I=iiiii M=mm C=LL" << std::endl;
		return 0;
	}
	return 1;
}

void recognizeToken(string arg)
{
	if (arg.find('Y') != string::npos)
	{
		year = arg.substr(arg.find('Y') + 2, arg.length() - 2);
		params_got++;
	}
	if (arg.find('M') != string::npos)
	{
		month = arg.substr(arg.find('M') + 2, arg.length() - 2);
		params_got++;
	}
	if (arg.find('I') != string::npos)
	{
		station_index = arg.substr(arg.find('I') + 2, arg.length() - 2);
		params_got++;
	}
	if (arg.find('C') != string::npos)
	{
		length = arg.substr(arg.find('C') + 2, arg.length() - 2);
		params_got++;
	}
}

void processInputParameters(int argc, _TCHAR* argv[])
{
	int i;

	for (i = 1; i != argc; i++)
		recognizeToken(string(argv[i]));
}
