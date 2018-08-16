#include "stdafx.h"
#include "TemplateMaster.h"

TemplateMaster::TemplateMaster()
{
	is_ok = true;
	mh = 0;
	tsr = 0;
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
			mh->loadTemplate("template1/");
			templates.push_back(mh);
		}
		catch (...)
		{
			is_ok = false;
		}
		try
		{
			tsr->loadTemplate("template1/");
			templates.push_back(tsr);
		}
		catch (...)
		{
			is_ok = false;
		}
		for (int i=0;i!=mCount;i++)
		{
			SheetGenerator* sh = new SheetGenerator();
			sh->loadTemplate("template1/");
			templates.push_back(sh);
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
	return "";
}

std::string TemplateMaster::returnStatPage2()
{
	return "";
}

std::string TemplateMaster::returnStatPage3()
{
	return "";
}

std::string TemplateMaster::returnStatPage4()
{
	return "";
}

void TemplateMaster::setData()
{
	
}

void TemplateMaster::setFields()
{
	
}

