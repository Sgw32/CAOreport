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

void StructureMaker::copyChartJSFiles()
{
	copyFile(mTm->getTemplateDirectory()+"\\template_files\\Chart.bundle.js",
		outdir+station_index+"_obfg_g.files\\Chart.bundle.js");
	copyFile(mTm->getTemplateDirectory()+"\\template_files\\utils.js",
		outdir+station_index+"_obfg_g.files\\utils.js");
}

void StructureMaker::arrangeFilesToFolders()
{
	copyFile(mTm->getTemplateDirectory()+"\\template_files\\stylesheet.css",
		outdir+station_index+"_obfg_g.files\\stylesheet.css");
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

void StructureMaker::copyFile(string in_file, string out_file)
{
	ifstream source(in_file.c_str(), ios::binary);
    ofstream dest(out_file.c_str(), ios::binary);

	if (source.is_open())
	{
		// file size
		source.seekg(0, ios::end);
		ifstream::pos_type size = source.tellg();
		source.seekg(0);
		// allocate memory for buffer
		char* buffer = new char[size];

		// copy file    
		source.read(buffer, size);
		dest.write(buffer, size);

		// clean up
		delete[] buffer;
		
	}   
	source.close();
	dest.close();
}

void StructureMaker::makeSheets()
{
	if (mTm)
	{
		for (size_t i = 0;i!=mTm->returnSheetsNumber();i++)
		{
			string data = mTm->returnSheet(i);
			char sheet_num[20];
			sprintf_s(sheet_num,"%03d",i+1);
			string sheetpath = outdir+station_index+"_obfg_g.files\\sheet"+string(sheet_num)+".htm";
			std::ofstream t1(sheetpath.c_str());
			t1<<data;
			t1.close();
		}
	}
}

void StructureMaker::makeCharts()
{
	if (mTm)
	{
		for (size_t i = 0;i!=LAUNCHES_PER_DAY;i++)
		{
			string chart = mTm->returnGraph(i);
			char chart_num[20];
			sprintf_s(chart_num,"%03d",i+1);
			string chartpath = outdir+station_index+"_obfg_g.files\\chart"+string(chart_num)+".htm";
			std::ofstream t1(chartpath.c_str());
			t1<<chart;
			t1.close();
		}
	}
}

void StructureMaker::runMainHTML()
{

}