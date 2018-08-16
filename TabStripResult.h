#include <xstring>
#include <fstream>
#include "HTMLTemplate.h"

#ifndef TABSTRIPRESULT_H
#define TABSTRIPRESULT_H

using namespace std;

class TabStripResult : public HTMLTemplate
{
public:
	TabStripResult();
	void loadTemplate(std::string templateDir);
	void process();
	std::string getData();
private:
	std::string mHead;
	std::string mEnding;
};

#endif 
