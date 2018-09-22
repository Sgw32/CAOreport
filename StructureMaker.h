//File structure maker
#include "setup.h"
using namespace std;

#ifndef STRUCTUREMAKER_H
#define STRUCTUDEMAKER_H

#include "TemplateMaster.h"

class StructureMaker
{
public:
	StructureMaker();
	void setTemplateMaster(TemplateMaster* tm);
	void makeFolderStructure();
	void makeMainHtml();
	void makeTabStrip();
	void makeCharts();
	void makeSheets();
	void copyChartJSFiles();
	void arrangeFilesToFolders();
	void runMainHTML();
	void loadRlsPrefixes();
	string getRlsPrefix(string d1);
	void copyFile(string in_file, string out_file);
private:
	map<string,string> rls_prefs;
	string outdir;
	TemplateMaster* mTm;
};

#endif