#ifndef RESOURCECB_H_INCLUDED
#define RESOURCECB_H_INCLUDED
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
typedef map<string,ResourceCB> _ResourceCB_Map;
extern _ResourceCB_Map ResourceCB_Map;
class PCB;

class ResourceCB
{
private:
    string RID;
    const unsigned int initialNumber=1;
public:
    static ResourceCB get_RCB(string RID);
    string getRID() const;
    ResourceCB(){};
    ResourceCB(const string name):RID(name){
    this->available=initialNumber;
    ResourceCB_Map.insert(_ResourceCB_Map::value_type(RID,*this));
    };
    ResourceCB& operator = (ResourceCB const& rhs){
        /*if( &rhs == this) return *this;*/
        RID = rhs.RID;
        available=rhs.available;
        waiting_List.assign(rhs.waiting_List.begin(),rhs.waiting_List.end());
        return *this;
    }
    queue<PCB> waiting_List;
    unsigned int available;
    //RID: 资源的ID
    //available: 空闲单元的数量
    //Waiting_List:block的PCB。
};
string ResourceCB::getRID() const
{
    return this->RID;
}


ResourceCB ResourceCB::get_RCB(string RID){
    _ResourceCB_Map::iterator  my_Itr=ResourceCB_Map.find(RID);
     if(my_Itr==ResourceCB_Map.end())
    {
        //没找到
        ResourceCB rcb;
        return rcb;
    }
    ResourceCB rcb=my_Itr->second;
    return rcb;
}

#endif // RESOURCECB_H_INCLUDED
