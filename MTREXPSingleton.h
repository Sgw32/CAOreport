#include "setup.h"

using namespace std;

#ifndef MTREXPSINGLETON_H
#define MTREXPSINGLETON_H

class isodata
{
public:
	isodata()
	{
		isobare=0;
	};
	vector<int> times;
	int isobare;
	vector<int> N;
	vector<double> meanV;
	vector<double> quad_err1;
	vector<double> quad_val1;
	vector<double> vzv_quad_val1;
};

class MTREXPSingleton
{
  private:
    static MTREXPSingleton * p_instance;
    // Конструкторы и оператор присваивания недоступны клиентам
    MTREXPSingleton() {}
    MTREXPSingleton( const MTREXPSingleton& );  
    MTREXPSingleton& operator=( MTREXPSingleton& );
  public:
	unsigned int mCnt;
	string prefix;
	std::string mYear,mMonth,mStation_index;
	int mMonthSpan;
	string mStationName;
	vector<isodata*> mIsobares;
	vector<string> mRzoTypesStr;
	void generateResultTxt();
	void generateFullResultTxt();
	void readResultTxt();
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
	std::string IntToStr(int a);
	std::string FloatToStr(double a);
	std::string parseCommas(std::string a);
	std::string extendDateByCnt(int cnt,int month,int year);
	void setMonthSpan(int mspan);
    static MTREXPSingleton * getInstance() {
        if(!p_instance)           
            p_instance = new MTREXPSingleton();
        return p_instance;
    }
};

#endif