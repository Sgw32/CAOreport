//File structure maker

#ifndef STRUCTUREMAKER_H
#define STRUCTUDEMAKER_H

#include "TemplateMaster.h"

class StructureMaker
{
public:
	StructureMaker();
	void setTemplateMaster(TemplateMaster* tm);
	void makeFolderStructure();
	void arrangeFilesToFolders();
	void runMainHTML();
private:
	TemplateMaster* tm;
};

#endif