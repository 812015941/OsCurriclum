#ifndef GENERIC_FUNCTIONS_H_INCLUDED
#define GENERIC_FUNCTIONS_H_INCLUDED

#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <queue>
#include "PCB.h"
#include "ResourceCB.h"

extern _PCB_Map PCB_Map;
_ResourceCB_Map ResourceCB_Map;
using namespace std;

void displayParentsAndChildren(string PID);
void displayAllMaps();
void create(string PID,unsigned int priority);
string findRunning();
void destroy(string PID);
void request(string RID);
void release(string RID);//释放resourceCB中的资源，然后更新runningPCB与resourceCB到两个map
void remove(ResourceCB resourceCB,PCB runningPCB);//单纯从pcb中释放resources资源，然后更新pcb_map
void insertBlock(ResourceCB resourceCB,PCB pcb);
//void insert(RL rl, PCB p);//wb
void time_out();//wb
void scheduler(string pid);//wb
void preempt(PCB p);
void kill_Tree(string PID);
//创建(create)： (none) -> ready
//撤销(destroy)： running/ready/blocked -> (none)
//请求资源(Request): running -> blocked (当资源没有时，进程阻塞)
//释放资源(Release): blocked -> ready (因申请资源而阻塞的进程被唤醒)
//时钟中断(Time_out): running -> ready
//调度：ready -> running  / running ->ready

void displayParentsAndChildren(string PID){
    PCB pcb=PCB::get_PCB(PID);
    vector<PCB>::const_iterator itorP=pcb.creation_tree_Parent.begin();
    cout<<"----------display "<<pcb.getPID()<<":parents----------"<<endl;
    vector<PCB>::size_type size_tp=0;
    while(itorP!=pcb.creation_tree_Parent.end())
    {
        ++size_tp;
        cout<<"Parents:"<<size_tp<<" name:"<<itorP->getPID()<<endl;
        ++itorP;
    }
    itorP=pcb.creation_tree_Children.begin();
    cout<<"----------display "<<pcb.getPID()<<":children----------"<<endl;
    size_tp=0;
    while(itorP!=pcb.creation_tree_Children.end())
    {
        ++size_tp;
        cout<<"Children:"<<size_tp<<" name:"<<itorP->getPID()<<endl;
        ++itorP;
    }
}

void displayAllMaps(){
    cout<<"----------display PCB ----------"<<endl;
    _PCB_Map::const_iterator itor=PCB_Map.begin();
    while(itor!=PCB_Map.end())
    {
        cout<<"PCB name:"<<itor->first<<" priority:"<<itor->second.getPriority()<<" Ptatus_Type:"<<itor->second.getPtatus_Type()
        <<" Resources number:"<<itor->second.resources.size()<<endl;
        //cout<<"PCB name:"<<itor->second<<endl;
        ++itor;
    }
    cout<<"----------display ResourceCB ----------"<<endl;
    typedef map<string,ResourceCB> _ResourceCB_Map;
    _ResourceCB_Map::const_iterator itor2=ResourceCB_Map.begin();
    while(itor2!=ResourceCB_Map.end())
    {
        cout<<"ResourceCB name:"<<itor2->first<<" available:"<<itor2->second.available<<endl;
        ++itor2;
    }
}
void create(string PID,unsigned int priority)
{
    PCB pcb(PID,priority);

    PID=findRunning();

    if(PID.empty())
        pcb.setType(running);
    else pcb.setType(ready);
    PCB_Map.insert(_PCB_Map::value_type(pcb.getPID(),pcb));
//    insert(rl,pcb);
    rl.push(pcb);
    //cout << "[debug] Create: rlSize: " << rl.size() << endl;
    //cout << "[debug] create: rlTop: " << rl.top().getPID() << endl;
//
    scheduler(PID);

}
void request(string RID){
    const int checkRID1=RID.find("r1");
    const int checkRID2=RID.find("r2");
    if(checkRID1!=0&&checkRID2!=0)
    {
        cout<<"Request error! Please request r1 or r2."<<endl;
        return;
    }
    string running=findRunning();
    PCB runningPCB=PCB::get_PCB(running);
    ResourceCB r=ResourceCB::get_RCB(RID);
    if(r.available!=0)//有资源
    {
        --r.available;
        runningPCB.resources.push_back(r);
        PCB_Map.erase(running);
        PCB_Map.insert(_PCB_Map::value_type(running,runningPCB));
        ResourceCB_Map.erase(r.getRID());
        ResourceCB_Map.insert(_ResourceCB_Map::value_type(r.getRID(),r));
    }
    else{
        //remove(rl,runningPCB);
        insertBlock(r,runningPCB);//insert(r.waiting_List,runningProcess);
         //
        scheduler(running);
    }

}
void insertBlock(ResourceCB resourceCB,PCB pcb){
        pcb.setType(block);
        cout<<"Debug:insertBlock. "<<pcb.getPID()<<endl;
        //remove(rl,runningPCB);
        resourceCB.waiting_List.push_back(pcb);//insert(r.waiting_List,runningProcess);
        PCB_Map.erase(pcb.getPID());
        PCB_Map.insert(_PCB_Map::value_type(pcb.getPID(),pcb));
        ResourceCB_Map.erase(resourceCB.getRID());
        ResourceCB_Map.insert(_ResourceCB_Map::value_type(resourceCB.getRID(),resourceCB));


}
string findRunning()
{
    _PCB_Map::const_iterator itor=PCB_Map.begin();
    while(itor!=PCB_Map.end())
    {
        PCB temp=itor->second;
        //cout << "[debug] findRunning: pid: " << temp.getPID() << endl;
        //cout << "[debug] findRunning: status: " << temp.getPtatus_Type() << endl;
        if(temp.getPtatus_Type()==running){
                //cout<<"find running process:"<<temp.getPID()<<endl;
                return temp.getPID();
        }
        else ++itor;

    }
    return "";
}
void kill_Tree(string PID)
{
    PCB p=PCB::get_PCB(PID);
    vector<ResourceCB>::iterator iterR=p.resources.begin();
    while (iterR!=p.resources.end())
    {
        cout<<"Debug:kill_Tree. "<<endl;
        release(iterR->getRID());
        iterR++;
    }
    vector<PCB>::iterator iter=p.creation_tree_Children.begin();
    while (iter!=p.creation_tree_Children.end())
    {

        kill_Tree(iter->getPID());
        PCB_Map.erase(iter->getPID());
        iter++;
    }
    PCB_Map.erase(PID);//消灭自己
}
void destroy(string PID)//==Kill_Tree
{
    kill_Tree(PID);
    //
    scheduler(PID);
}
void release(string RID){
    ResourceCB resourceCB=ResourceCB::get_RCB(RID);
    string running=findRunning();
    PCB runningPCB=PCB::get_PCB(running);
    remove(resourceCB,runningPCB);//处理了runningPCB
    if(resourceCB.waiting_List.empty())
    {
        resourceCB.available++;
    }else
    {

    }
    ////////////////////////////////////////
    cout<<"Debug:release. "<<endl;
    displayAllMaps();
    resourceCB.available++;
    if(resourceCB.available>1)
    {
        cout<<"Error! Resouce"<<endl;
        return ;
    }
    //resourceCB.waiting_List
}
void remove(ResourceCB resourceCB,PCB runningPCB)
{
    vector<ResourceCB>::iterator iter=runningPCB.resources.begin();
     while (iter!=runningPCB.resources.end())
    {
        string targetRID=resourceCB.getRID();
        string srcRID=iter->getRID();
        const int targetLocCR=srcRID.find(targetRID);
        if(targetLocCR==0)//r1=r1
        {
           iter=runningPCB.resources.erase(iter);
           //iter=runningPCB.resources.erase(iter);//删除元素，返回值指向已删除元素的下一个位
            PCB_Map.erase(runningPCB.getPID());
            PCB_Map.insert(_PCB_Map::value_type(runningPCB.getPID(),runningPCB));
            return;
        }
        iter++;
    }
    //更新PCB

}

void scheduler(string pid)
{
  PCB p = rl.top();
  cout << "[debug] scheduler: topPid: " << p.getPID() << endl;
  PCB runP = PCB::get_PCB(pid);
  if (pid.empty() || (runP.getPtatus_Type() != running))
    preempt(p);
  else if (runP.getPriority() < p.getPriority())
    {
      runP.setType(ready);
      PCB_Map.erase(pid);
      PCB_Map.insert(_PCB_Map::value_type(pid, runP));
      rl.push(runP);
      preempt(p);
    }

}

void preempt(PCB p)
{
  p.setType(running);
  PCB_Map.erase(p.getPID());
  PCB_Map.insert(_PCB_Map::value_type(p.getPID(), p));
  rl.pop();
  cout << "[debug] preempt: rlTop: " << rl.top().getPID() << endl;
}

void timeout()
{
  string pid = findRunning();
  PCB runP = PCB::get_PCB(pid);
  runP.setType(ready);
  PCB_Map.erase(pid);
  PCB_Map.insert(_PCB_Map::value_type(pid, runP));
  rl.push(runP);
  cout << "[debug] timeout: pid: " << runP.getPID() << endl;
  //cout << "[debug] timeout: rlSize: " << rl.size() << endl;
  scheduler(pid);
}

#endif // GENERIC_FUNCTIONS_H_INCLUDED
