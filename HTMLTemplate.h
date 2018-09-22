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

static std::string MonthToStr(int a)
{
	stringstream ss;
	ss<< setfill('0') << setw(2) <<a;
	return ss.str();
}

static std::string extendDateByCntV2(int cnt,int month,int year)
{
	int months = year*12+month;
	months-=cnt;
	//Year and month
	int mf = months%12;
	if (mf==0)
		mf=12;
	return IntToStr2(months / 12) + "-" + MonthToStr(months%12);
}

class HTMLTemplate
{
public:
	HTMLTemplate(){mCnt = 0;};
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
