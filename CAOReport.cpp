// CAOReport.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TemplateMaster.h"

int _tmain(int argc, _TCHAR* argv[])
{
	TemplateMaster* tm = new TemplateMaster;
	string mainHTML = tm->returnMainHTMLResult();
	return 0;
}

