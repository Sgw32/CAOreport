#include <string>

using namespace std;

#ifndef CONSOLEPARAMS_H
#define CONSOLEPARAMS_H

extern string station_index;
extern string year;
extern string month;
extern string length;
extern int params_got;

std::string GetExeFileName();
std::string GetExePath();
bool printUsageStrings(int argc, _TCHAR* argv[]);
void recognizeToken(string arg);
void processInputParameters(int argc, _TCHAR* argv[]);

#endif
