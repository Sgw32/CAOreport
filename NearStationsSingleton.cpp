#include "stdafx.h"
#include "NearStationsSingleton.h"
  
NearStationsSingleton* NearStationsSingleton::p_instance = 0;

void NearStationsSingleton::setStationIndex(string index)
{
	mStationIndex = index;
}

string NearStationsSingleton::makeAHrefRow(size_t i)
{
	if (ns->href.size()<=i)
		return "<a></a>";
	map<string,string>::iterator it = ns->href.begin();
	advance(it,i);
	string result = "<a href=\"" + (*it).second + "\" target=\"_parent\">" + (*it).first + "</a>";
	return result;
}	

void NearStationsSingleton::loadBaseFiles()
{
	std::ifstream t("ahref_names.csv");
	string st_data;
	if (t.is_open())
	{
		while (std::getline(t,st_data))
		{
			if (st_data.find(mStationIndex.c_str())!= std::string::npos)
			{
				break;
			}
		}
	}

	std::ifstream t1("ahref_links.csv");
	string st_link;
	if (t1.is_open())
	{
		while (std::getline(t1,st_link))
		{
			if ((st_link.find(mStationIndex.c_str())!= std::string::npos)&&
				(st_link.find(";")>st_link.find(mStationIndex.c_str())))
			{
				break;
			}
		}
	}

	//30554,Усть-Баргузин,Чита,Чара,Могоча,Красный,Чикой	

	map<string,string> lList;

	size_t comma1 = st_data.find(";");
	string data = st_data.substr(0,comma1); //station
	size_t comma2 = st_link.find(";");
	string link = st_link.substr(0,comma2); //link
	st_data=st_data.substr(comma1+1,st_data.size()-comma1-1);
	st_link=st_link.substr(comma2+1,st_link.size()-comma2-1);
	while (st_data.find(";"))
	{
		comma1 = st_data.find(";");
		data = st_data.substr(0,comma1); //station
		comma2 = st_link.find(";");
		link = st_link.substr(0,comma2); //link
		st_data=st_data.substr(comma1+1,st_data.size()-comma1-1);
		st_link=st_link.substr(comma2+1,st_link.size()-comma2-1);
		lList[data] = link;
	}
	
	if (ns)
		delete ns;
	ns = new NearStations();
	ns->href = lList;
}