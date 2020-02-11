#include "MainHTMLResult.h"
#include "TabStripResult.h"
#include "SheetGenerator.h"
#include "ChartGenerator.h"
#include "setup.h"

#ifndef TEMPLATEMASTER_H
#define TEMPLATEMASTER_H

//A class for working with HTML templates

using namespace std;

class TemplateMaster
{
public:
	TemplateMaster();
	void loadTemplates();
	void setMainHTMLData(string year, string month,string station_index, string count);
	void setData(string year, string month,string station_index, string count);
	void setActualStationIndex(string act_index)
	{
		mCurrentStationIndex = act_index;
	}
	void processData();
	std::string returnMainHTMLResult();
	std::string returnTabStripResult();
	std::string returnGraph00();
	std::string returnGraph12();
	std::string returnGraph(size_t i);
	std::string returnStatPage1();
	std::string returnStatPage2();
	std::string returnStatPage3();
	std::string returnStatPage4();
	std::string returnSheet(size_t i);
	std::string getTemplateDirectory();
	int returnSheetsNumber();
	void setFields();
private:
	string template_name;
	string mCurrentStationIndex;
	unsigned int mCount;
	bool is_ok;
	string mHtmlReport;
	vector<HTMLTemplate*> templates;
	vector<SheetGenerator*> sheets;
	vector<ChartGenerator*> charts;
	TabStripResult* tsr;
	MainHTMLResult* mh;
};
#endif
