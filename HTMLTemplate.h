#include <xstring>
#include <fstream>

#ifndef HTMLTEMPLATE_H
#define HTMLTEMPLATE_H

using namespace std;

class HTMLTemplate
{
public:
	HTMLTemplate(){};
	virtual void loadTemplate(std::string templateDir){};
	void setData(string year, string month, string station_index)
	{
		mYear = year;
		mMonth = month;
		mStation_index = station_index;
	}
	void setMonthCount(unsigned int cnt)
	{
		mCnt = cnt;
	}
	virtual void process(){};
	virtual std::string getData(){return "";};
	unsigned int mCnt;
	std::string mYear,mMonth,mStation_index;
};

#endif 
