#ifndef PCB_H_INCLUDED
#define PCB_H_INCLUDED
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
enum Ptatus_Type
{
ready=1,block=2,running=3
};
class ResourceCB;
class PCB{
private:
    unsigned int priority;
    string PID;
    Ptatus_Type ptatus_Type;

public:
    PCB(){}
    PCB(const string name,const unsigned int Priority):PID(name),priority(Priority){};

    void create(string PID,unsigned int priority);//由它创建子进程
    void setType(const Ptatus_Type ptatus_Type);
    static PCB get_PCB(string PID);
    unsigned int getPriority() const;
    string getPID() const;

    //enum _ptatus_Type{ready=1,running=2,block=3} ;//ptatus_Type = ready;


    // Status_List;
    vector<PCB> creation_tree_Parent;
    vector<PCB> creation_tree_Children;
    vector<ResourceCB> resources;

     Ptatus_Type getPtatus_Type() const;
//
//用法：PCB p1(string("p1"),1);
//p1.setType(running);！！！！！
//•PID（name） cr A 1 ;A=name
//•Resources //: resource which is occupied
//Ptatus_Type: type: ready, block, running….,
//•Creation_tree: Parent/Children与自己链接的父子PCB class
//•Priority: 0, 1, 2 (Init, User, System)//构造函数

};
string PCB::getPID() const
{
    return this->PID;
}
unsigned int PCB::getPriority() const
{
    return this->priority;
}
void PCB::setType(const Ptatus_Type ptatus_Type)
{
    this->ptatus_Type=ptatus_Type;
}
Ptatus_Type PCB::getPtatus_Type() const
{
    return this->ptatus_Type;
}
typedef map<string,PCB> _PCB_Map;
_PCB_Map PCB_Map;

void PCB::create(string PID,unsigned int priority)//隐式PCB *this
{
    PCB pcb(PID,priority);
    pcb.setType(Ptatus_Type::ready);
    //string tmpSelf=this->getPID();
    //PCB self=PCB::get_PCB(tmpSelf);
    pcb.creation_tree_Parent.push_back(*this);
    PCB_Map.insert(_PCB_Map::value_type(PID,pcb));
    this->creation_tree_Children.push_back(pcb);
    PCB temp=*this;
    string tempPID=temp.getPID();
    PCB_Map.erase(tempPID);
    PCB_Map.insert(_PCB_Map::value_type(tempPID,temp));
//    insert(rl,pcb);
//    scheduler();

}


PCB PCB::get_PCB(string PID)
{
    _PCB_Map::iterator  my_Itr=PCB_Map.find(PID);
    if(my_Itr==PCB_Map.end())
    {
        //没找到
        PCB pcb;
        return pcb;
    }
     PCB pcb=my_Itr->second;
     return pcb;
}
#endif // PCB_H_INCLUDED
