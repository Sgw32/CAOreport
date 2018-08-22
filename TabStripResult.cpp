#include "stdafx.h"
#include "TabStripResult.h"

TabStripResult::TabStripResult()
{
}

void TabStripResult::loadTemplate(std::string templateDir)
{
	string p1;
	string p2;
	string filename = templateDir + "\\template_files\\tabstrip_t1.src";
	std::ifstream t(filename.c_str());
	if (t.is_open())
	{
		t.seekg(0, std::ios::end);
		p1.reserve(t.tellg());
		t.seekg(0, std::ios::beg);

		p1.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());
	}
	filename = templateDir + "\\template_files\\tabstrip_t2.src";
	std::ifstream t2(filename.c_str());
	if (t2.is_open())
	{
		t2.seekg(0, std::ios::end);
		p2.reserve(t2.tellg());
		t2.seekg(0, std::ios::beg);

		p2.assign((std::istreambuf_iterator<char>(t2)),
			std::istreambuf_iterator<char>());
	}
	mHead = p1;
	mEnding = p2;
	t.close();
	t2.close();
}

void TabStripResult::process()
{
	for (int i=1;i!=mCnt+1;i++)
	{
		char mth[20];
		mHead += " <td bgcolor=\"#FFFFFF\" nowrap><b><small><small>&nbsp;<a href=\"sheet";
		sprintf_s(mth,"%03d",i);
		string res2 = extendDateByCntV2(i-1,atoi(mMonth.c_str()),atoi(mYear.c_str()));
		mHead += string(mth)+".htm\" target=\"frSheet\"><font face=\"Arial\" color=\"#000000\">"+res2+"</font></a>&nbsp;</small></small></b></td>\n";
	}
}

std::string TabStripResult::getData()
{
	return mHead+mEnding;
}