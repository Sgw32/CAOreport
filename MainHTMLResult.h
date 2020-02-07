#include <xstring>
#include <fstream>
#include "HTMLTemplate.h"
#include "SessionLogger.h"

#ifndef MAINHTMLRESULT_H
#define MAINHTMLRESULT_H

using namespace std;

class MainHTMLResult : public HTMLTemplate
{
public:
	MainHTMLResult();
	void loadTemplate(std::string templateDir);
	void process();
	std::string getData();
private:
	//unsigned int mCnt;
	//std::string mYear,mMonth,mStation_index;
	std::string mHead;
	std::string mSheet_links;
	std::string mJs_data;
	std::string mXml_excel_workbook;
	std::string mFrameset_srcs;
	std::string mEnding;
};

#endif 
