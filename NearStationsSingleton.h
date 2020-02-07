#include "setup.h"

using namespace std;

#ifndef NEARSTATIONSSINGLETON_H
#define NEARSTATIONSSINGLETON_H

class NearStations
{
public:
	NearStations(){}
	map<string,string> href; //Name - link
};

class NearStationsSingleton
{
  private:
    static NearStationsSingleton * p_instance;
    // Конструкторы и оператор присваивания недоступны клиентам
    NearStationsSingleton() {ns=0;}
    NearStationsSingleton( const NearStationsSingleton& );  
    NearStationsSingleton& operator=( NearStationsSingleton& );
  public:
	void setStationIndex(string index);
	string makeAHrefRow(size_t i);
	int loadBaseFiles();
	int checkStationCat(string index);
	NearStations* ns; //Name of our station - Names/Links.
    static NearStationsSingleton * getInstance() {
        if(!p_instance)           
            p_instance = new NearStationsSingleton();
        return p_instance;
    }
	string mStationIndex;
};

#endif