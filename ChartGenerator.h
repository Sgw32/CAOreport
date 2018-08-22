#include "HTMLTemplate.h"

#ifndef CHARTGENERATOR_H
#define CHARTGENERATOR_H

using namespace std;

class ChartGenerator : public HTMLTemplate
{
public:
	ChartGenerator();
	void setImage(string image);
	void setTime(int time);
	void loadTemplate(std::string templateDir);
	void process();
	std::string getData();
private:
	int mTime;
	std::string mImage;
	std::string mHead;
	std::string mEnding;
};

#endif 
