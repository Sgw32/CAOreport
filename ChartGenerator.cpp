#include "stdafx.h"
#include "ChartGenerator.h"

ChartGenerator::ChartGenerator()
{
	mImage = "";
	mTime = 0;
}

std::string ChartGenerator::getData()
{
	return mHead;
}

void ChartGenerator::process()
{
	//Process frameset links
	string prefix = mImage;
	size_t index = mHead.find("FILENAME");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 mHead.replace(index, 8, prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += 8;
		 /* Locate the substring to replace. */
		 index = mHead.find("FILENAME", index);
	}
	stringstream a;
	a << mTime;
	prefix = a.str();
	index = mHead.find("TIME");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 mHead.replace(index, 4, prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += 4;
		 /* Locate the substring to replace. */
		 index = mHead.find("TIME", index);
	}
}

void ChartGenerator::setImage(string image)
{
	mImage = image;
}

void ChartGenerator::setTime(int time)
{
	mTime = time;
}

void ChartGenerator::loadTemplate(std::string templateDir)
{
	string p1;
	string p2;
	string filename = templateDir + "\\template_files\\chart.src";
	std::ifstream t(filename.c_str());
	if (t.is_open())
	{
		t.seekg(0, std::ios::end);
		p1.reserve(t.tellg());
		t.seekg(0, std::ios::beg);

		p1.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());
	}	
	mHead = p1;
	t.close();
}

