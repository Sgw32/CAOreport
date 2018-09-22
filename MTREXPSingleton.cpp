#include "stdafx.h"
#include "MTREXPSingleton.h"
  
MTREXPSingleton* MTREXPSingleton::p_instance = 0;

std::string MTREXPSingleton::extendDateByCnt(int cnt,int month,int year)
{
	int months = year*12+month;
	months-=cnt;

	int mf = months%12;
	if (!mf)
		mf=12;
	return string("01.") + IntToStr(mf) + "." + IntToStr(months / 12);
}

std::string MTREXPSingleton::extendEndDateByCnt(int cnt,int month,int year)
{
	cnt += 1;
	int months = year*12+month;
	months-=cnt;
	
	int mf = months%12;

	string endMonthDay;
	if (mf == 4 || mf == 6 || mf == 9 || mf == 11)
		endMonthDay = "30.";
	else if (mf == 02)
	{
		bool leapyear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

		if (leapyear == 0)
				endMonthDay = "29.";
		else 
				endMonthDay = "29.";
	}
	else 
		endMonthDay = "31.";
	
	if (!mf)
		mf=12;

	return endMonthDay + IntToStr(mf) + "." + IntToStr(months / 12);
}

std::string MTREXPSingleton::parseCommas(std::string a)
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

std::string MTREXPSingleton::IntToStr(int a)
{
	stringstream ss;
	ss<<a;
	return ss.str();
}

std::string MTREXPSingleton::FloatToStr(double a)
{
	stringstream ss;
	ss<<std::setprecision(2)<<a;
	return ss.str();
}

double MTREXPSingleton::calcVzvSkzSloy(int time)
{
	if (hadError[0]|hadError[1])
		return 0;
	int nSum = 0;
	double res = 0;
	for (size_t i=0;i!=mIsobares.size();i++)
	{
		isodata* iso = mIsobares[i];
		int N = iso->N[time];
		double vzvSkz = iso->vzv_quad_val1[time];
		nSum+=N;
		res+=(double)N*vzvSkz;
	}
	return res/nSum;
}

double MTREXPSingleton::calcCommonSkzSloy()
{
	if (hadError[0]|hadError[1])
		return 0;
	int nSum = 0;
	double res = 0;
	for (size_t i=0;i!=mIsobares.size();i++)
	{
		isodata* iso = mIsobares[i];
		int N1 = iso->N[0];
		int N2 = iso->N[1];
		int N=N1+N2;
		double vzvSkz = iso->common_quad_val1[0];
		nSum+=N;
		res+=(double)N*vzvSkz*vzvSkz;	
	}
	return sqrt(res/nSum);
}

double MTREXPSingleton::calcCommonVzvSkzSloy()
{
	if (hadError[0]|hadError[1])
		return 0;
	int nSum = 0;
	double res = 0;
	for (size_t i=0;i!=mIsobares.size();i++)
	{
		isodata* iso = mIsobares[i];
		int N = iso->N[0];
		double vzvSkz = iso->vzv_quad_val1[0];
		nSum+=N;
		res+=(double)N*vzvSkz;
	}
	for (size_t i=0;i!=mIsobares.size();i++)
	{
		isodata* iso = mIsobares[i];
		int N = iso->N[1];
		double vzvSkz = iso->vzv_quad_val1[1];
		nSum+=N;
		res+=(double)N*vzvSkz;
	}
	return res/nSum;
}

void MTREXPSingleton::readResultTxt()
{
	for (size_t i=0;i!=mIsobares.size();i++)
	{
		isodata* iso = mIsobares[i];
		delete iso;
	}
	mIsobares.clear();
	string p1;
	string filename = "result.txt";
	std::ifstream t(filename.c_str());
	if (t.is_open())
	{
		t >> mStationName;
		for (int i=0;i!=ISOBARES;i++)
		{
			/*int P;
			int Nn[2];
			double mV[2];
			double qE[2];
			double qV[2];
			double wqV[2];*/
			string sP,sNn[2],sNern[2],smV[2],sqE[2],sqV[2],swqV[2],s_c_qV[2],s_c_wqV[2];
			isodata* iso = new isodata();
			t>> sP >> sNn[0] >> sNern[0] >>smV[0] >> sqE[0] >>sqV[0] >> swqV[0] >> /*s_c_qV[0] >> s_c_wqV[0] >>*/
					sNn[1] >> sNern[1] >> smV[1] >> sqE[1] >>sqV[1] >> swqV[1] >> s_c_qV[0] >> s_c_wqV[0];
			sP = parseCommas(sP);
			sNn[0] = parseCommas(sNn[0]);
			sNn[1] = parseCommas(sNn[1]);
			sNern[0] = parseCommas(sNern[0]);
			sNern[1] = parseCommas(sNern[1]);
			smV[0] = parseCommas(smV[0]);
			smV[1] = parseCommas(smV[1]);
			sqE[0] = parseCommas(sqE[0]);
			sqE[1] = parseCommas(sqE[1]);
			sqV[0] = parseCommas(sqV[0]);
			sqV[1] = parseCommas(sqV[1]);
			swqV[0] = parseCommas(swqV[0]);
			swqV[1] = parseCommas(swqV[1]);

			s_c_qV[0] = parseCommas(s_c_qV[0]);
			//s_c_qV[1] = parseCommas(s_c_qV[1]);
			s_c_wqV[0] = parseCommas(s_c_wqV[0]);
			//s_c_wqV[1] = parseCommas(s_c_wqV[1]);

			iso->isobare = atoi(sP.c_str());
			iso->Nerr.push_back(atof(sNern[0].c_str()));
			iso->Nerr.push_back(atof(sNern[1].c_str()));

			if (atoi(sNn[0].c_str())<=9) 
			{
				hadError[0] = 1;
				iso->iso_hadError[0] = 1;
			}
			if (atoi(sNn[1].c_str())<=9)
			{
				hadError[1] = 1;
				iso->iso_hadError[1] = 1;
			}
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

			iso->common_quad_val1.push_back(atof(s_c_qV[0].c_str()));
			//iso->common_quad_val1.push_back(atof(s_c_qV[1].c_str()));
			iso->common_vzv_quad_val1.push_back(atof(s_c_wqV[0].c_str()));
			//iso->common_vzv_quad_val1.push_back(atof(s_c_wqV[1].c_str()));

			mIsobares.push_back(iso);
		}
		string rzo1,rzo2;
		rzo1=rzo2="";
		std::getline(t,rzo1);
		std::getline(t,rzo1);
		std::getline(t,rzo2);
		mRzoTypesStr.clear();
		mRzoTypesStr.push_back(rzo1);
		mRzoTypesStr.push_back(rzo2);
	}
}

void MTREXPSingleton::setMonthSpan(int mspan)
{
	mMonthSpan = mspan;
}

void MTREXPSingleton::generateResultTxt()
{
	hadError[0] = 0;
	hadError[1] = 0;
	string cmd = "MTREXP.exe \\rep=1 ";
	cmd += "\\loc=0";
	cmd += " \\st="+mStation_index;
	cmd += " \\pere=" + extendEndDateByCnt(-2-mMonthSpan+mCnt,atoi(mMonth.c_str()),atoi(mYear.c_str()));
	cmd += " \\pers=" + extendDateByCnt(mCnt-1-mMonthSpan,atoi(mMonth.c_str()),atoi(mYear.c_str()));
	system(cmd.c_str());
}

void MTREXPSingleton::generateFullResultTxt()
{
	hadError[0] = 1;
	hadError[1] = 1;
	string cmd = "MTREXP.exe \\rep=1 ";
	cmd += "\\loc=0";
	cmd += " \\st="+mStation_index;
	cmd += " \\pere=" + extendEndDateByCnt(-1,atoi(mMonth.c_str()),atoi(mYear.c_str()));
	cmd += " \\pers=" + extendDateByCnt(mCnt-1,atoi(mMonth.c_str()),atoi(mYear.c_str()));
	system(cmd.c_str());
}