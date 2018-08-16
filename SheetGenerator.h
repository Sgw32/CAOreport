#include <xstring>
#include <fstream>
#include "HTMLTemplate.h"

#ifndef SHEETGENERATOR_H
#define SHEETGENERATOR_H

using namespace std;

class SheetGenerator : public HTMLTemplate
{
public:
	SheetGenerator();
	void loadTemplate(std::string templateDir);
	void process();
	std::string getData();
private:
	std::string mHead;
	std::string mEnding;
};

#endif 
