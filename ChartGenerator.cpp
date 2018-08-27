#include "stdafx.h"
#include "ChartGenerator.h"

ChartGenerator::ChartGenerator()
{
	mImage = "";
	mTime = 0;
}

std::string ChartGenerator::getData()
{
	return mHead+mEnding;
}

void ChartGenerator::process()
{
	MTREXPSingleton::getInstance()->generateFullResultTxt();
	MTREXPSingleton::getInstance()->readResultTxt();
	mIsobares = MTREXPSingleton::getInstance()->mIsobares;
	
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

	index = mEnding.find("TIME");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 mEnding.replace(index, 4, prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += 4;
		 /* Locate the substring to replace. */
		 index = mEnding.find("TIME", index);
	}

	prefix = getXLabels();
	index = mHead.find("LABELS_DATA");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 mHead.replace(index, string("LABELS_DATA").size(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("LABELS_DATA").size();
		 /* Locate the substring to replace. */
		 index = mHead.find("LABELS_DATA", index);
	}

	prefix = mStation_index;
	index = mEnding.find("STATION_NAME");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 mEnding.replace(index, string("STATION_NAME").size(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("STATION_NAME").size();
		 /* Locate the substring to replace. */
		 index = mEnding.find("STATION_NAME", index);
	}

	size_t i;

	for (i=0;i!=mIsobares.size();i++)
	{
		isodata* iso = mIsobares[i];
		string newDataset = mDataset;
		
		prefix = IntToStr2(iso->isobare)+"_"+IntToStr2(mTime);
		index = newDataset.find("DATASET_NAME");
		while (index != std::string::npos) {
			 /* Make the replacement. */
			 newDataset.replace(index, string("DATASET_NAME").size(), prefix.c_str());
			 /* Advance index forward so the next iteration doesn't pick it up as well. */
			 index += string("DATASET_NAME").size();
			 /* Locate the substring to replace. */
			 index = newDataset.find("DATASET_NAME", index);
		}
		prefix = getYData(i,mTimeId);
		index = newDataset.find("VALUES_DATA");
		while (index != std::string::npos) {
			 /* Make the replacement. */
			 newDataset.replace(index, string("VALUES_DATA").size(), prefix.c_str());
			 /* Advance index forward so the next iteration doesn't pick it up as well. */
			 index += string("VALUES_DATA").size();
			 /* Locate the substring to replace. */
			 index = newDataset.find("VALUES_DATA", index);
		}
		mHead=mHead+newDataset;
		mHead+=",\n";
	
	}

	//RaRa

	string newDataset = mDataset;
	
	prefix = string("RaRa_")+IntToStr2(mTime);
	index = newDataset.find("DATASET_NAME");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 newDataset.replace(index, string("DATASET_NAME").size(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("DATASET_NAME").size();
		 /* Locate the substring to replace. */
		 index = newDataset.find("DATASET_NAME", index);
	}
	prefix = getRaRaData(mTimeId);
	index = newDataset.find("VALUES_DATA");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 newDataset.replace(index, string("VALUES_DATA").size(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("VALUES_DATA").size();
		 /* Locate the substring to replace. */
		 index = newDataset.find("VALUES_DATA", index);
	}

	mHead=mHead+newDataset;

}

void ChartGenerator::setImage(string image)
{
	mImage = image;
}

void ChartGenerator::setTime(int time,int id)
{
	mTime = time;
	mTimeId = id;
}

void ChartGenerator::setIsobaresVector(vector<isodata*> isob)
{
	mIsobares = isob;
}

std::string ChartGenerator::getRaRaData(char iUT)
{
	string p1;
	string filename = "result_rara_"+IntToStr2(iUT)+".txt";
	std::ifstream t(filename.c_str());
	if (t.is_open())
	{
		t.seekg(0, std::ios::end);
		p1.reserve(t.tellg());
		t.seekg(0, std::ios::beg);

		p1.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());
	}	
	t.close();
	return p1.substr(1,p1.size()-1);
}

void ChartGenerator::loadTemplate(std::string templateDir)
{
	string p1;
	string filename = templateDir + "\\template_files\\chart_head.src";
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

	filename = templateDir + "\\template_files\\chart_end.src";
	std::ifstream t1(filename.c_str());
	if (t1.is_open())
	{
		t1.seekg(0, std::ios::end);
		p1.reserve(t1.tellg());
		t1.seekg(0, std::ios::beg);

		p1.assign((std::istreambuf_iterator<char>(t1)),
			std::istreambuf_iterator<char>());
	}	
	mEnding = p1;
	t1.close();

	filename = templateDir + "\\template_files\\chart_dataset.src";
	std::ifstream t2(filename.c_str());
	if (t2.is_open())
	{
		t2.seekg(0, std::ios::end);
		p1.reserve(t2.tellg());
		t2.seekg(0, std::ios::beg);

		p1.assign((std::istreambuf_iterator<char>(t2)),
			std::istreambuf_iterator<char>());
	}	
	mDataset = p1;
	t2.close();
}

void ChartGenerator::setMonthSpan(int mspan)
{
	mMonthSpan = mspan;
}

std::string ChartGenerator::getXLabels()
{
	string p1;
	string filename = "result_xdate.txt";
	std::ifstream t(filename.c_str());
	if (t.is_open())
	{
		t.seekg(0, std::ios::end);
		p1.reserve(t.tellg());
		t.seekg(0, std::ios::beg);

		p1.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());
	}	
	t.close();
	return p1.substr(0,p1.size()-1);
}

std::string ChartGenerator::getYData(size_t i,char iUT)
{
	//vector<isodata*>::iterator i;
	string p1="";
	if (!mIsobares.size())
		return p1;
	//for (i=mIsobares.begin();i!=mIsobares.end();i++)
	//{
		isodata* iso = mIsobares[i];
		string p_data = IntToStr2(iso->isobare);
		string ut_data = IntToStr2(iUT);
		string filename = "result_" + p_data + "_" + ut_data + ".txt";
		std::ifstream t(filename.c_str());
		if (t.is_open())
		{
			t.seekg(0, std::ios::end);
			p1.reserve(t.tellg());
			t.seekg(0, std::ios::beg);

			p1.assign((std::istreambuf_iterator<char>(t)),
				std::istreambuf_iterator<char>());
		}	
		t.close();
		
	//}
	return p1.substr(1,p1.size()-1);
}