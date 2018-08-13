#ifndef TEMPLATEMASTER_H
#define TEMPLATEMASTER_H
#include <string>
#include <iostream>

using namespace std;

class TemplateMaster
{
public:
	TemplateMaster();
	void setData();
	std::string returnMainHTMLResult();
	std::string returnGraph00();
	std::string returnGraph12();
	std::string returnGraphStatPage1();
	std::string returnGraphStatPage2();
	std::string returnGraphStatPage3();
	std::string returnGraphStatPage4();
	void setFields();
private:
	bool is_ok;
	string mHtmlReport;
};
#endif
