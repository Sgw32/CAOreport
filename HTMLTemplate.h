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

static std::string extendYearByCntV2(int cnt,int month,int year)
{
	int months = year*12+month;
	months-=cnt;
	//Year and month
	int mf = months%12;
	if (mf==0)
	{
		mf=12;
		months--;
	}
	return IntToStr2(months / 12);
}

static std::string extendMonthByCntV2(int cnt,int month,int year)
{
	int months = year*12+month;
	months-=cnt;
	//Year and month
	int mf = months%12;
	if (mf==0)
	{
		mf=12;
		months--;
	}
	return MonthToStr(mf);
}

static std::string extendDateByCntV2(int cnt,int month,int year)
{
	int months = year*12+month;
	months-=cnt;
	//Year and month
	int mf = months%12;
	if (mf==0)
	{
		mf=12;
		months--;
	}
	return IntToStr2(months / 12) + "-" + MonthToStr(mf);
}

/*
std::string MTREXPSingleton::extendDateByCnt(int cnt,int month,int year)
{
	int months = year*12+month;
	months-=cnt;
	
	int mf = months%12;

	if (!mf)
	{
		mf=12;
		months--;
	}
	return string("01.") + IntToStr(mf) + "." + IntToStr(months / 12);
}

*/

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
	void setActualStationIndex(string act_index)
	{
		mCurrentStationIndex = act_index;
	}
	void setMonthCount(unsigned int cnt)
	{
		mCnt = cnt;
		//todo: recalc year
	}
	virtual void process(){};
	virtual std::string getData(){return "";};
	unsigned int mCnt;
	string prefix;
	string mCurrentStationIndex;
	std::string mYear,mMonth,mStation_index;
};

#endif 
