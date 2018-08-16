#include "MainHTMLResult.h"
#include "TabStripResult.h"
#include "SheetGenerator.h"

#ifndef TEMPLATEMASTER_H
#define TEMPLATEMASTER_H

//A class for working with HTML templates

using namespace std;

class TemplateMaster
{
public:
	TemplateMaster();
	void setData();
	void loadTemplates();
	void setMainHTMLData(string year, string month,string station_index, string count);
	void processData();
	std::string returnMainHTMLResult();
	std::string returnTabStripResult();
	std::string returnGraph00();
	std::string returnGraph12();
	std::string returnStatPage1();
	std::string returnStatPage2();
	std::string returnStatPage3();
	std::string returnStatPage4();
	void setFields();
private:
	unsigned int mCount;
	bool is_ok;
	string mHtmlReport;
	vector<HTMLTemplate*> templates;
	TabStripResult* tsr;
	MainHTMLResult* mh;
};
#endif
