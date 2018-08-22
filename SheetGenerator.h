#include "HTMLTemplate.h"
#include "setup.h"

#ifndef SHEETGENERATOR_H
#define SHEETGENERATOR_H

using namespace std;

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

class SheetGenerator : public HTMLTemplate
{
public:
	SheetGenerator();
	void loadTemplate(std::string templateDir);
	void process();
	void generateResultTxt();
	void readResultTxt();
	void processIsobareTable();
	void processHeader();
	void processRzoTypes();
	std::string extendDateByCnt(int cnt,int month,int year);
	std::string processIsobareString(string isoData, isodata* iso);
	void setIsobareMap(map<int,isodata*> isobares);
	std::string getData();
private:
	std::string IntToStr(int a);
	std::string FloatToStr(double a);
	std::string parseCommas(std::string a);
	vector<isodata*> mIsobares;
	vector<string> mRzoTypesStr;
	std::string mHead;
	std::string mSheetData,mSheetDataLast;
	std::string mEnding;
};

#endif 
