#include "HTMLTemplate.h"
#include "MTREXPSingleton.h"

#ifndef CHARTGENERATOR_H
#define CHARTGENERATOR_H

using namespace std;

class ChartGenerator : public HTMLTemplate
{
public:
	ChartGenerator();
	void setImage(string image);
	void setTime(int time,int id);
	void loadTemplate(std::string templateDir);
	void process();
	string getLineBackground(int i);
	string getLineBorder(int i);
	std::string getXLabels();
	std::string getYData(size_t i,char iUT);
	std::string getRaRaData(char iUT);
	std::string getData();
	void setMonthSpan(int mspan);
	void setIsobaresVector(vector<isodata*> isob);
private:
	int mMonthSpan;
	vector<isodata*> mIsobares;
	int mTime;
	int mTimeId;
	std::string mImage;
	std::string mHead;
	std::string mDataset;
	std::string mEnding;
};

#endif 
