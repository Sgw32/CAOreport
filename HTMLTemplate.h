#include <xstring>
#include <fstream>

#ifndef HTMLTEMPLATE_H
#define HTMLTEMPLATE_H

using namespace std;

static std::string IntToStr2(int a)
{
	stringstream ss;
	ss<<a;
	return ss.str();
}

static std::string extendDateByCntV2(int cnt,int month,int year)
{
	int months = year*12+month;
	months-=cnt;
	return IntToStr2(months / 12) + "-" + IntToStr2(months%12);
}

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
	string prefix;
	std::string mYear,mMonth,mStation_index;
};

#endif 
