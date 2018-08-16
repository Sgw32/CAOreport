#include "stdafx.h"
#include "MainHTMLResult.h"

MainHTMLResult::MainHTMLResult()
{
	
}

std::string MainHTMLResult::getData()
{
	//Чего то я подумал, тут половина всего этого мусор ненужный.
	//return mHead + mSheet_links + mJs_data + mXml_excel_workbook + mFrameset_srcs + mEnding;
	return mHead + mFrameset_srcs + mEnding;
}

void MainHTMLResult::process()
{
	//Add sheet links
	/*
	for (int i=1;i!=mCnt+1;i++)
	{
		char mth[20];
		mSheet_links += "<link id=\"shLink\" href=\"template_menu.files/sheet";
		sprintf_s(mth,"%03d",i);
		mSheet_links += string(mth)+".htm\">\n";
	}
	*/
	//Process frameset links
	string prefix = mStation_index + "_obfg_g";
	size_t index = mFrameset_srcs.find("template_menu");
	while (index != std::string::npos) {
		 /* Make the replacement. */
		 mFrameset_srcs.replace(index, 13, prefix.c_str());
		 /* Advance index forward so the next iteration doesn't pick it up as well. */
		 index += 13;
		 /* Locate the substring to replace. */
		 index = mFrameset_srcs.find("template_menu", index);
	}
	
}

void MainHTMLResult::loadTemplate(std::string templateDir)
{
	string head;
	string sheet_links;
	string js_data;
	string xml_excel_workbook;
	string frameset_srcs;
	string ending;
	string filename = templateDir + "head.src";
	std::ifstream t(filename.c_str());
	if (t.is_open())
	{
		t.seekg(0, std::ios::end);
		head.reserve(t.tellg());
		t.seekg(0, std::ios::beg);

		head.assign((std::istreambuf_iterator<char>(t)),
			std::istreambuf_iterator<char>());
	}
	filename = templateDir + "sheet_links.src";
	std::ifstream t1(filename.c_str());
	if (t1.is_open())
	{
		t1.seekg(0, std::ios::end);
		sheet_links.reserve(t1.tellg());
		t1.seekg(0, std::ios::beg);

		sheet_links.assign((std::istreambuf_iterator<char>(t1)),
			std::istreambuf_iterator<char>());
	}
	filename = templateDir + "js_data.src";
	std::ifstream t2(filename.c_str());
	if (t2.is_open())
	{
		t2.seekg(0, std::ios::end);
		js_data.reserve(t2.tellg());
		t2.seekg(0, std::ios::beg);

		js_data.assign((std::istreambuf_iterator<char>(t2)),
			std::istreambuf_iterator<char>());
	}
	filename = templateDir + "xml_excel_workbook.src";
	std::ifstream t3(filename.c_str());
	if (t3.is_open())
	{
		t3.seekg(0, std::ios::end);
		xml_excel_workbook.reserve(t3.tellg());
		t3.seekg(0, std::ios::beg);

		xml_excel_workbook.assign((std::istreambuf_iterator<char>(t3)),
			std::istreambuf_iterator<char>());
	}
	filename = templateDir + "frameset_srcs.src";
	std::ifstream t4(filename.c_str());
	if (t4.is_open())
	{
		t4.seekg(0, std::ios::end);
		frameset_srcs.reserve(t4.tellg());
		t4.seekg(0, std::ios::beg);

		frameset_srcs.assign((std::istreambuf_iterator<char>(t4)),
			std::istreambuf_iterator<char>());
	}
	filename = templateDir + "ending.src";
	std::ifstream t5(filename.c_str());
	if (t5.is_open())
	{
		t5.seekg(0, std::ios::end);
		ending.reserve(t5.tellg());
		t5.seekg(0, std::ios::beg);

		ending.assign((std::istreambuf_iterator<char>(t5)),
			std::istreambuf_iterator<char>());
	}
	mHead = head;
	mSheet_links = sheet_links;
	mJs_data = js_data;
	mXml_excel_workbook = xml_excel_workbook;
	mFrameset_srcs = frameset_srcs;
	mEnding = ending;
	t.close();
	t1.close();
	t2.close();
	t3.close();
	t4.close();
}

