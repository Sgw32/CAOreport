// CAOReport.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sstream>
#include "TemplateMaster.h"
#include "ConsoleParams.h"
#include "StructureMaker.h"

string station_index;
string year;
string month;
string length;
int params_got;

int _tmain(int argc, _TCHAR* argv[])
{
	params_got = 0;
	printUsageStrings(argc, argv);
	processInputParameters(argc, argv);

	if (params_got == 4)
	{
		TemplateMaster* tm = new TemplateMaster();
		StructureMaker* sm = new StructureMaker();
		tm->loadTemplates();
		tm->setMainHTMLData(year,month,station_index,length);
		tm->processData();
		sm->setTemplateMaster(tm);
		sm->makeFolderStructure();
		sm->makeMainHtml();
		sm->makeTabStrip();
	}
	system("pause");
	return 0;
}

