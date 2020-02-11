// CAOReport.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sstream>
#include "TemplateMaster.h"
#include "ConsoleParams.h"
#include "StructureMaker.h"
#include "MTREXPSingleton.h"
#include "NearStationsSingleton.h"
#include "SessionLogger.h"

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
		SessionLogger::getInstance()->setSessionData(GetExePath(),year,month,station_index,length);
		SessionLogger::getInstance()->openSession();

		if (NearStationsSingleton::getInstance()->checkStationCat(station_index))
		{
			std::cout << "Index not found in station.cat! Exiting program. " <<std::endl;
			SessionLogger::getInstance()->logData("Index not found in station.cat! Exiting program. ");
			system("pause");
			return 1;
		}
		SessionLogger::getInstance()->logData("Station.cat check passed!");

		NearStationsSingleton::getInstance()->setStationIndex(station_index);
		if (NearStationsSingleton::getInstance()->loadBaseFiles())
		{
			std::cout << "Index not found in ahref CSV files! Exiting program. " <<std::endl;
			SessionLogger::getInstance()->logData("Index not found in ahref CSV files! Exiting program. ");
			system("pause");
			return 1;
		}

		string actIndex = NearStationsSingleton::getInstance()->getCurrentStationIndex();
		
		SessionLogger::getInstance()->logData("AHREF data check passed!");

		//NearStationsSingleton::getInstance()->makeAHrefRow(0);
		TemplateMaster* tm = new TemplateMaster();
		StructureMaker* sm = new StructureMaker();
		sm->loadRlsPrefixes();
		SessionLogger::getInstance()->logData("RLS prefixes loaded.");
		tm->setData("","","",length);
		tm->loadTemplates();
		SessionLogger::getInstance()->logData("Templates loaded.");
		//Length - start from (month-length) to (month)
		tm->setActualStationIndex(actIndex);
		tm->setMainHTMLData(year,month,station_index,length);
		SessionLogger::getInstance()->logData("Main HTML file data set ok.");
		tm->processData();
		SessionLogger::getInstance()->logData("Data processed.");
		sm->setTemplateMaster(tm);
		sm->makeFolderStructure();
		SessionLogger::getInstance()->logData("Make folder structure ok.");
		sm->makeMainHtml();
		SessionLogger::getInstance()->logData("Make main .html ok.");
		sm->makeTabStrip();
		sm->makeCharts();
		SessionLogger::getInstance()->logData("Make charts ok.");
		sm->makeSheets();
		SessionLogger::getInstance()->logData("Make sheets ok.");
		sm->copyChartJSFiles();
		SessionLogger::getInstance()->logData("Copy chart files ok.");
		sm->arrangeFilesToFolders();
		SessionLogger::getInstance()->logData("File structure arranged.");
	}
	std::cout<<"CAOReport: OK"<<std::endl;
	SessionLogger::getInstance()->logData("CAOReport: OK");
	system("pause");
	return 0;
}

