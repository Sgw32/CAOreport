#include "stdafx.h"
#include "SheetGenerator.h"

string months_ru[12] = {"Январь", "Февраль", "Март", "Апрель",
"Май", "Июнь", "Июль", "Август",
"Сентябрь", "Октябрь", "Ноябрь", "Декабрь"};

SheetGenerator::SheetGenerator()
{
}

void SheetGenerator::loadTemplate(std::string templateDir)
{
	string p1;
	string p2;
	string p3;
	string p4;
	string filename = templateDir + "\\template_files\\sheet_p1.src";
	std::ifstream t(filename.c_str());
	if (t.is_open())
	{
		t.seekg(0, std::ios::end);
		p1.reserve(t.tellg());
		t.seekg(0, std::ios::beg);

		p1.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());
	}
	filename = templateDir + "\\template_files\\sheet_p2.src";
	std::ifstream t2(filename.c_str());
	if (t2.is_open())
	{
		t2.seekg(0, std::ios::end);
		p2.reserve(t2.tellg());
		t2.seekg(0, std::ios::beg);

		p2.assign((std::istreambuf_iterator<char>(t2)),
			std::istreambuf_iterator<char>());
	}

	filename = templateDir + "\\template_files\\sheet_data.src";
	std::ifstream t3(filename.c_str());
	if (t3.is_open())
	{
		t3.seekg(0, std::ios::end);
		p3.reserve(t3.tellg());
		t3.seekg(0, std::ios::beg);

		p3.assign((std::istreambuf_iterator<char>(t3)),
			std::istreambuf_iterator<char>());
	}

	filename = templateDir + "\\template_files\\sheet_data_last.src";
	std::ifstream t4(filename.c_str());
	if (t4.is_open())
	{
		t4.seekg(0, std::ios::end);
		p4.reserve(t4.tellg());
		t4.seekg(0, std::ios::beg);

		p4.assign((std::istreambuf_iterator<char>(t4)),
			std::istreambuf_iterator<char>());
	}

	mHead = p1;
	mEnding = p2;
	mSheetData = p3;
	mSheetDataLast = p4;
	t.close();
	t2.close();
	t3.close();
	t4.close();
}

void SheetGenerator::processHeader()
{
	string prefix = mStation_index;
	size_t index = mHead.find("STATION_INDEX");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 mHead.replace(index, string("STATION_INDEX").size(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("STATION_INDEX").size();
		 /* Locate the substring to replace. */
		 index = mHead.find("STATION_INDEX", index);
	}

	prefix = "";
	index = mHead.find("STATION_NAME");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 mHead.replace(index, string("STATION_NAME").size(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("STATION_NAME").size();
		 /* Locate the substring to replace. */
		 index = mHead.find("STATION_NAME", index);
	}

	prefix = mYear;
	index = mHead.find("YEAR_TEXT_NUM");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 mHead.replace(index, string("YEAR_TEXT_NUM").size(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("YEAR_TEXT_NUM").size();
		 /* Locate the substring to replace. */
		 index = mHead.find("YEAR_TEXT_NUM", index);
	}

	string month_num = "";
	if ((atoi(mMonth.c_str()-1)>=0) && (atoi(mMonth.c_str()-1)<12))
		month_num = months_ru[atoi(mMonth.c_str())-1];
	prefix = month_num;
	index = mHead.find("MONTH_TEXT_RU");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 mHead.replace(index, string("MONTH_TEXT_RU").size(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("MONTH_TEXT_RU").size();
		 /* Locate the substring to replace. */
		 index = mHead.find("MONTH_TEXT_RU", index);
	}
}

void SheetGenerator::processRzoTypes()
{
	if (mRzoTypesStr.size()==2) //Full data set
	{
		//Process RZO types
		string prefix = mRzoTypesStr[0];
		size_t index = mEnding.find("RZO_TYPE_NUMBER1");
		while (index != std::string::npos) {
			 /* Make the replacement. */
			 mEnding.replace(index, string("RZO_TYPE_NUMBER1").size(), prefix.c_str());
			 /* Advance index forward so the next iteration doesn't pick it up as well. */
			 index += string("RZO_TYPE_NUMBER1").size();
			 /* Locate the substring to replace. */
			 index = mEnding.find("RZO_TYPE_NUMBER1", index);
		}

		//Process RZO types
		prefix = mRzoTypesStr[1];
		index = mEnding.find("RZO_TYPE_NUMBER2");
		while (index != std::string::npos) {
			 /* Make the replacement. */
			 mEnding.replace(index, string("RZO_TYPE_NUMBER2").size(), prefix.c_str());
			 /* Advance index forward so the next iteration doesn't pick it up as well. */
			 index += string("RZO_TYPE_NUMBER2").size();
			 /* Locate the substring to replace. */
			 index = mEnding.find("RZO_TYPE_NUMBER2", index);
		}
	}
}

std::string SheetGenerator::extendDateByCnt(int cnt,int month,int year)
{
	int months = year*12+month;
	months-=cnt;
	return string("01.") + IntToStr(months%12) + "." + IntToStr(months / 12);
}

void SheetGenerator::generateResultTxt()
{
	string cmd = "MTREXP.exe \\rep=1 ";
	cmd += "\\loc=0";
	cmd += " \\st="+mStation_index;
	cmd += " \\pere=01." + mMonth + '.' + mYear;
	cmd += " \\pers=" + extendDateByCnt(mCnt,atoi(mMonth.c_str()),atoi(mYear.c_str()));
	//system(cmd.c_str());
}

void SheetGenerator::readResultTxt()
{
	string p1;
	string filename = "result.txt";
	std::ifstream t(filename.c_str());
	if (t.is_open())
	{
		for (int i=0;i!=ISOBARES;i++)
		{
			/*int P;
			int Nn[2];
			double mV[2];
			double qE[2];
			double qV[2];
			double wqV[2];*/
			string sP,sNn[2],smV[2],sqE[2],sqV[2],swqV[2];
			isodata* iso = new isodata();
			t>> sP >> sNn[0] >> smV[0] >> sqE[0] >>sqV[0] >> swqV[0] >>
					sNn[1] >> smV[1] >> sqE[1] >>sqV[1] >> swqV[1];
			sP = parseCommas(sP);
			sNn[0] = parseCommas(sNn[0]);
			sNn[1] = parseCommas(sNn[1]);
			smV[0] = parseCommas(smV[0]);
			smV[1] = parseCommas(smV[1]);
			sqE[0] = parseCommas(sqE[0]);
			sqE[1] = parseCommas(sqE[1]);
			sqV[0] = parseCommas(sqV[0]);
			sqV[1] = parseCommas(sqV[1]);
			swqV[0] = parseCommas(swqV[0]);
			swqV[1] = parseCommas(swqV[1]);
			iso->isobare = atoi(sP.c_str());
			iso->N.push_back(atof(sNn[0].c_str()));
			iso->N.push_back(atof(sNn[1].c_str()));
			iso->meanV.push_back(atof(smV[0].c_str()));
			iso->meanV.push_back(atof(smV[1].c_str()));
			iso->quad_err1.push_back(atof(sqE[0].c_str()));
			iso->quad_err1.push_back(atof(sqE[1].c_str()));
			iso->quad_val1.push_back(atof(sqV[0].c_str()));
			iso->quad_val1.push_back(atof(sqV[1].c_str()));
			iso->vzv_quad_val1.push_back(atof(swqV[0].c_str()));
			iso->vzv_quad_val1.push_back(atof(swqV[1].c_str()));
			mIsobares.push_back(iso);
		}
		string rzo1,rzo2;
		rzo1=rzo2="";
		std::getline(t,rzo1);
		std::getline(t,rzo1);
		std::getline(t,rzo2);
		mRzoTypesStr.push_back(rzo1);
		mRzoTypesStr.push_back(rzo2);
	}
}

std::string SheetGenerator::parseCommas(std::string a)
{
	string prefix = ".";
	size_t index = a.find(",");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 a.replace(index, string(",").size(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string(",").size();
		 /* Locate the substring to replace. */
		 index = a.find(",", index);
	}
	return a;
}

std::string SheetGenerator::IntToStr(int a)
{
	stringstream ss;
	ss<<a;
	return ss.str();
}

std::string SheetGenerator::FloatToStr(double a)
{
	stringstream ss;
	ss<<std::setprecision(2)<<a;
	return ss.str();
}

std::string SheetGenerator::processIsobareString(string isoData, isodata* iso)
{
	string result = isoData;
	//Set isobare value
	string prefix = IntToStr(iso->isobare);
	size_t index = result.find("ISOBARE_VALUE");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 result.replace(index, string("ISOBARE_VALUE").length(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("ISOBARE_VALUE").length();
		 /* Locate the substring to replace. */
		 index = result.find("ISOBARE_VALUE", index);
	}
	//Set N0
	prefix = IntToStr(iso->N[0]);
	index = result.find("NUM_VALUE0");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 result.replace(index, string("NUM_VALUE0").length(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("NUM_VALUE0").length();
		 /* Locate the substring to replace. */
		 index = result.find("NUM_VALUE0", index);
	}
	//Set N1
	prefix = IntToStr(iso->N[1]);
	index = result.find("NUM_VALUE1");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 result.replace(index, string("NUM_VALUE1").length(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("NUM_VALUE1").length();
		 /* Locate the substring to replace. */
		 index = result.find("NUM_VALUE1", index);
	}
	//Set MEAN_VALUE0
	prefix = FloatToStr(iso->meanV[0]);
	index = result.find("MEAN_VALUE0");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 result.replace(index, string("MEAN_VALUE0").length(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("MEAN_VALUE0").length();
		 /* Locate the substring to replace. */
		 index = result.find("MEAN_VALUE0", index);
	}
	//Set MEAN_VALUE1
	prefix = FloatToStr(iso->meanV[1]);
	index = result.find("MEAN_VALUE1");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 result.replace(index, string("MEAN_VALUE1").length(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("MEAN_VALUE1").length();
		 /* Locate the substring to replace. */
		 index = result.find("MEAN_VALUE1", index);
	}
	//Set QUADRATIC_ERROR0
	prefix = FloatToStr(iso->quad_err1[0]);
	index = result.find("QUADRATIC_ERROR0");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 result.replace(index, string("QUADRATIC_ERROR0").length(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("QUADRATIC_ERROR0").length();
		 /* Locate the substring to replace. */
		 index = result.find("QUADRATIC_ERROR0", index);
	}
	//Set QUADRATIC_ERROR1
	prefix = FloatToStr(iso->quad_err1[1]);
	index = result.find("QUADRATIC_ERROR1");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 result.replace(index, string("QUADRATIC_ERROR1").length(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("QUADRATIC_ERROR1").length();
		 /* Locate the substring to replace. */
		 index = result.find("QUADRATIC_ERROR1", index);
	}
	//Set QUADRATIC_VALUE0
	prefix = FloatToStr(iso->quad_val1[0]);
	index = result.find("QUADRATIC_VALUE0");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 result.replace(index, string("QUADRATIC_VALUE0").length(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("QUADRATIC_VALUE0").length();
		 /* Locate the substring to replace. */
		 index = result.find("QUADRATIC_VALUE0", index);
	}
	//Set QUADRATIC_VALUE1
	prefix = FloatToStr(iso->quad_val1[1]);
	index = result.find("QUADRATIC_VALUE1");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 result.replace(index, string("QUADRATIC_VALUE1").length(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("QUADRATIC_VALUE1").length();
		 /* Locate the substring to replace. */
		 index = result.find("QUADRATIC_VALUE1", index);
	}
	//Set QUADRATIC_VALUE0
	prefix = FloatToStr(iso->vzv_quad_val1[0]);
	index = result.find("WEIGHTED_VALUE0");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 result.replace(index, string("WEIGHTED_VALUE0").length(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("WEIGHTED_VALUE0").length();
		 /* Locate the substring to replace. */
		 index = result.find("WEIGHTED_VALUE0", index);
	}
	//Set QUADRATIC_VALUE1
	prefix = FloatToStr(iso->vzv_quad_val1[1]);
	index = result.find("WEIGHTED_VALUE1");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 result.replace(index, string("WEIGHTED_VALUE1").length(), prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += string("WEIGHTED_VALUE1").length();
		 /* Locate the substring to replace. */
		 index = result.find("WEIGHTED_VALUE1", index);
	}
	return result;
}

void SheetGenerator::processIsobareTable()
{
	vector<isodata*>::iterator i;
	for (i=mIsobares.begin();i!=mIsobares.end();i++)
	{
		isodata* iso = (*i);
		string new_sheet_data = "";
		if (i!=mIsobares.end()-1)
			new_sheet_data = processIsobareString(mSheetData, iso);
		else
			new_sheet_data = processIsobareString(mSheetDataLast, iso);
		mHead+=new_sheet_data;
	}
}

void SheetGenerator::process()
{
	generateResultTxt();
	readResultTxt();
	processHeader();
	processIsobareTable();
	processRzoTypes();
}

string SheetGenerator::getData()
{
	return mHead+mEnding;
}