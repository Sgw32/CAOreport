#include "stdafx.h"
#include "StructureMaker.h"
#include "ConsoleParams.h"

StructureMaker::StructureMaker()
{
	mTm=0;
}

void StructureMaker::setTemplateMaster(TemplateMaster* tm)
{
	mTm = tm;
}

void StructureMaker::makeFolderStructure()
{
	outdir = GetExePath()+"\\results\\" + year + "\\" + month + "\\"
			+ station_index + "\\";
	string res_dir = string("md "+GetExePath()+"\\results\\" + year + "\\" + month + "\\" 
			+ station_index + "\\" + station_index + "_obfg_g.files");
	system(res_dir.c_str());
	
}

void StructureMaker::arrangeFilesToFolders()
{
	
}

void StructureMaker::makeMainHtml()
{
	if (mTm)
	{
		string mainHTML = mTm->returnMainHTMLResult();
		string mainHTMLpath = outdir+station_index+"_obfg_g.htm";
		std::ofstream t1(mainHTMLpath.c_str());
		t1<<mainHTML;
		t1.close();
	}
}

void StructureMaker::makeTabStrip()
{
	if (mTm)
	{
		string tabstrip = mTm->returnTabStripResult();
		string tabstrippath = outdir+station_index+"_obfg_g.files\\tabstrip.htm";
		std::ofstream t1(tabstrippath.c_str());
		t1<<tabstrip;
		t1.close();
	}
}

void StructureMaker::runMainHTML()
{

}