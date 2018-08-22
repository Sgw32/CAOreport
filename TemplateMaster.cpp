#include "stdafx.h"
#include "TemplateMaster.h"

TemplateMaster::TemplateMaster()
{
	is_ok = true;
	mh = 0;
	tsr = 0;
	mCount = 0;
	template_name = "template1/";
}

std::string TemplateMaster::returnMainHTMLResult()
{
	if (is_ok)
	{
		return mh->getData();
	}
	return "";
}

void TemplateMaster::setMainHTMLData(string year, string month,string station_index, string count)
{
	vector<HTMLTemplate*>::iterator i;
	for (i=templates.begin();i!=templates.end();i++)
	{
		HTMLTemplate* mh = (*i);
		if (mh)
		{
			mh->setData(year,month,station_index);
			mh->setMonthCount(atoi(count.c_str()));
		}
	}
	mCount = atoi(count.c_str());
}

void TemplateMaster::processData()
{
	vector<HTMLTemplate*>::iterator i;
	for (i=templates.begin();i!=templates.end();i++)
	{
		HTMLTemplate* mh = (*i);
		if (mh)
		{
			mh->process();
		}
	}	
}

void TemplateMaster::loadTemplates()
{
	if (!mh)
	{
		mh = new MainHTMLResult();
		tsr = new TabStripResult();
		is_ok = true;
		try
		{
			mh->loadTemplate(template_name);
			templates.push_back(mh);
		}
		catch (...)
		{
			is_ok = false;
		}
		try
		{
			tsr->loadTemplate(template_name);
			templates.push_back(tsr);
		}
		catch (...)
		{
			is_ok = false;
		}
		int times[LAUNCHES_PER_DAY] = LAUNCHES_TIMES;
		for (int i=0;i!=LAUNCHES_PER_DAY;i++)
		{
			char mth[20];
			sprintf_s(mth,"%03d",i+1);
			ChartGenerator* sh = new ChartGenerator();
			sh->setTime(times[i]);
			sh->setImage("image"+string(mth)+".png");
			sh->loadTemplate(template_name);
			templates.push_back(sh);
			charts.push_back(sh);
		}
		for (int i=0;i!=mCount;i++)
		{
			SheetGenerator* sh = new SheetGenerator();
			sh->loadTemplate(template_name);
			templates.push_back(sh);
			sheets.push_back(sh);
		}
	}
}

std::string TemplateMaster::returnTabStripResult()
{
	if (is_ok)
	{
		return tsr->getData();
	}
	return "";
}

std::string TemplateMaster::returnGraph00()
{
	return "";
}

std::string TemplateMaster::returnGraph12()
{
	return "";
}

std::string TemplateMaster::returnStatPage1()
{
	return sheets[0]->getData();
}

std::string TemplateMaster::returnStatPage2()
{
	return sheets[1]->getData();
}

std::string TemplateMaster::returnStatPage3()
{
	return sheets[2]->getData();
}

std::string TemplateMaster::returnStatPage4()
{
	return sheets[3]->getData();
}

std::string TemplateMaster::returnGraph(size_t i)
{
	if (charts.size()<i)
		return "";
	return charts[i]->getData();
}

std::string TemplateMaster::returnSheet(size_t i)
{
	if (sheets.size()<i)
		return "";
	return sheets[i]->getData();
}

int TemplateMaster::returnSheetsNumber()
{
	return sheets.size();
}

std::string TemplateMaster::getTemplateDirectory()
{
	return template_name;
}

void TemplateMaster::setData(string year, string month,string station_index, string count)
{
	mCount = atoi(count.c_str());
}

void TemplateMaster::setFields()
{
	
}

