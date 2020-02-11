#include "stdafx.h"
#include "NearStationsSingleton.h"
#include "SessionLogger.h"

NearStationsSingleton* NearStationsSingleton::p_instance = 0;

std::string GetExeFileName();

std::string GetExePath();

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

int NearStationsSingleton::checkStationCat(string index)
{
	SessionLogger::getInstance()->logData("Loading station.cat from:"+GetExePath()+"/station.cat");
	std::ifstream t("station.cat");
	if (t.is_open())
	{
		//std::string str((std::istreambuf_iterator<char>(t)),
		//				 std::istreambuf_iterator<char>());
		std::string str = "";
		while (!t.eof())
		{
			std::getline(t,str);
			if (str.find(index.c_str())!= std::string::npos)
			{
				SessionLogger::getInstance()->logData("Found station.cat entry for selected index:" + str);
				mCurrentStationIndex = str.substr(1,5);
				SessionLogger::getInstance()->logData("Actual index:" + mCurrentStationIndex);
				string curData = "";
				int cnt = 0;
				for (int i=5;i!=str.length();i++)
				{
					curData=curData+str[i];
					cnt++;
					SessionLogger::getInstance()->logData(curData);
					if (str[i]==' ')
					{
						curData="";
						cnt=0;
					}
					if (str[i]=='.')
					{
						curData="";
						cnt=0;
					}					
					if (cnt==5)
					{
						altStationNames.push_back(curData);
						SessionLogger::getInstance()->logData("Alt station name: " + curData);
						curData = "";
						cnt = 0;
					}
				}
				return 0; //No error
			}
		}
	}
	else
		return 1; //Error
	return 1; // Not found
}

int NearStationsSingleton::loadBaseFiles()
{
	std::ifstream t("ahref_names.csv");
	string st_data="";
	int found = 0;
#ifdef VERBOSE
	cout<<"NSS:ahref_names.csv"<<endl;
#endif
	if (t.is_open())
	{
		while (std::getline(t,st_data))
		{
			if (!found)
			{
				if (st_data.find(mStationIndex.c_str())!= std::string::npos)
				{
	#ifdef VERBOSE
					cout<<"NSS: FOUND!"<<endl;
	#endif
					found=1;
					break;
				}
				if (st_data.find(mCurrentStationIndex.c_str())!= std::string::npos)
				{
	#ifdef VERBOSE
					cout<<"NSS: FOUND!"<<endl;
	#endif
					found=1;
					break;
				}

				for (int i=0;i!=altStationNames.size();i++)
				{
					if (st_data.find(altStationNames[i].c_str())!= std::string::npos)
					{
	#ifdef VERBOSE
						cout<<"NSS: FOUND!"<<endl;
	#endif
						found=1;
						break;
					}
				}
			}
		}
	}
	else
		return 1;
	if (!found)
		return 1; //Station name not found
#ifdef VERBOSE
	cout<<"NSS:ahref_links.csv"<<endl;
#endif
	found=0;
	std::ifstream t1("ahref_links.csv");
	string st_link="";
	
	if (t1.is_open())
	{
		while (std::getline(t1,st_link)&&(!found))
		{
			if (!found)
			{
				if ((st_link.find(mStationIndex.c_str())!= std::string::npos)&&
					(st_link.find(";")>st_link.find(mStationIndex.c_str())))
				{
					found=1;
					break;
				}
				if ((st_link.find(mCurrentStationIndex.c_str())!= std::string::npos)&&
					(st_link.find(";")>st_link.find(mStationIndex.c_str())))
				{
					found=1;
					break;
				}

				for (int i=0;i!=altStationNames.size();i++)
				{
					if ((st_link.find(altStationNames[i].c_str())!= std::string::npos)&&
					(st_link.find(";")>st_link.find(altStationNames[i].c_str())))
					{
						found=1;
						break;
					}
				}
			}
		}
	}
	else
		return 1;
	
	if (!found)
		return 1; //Station link not found

	//30554,Усть-Баргузин,Чита,Чара,Могоча,Красный,Чикой	
#ifdef VERBOSE
	cout<<"NSS:map<string,string> lList;"<<endl;
#endif
	map<string,string> lList;

	size_t comma1 = st_data.find(";");
	string data = st_data.substr(0,comma1); //station
	size_t comma2 = st_link.find(";");
	string link = st_link.substr(0,comma2); //link
	st_data=st_data.substr(comma1+1,st_data.size()-comma1-1);
	st_link=st_link.substr(comma2+1,st_link.size()-comma2-1);
#ifdef VERBOSE
	cout<<"NSS:while (st_data.find(\";\"))"<<endl;
	
#endif
	
	std::string delimiter = ";";
	
	while ((comma1 = st_data.find(delimiter)) != std::string::npos) {
    
		comma2 = st_link.find(delimiter);
		data = st_data.substr(0, comma1);
		link = st_link.substr(0, comma2);

		#ifdef VERBOSE
			cout<<"NSS:data,link "<<st_data<<" "<<link<<" "<<comma1<<" "<<comma2<<endl;
			system("pause");
		#endif

		st_data.erase(0, comma1 + delimiter.length());
		st_link.erase(0, comma2 + delimiter.length());

		if (!data.empty())
			lList[data] = link;
	}
	//Make list station : link
	/*while (st_data.find(";")!= std::string::npos)
	{
		comma1 = st_data.find(";");
		data = st_data.substr(0,comma1); //station
		comma2 = st_link.find(";");
		link = st_link.substr(0,comma2); //link

		#ifdef VERBOSE
			cout<<"NSS:data,link "<<st_data<<" "<<link<<" "<<comma1<<" "<<comma2<<endl;
			system("pause");
		#endif
		if ((!comma1)||(!comma2))
			break;
		st_data=st_data.substr(comma1+1,st_data.size()-comma1-1);
		st_link=st_link.substr(comma2+1,st_link.size()-comma2-1);
		lList[data] = link;
	}
	*/
#ifdef VERBOSE
	cout<<"NSS: NS"<<endl;
#endif	
	if (ns)
		delete ns;
	ns = new NearStations();
	ns->href = lList;
	return 0;
}