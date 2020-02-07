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
	SessionLogger::getInstance()->logDataPause("ChartGenerator");
	MTREXPSingleton::getInstance()->generateFullResultTxt();
	SessionLogger::getInstance()->logDataPause("ChartGenerator: Read MTREXP");
	MTREXPSingleton::getInstance()->readResultTxt();
	SessionLogger::getInstance()->logDataPause("ChartGenerator: mIsobares");
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
	a << setfill('0') << setw(2) << mTime;
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
	SessionLogger::getInstance()->logDataPause("ChartGenerator: process mIsobares");
	for (i=0;i!=mIsobares.size();i++)
	{
		isodata* iso = mIsobares[i];
		if (iso)
		{
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

			

			SessionLogger::getInstance()->logData("ChartGenerator: getYData");
			prefix = getYData(i,mTimeId);
			index = newDataset.find("VALUES_DATA");

			stringstream ss2;
			ss2 << "ChartGenerator: prefix " << prefix <<endl;
			SessionLogger::getInstance()->logData(ss2.str());

			while (index != std::string::npos) {
				 /* Make the replacement. */
				 newDataset.replace(index, string("VALUES_DATA").size(), prefix.c_str());
				 /* Advance index forward so the next iteration doesn't pick it up as well. */
				 index += string("VALUES_DATA").size();
				 /* Locate the substring to replace. */
				 index = newDataset.find("VALUES_DATA", index);
			}
			SessionLogger::getInstance()->logData("ChartGenerator: getLineBackground");
			prefix = getLineBackground(i);
			index = newDataset.find("#LINE_COLOR1");
			while (index != std::string::npos) {
				 /* Make the replacement. */
				 newDataset.replace(index, string("#LINE_COLOR1").size(), prefix.c_str());
				 /* Advance index forward so the next iteration doesn't pick it up as well. */
				 index += string("#LINE_COLOR1").size();
				 /* Locate the substring to replace. */
				 index = newDataset.find("#LINE_COLOR1", index);
			}

			index = newDataset.find("#LINE_COLOR2");
			prefix = getLineBorder(i);
			while (index != std::string::npos) {
				 /* Make the replacement. */
				newDataset.replace(index, string("#LINE_COLOR2").size(), prefix.c_str());
				 /* Advance index forward so the next iteration doesn't pick it up as well. */
				index += string("#LINE_COLOR2").size();
				 /* Locate the substring to replace. */
				index = newDataset.find("#LINE_COLOR2", index);
			}
			SessionLogger::getInstance()->logData("ChartGenerator: adding dataset");
		
			stringstream ss;
			ss << "ChartGenerator: newDataset" << newDataset <<endl;
			SessionLogger::getInstance()->logData(ss.str());
			
			mHead=mHead+newDataset;
			mHead+=",\n";
		}
		else
		{
			SessionLogger::getInstance()->logData("Error in isodata! Exiting.");
			cout<<"Error in isodata! Exiting. " <<endl;
			system("pause");
			exit(0);
		}
	}
	SessionLogger::getInstance()->logDataPause("ChartGenerator: finished");

	//RaRa

	SessionLogger::getInstance()->logDataPause("ChartGenerator: process RaRa");
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

	//y-axis-1
	prefix = "y-axis-2";
	index = newDataset.find("y-axis-1");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 newDataset.replace(index, string("y-axis-1").size(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("y-axis-1").size();
		 /* Locate the substring to replace. */
		 index = newDataset.find("y-axis-1", index);
	}

	
	prefix = string("#7f7f7f");
	index = newDataset.find("#LINE_COLOR1");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 newDataset.replace(index, string("#LINE_COLOR1").size(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("#LINE_COLOR1").size();
		 /* Locate the substring to replace. */
		 index = newDataset.find("#LINE_COLOR1", index);
	}

	prefix = string("#7f7f7f");
	index = newDataset.find("#LINE_COLOR2");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		newDataset.replace(index, string("#LINE_COLOR2").size(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		index += string("#LINE_COLOR2").size();
		 /* Locate the substring to replace. */
		index = newDataset.find("#LINE_COLOR2", index);
	}

	mHead=mHead+newDataset;
	SessionLogger::getInstance()->logDataPause("End_ChartGenerator");
}

string ChartGenerator::getLineBackground(int i)
{
	string res = "";
	switch (i)
	{
	case 4:
		res = "#7f007f";
		break;
	case 3:
		res = "#00ffff";
		break;
	case 2:
		res = "#f79646";
		break;
	case 1:
		res = "#ff00ff";
		break;
	case 0:
		res = "#00007f";
		break;
	default:
		res = "#000000";
		break;
	}
	return res;
}

string ChartGenerator::getLineBorder(int i)
{
	string res = "";
	switch (i)
	{
	case 4:
		res = "#7f007f";
		break;
	case 3:
		res = "#00ffff";
		break;
	case 2:
		res = "#ffff00";
		break;
	case 1:
		res = "#ff00ff";
		break;
	case 0:
		res = "#00007f";
		break;
	default:
		res = "#000000";
		break;
	}
	return res;
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
			t.close();
		}	
		else
		{
			cout << "Opening file " << filename << " failed! Exiting." << endl;
			system("pause");
			exit(0);
		}
		
		
	//}
	return p1.substr(1,p1.size()-1);
}