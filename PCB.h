#ifndef PCB_H_INCLUDED
#define PCB_H_INCLUDED
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
using namespace std;

void scheduler(string pid);
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
priority_queue<PCB> rl;


#endif // PCB_H_INCLUDED
