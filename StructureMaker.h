//File structure maker

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
	void arrangeFilesToFolders();
	void runMainHTML();
private:
	string outdir;
	TemplateMaster* mTm;
};

#endif