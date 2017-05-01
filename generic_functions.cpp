
#ifndef GENERIC_FUNCTIONS_H_INCLUDED
#define GENERIC_FUNCTIONS_H_INCLUDED
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "generic_functions.h"
#include "RL.h"
//#define GENERIC_FUNCTIONS_H
using namespace std;
#include "PCB.h"
extern map<string,PCB> PCB_Map;
extern map<string,ResourceCB> ResourceCB_Map;
void displayAllMaps(){
    map<string,PCB>::const_iterator itor=PCB_Map.begin();
    while(itor!=PCB_Map.end())
    {
        cout<<"PCB name:"<<itor->first<<endl;
        //cout<<"PCB name:"<<itor->second<<endl;
        ++itor;
    }
    map<string,ResourceCB>::const_iterator itor2=ResourceCB_Map.begin();
    while(itor2!=ResourceCB_Map.end())
    {
        cout<<"ResourceCB name:"<<itor2->first<<endl;
        ++itor2;
    }
}
void create(string PID,unsigned int priority)
{
    PCB pcb(PID,priority);

//    PCB runningProcess=findRunning();
//
//    if(running==false)
    pcb.setType(ready);
 //   pcb.creation_tree_Parent.push_back(runningProcess);
//    runningProcess.creation_tree_Children.push_back()
//    insert(rl,pcb);
//    scheduler();
    //PCB_Map.insert(std::make_pair(pcb.getPID(),pcb));
}
#ifdef GENERIC_FUNCTIONS_H
PCB findRunning(){


}


void destroy(string PID)
{
    PCB *pcb=get_PCB(PID);
    kill_Tree(*pcb);
    scheduler();

}
void kill_Tree(PCB &p)
{
    for (vector<PCB>::iterator iter=p.creation_tree_Children.end();iter!=p.creation_tree_Children.begin();iter--)
    {
        kill_Tree(*iter);
        *iter=(*iter)+1;
    }
    for (vector<RCB>::iterator iter=p.resources.end();iter!=p.resources.begin();iter--)
    {
        release(*iter.getRID());
    }
}
void request(string RID){
    PCB runningProcess;
    ResourceCB r=get_RCB(RID);
    if(r.available!=0)
    {
        --r.available;
        insert(runningProcess.Resources,r);
    }
    else{
        runningProcess.setType(block);
        remove(rl,runningProcess);
        r.waiting_List.push_back(runningProcess);//insert(r.waiting_List,runningProcess);
        scheduler();
    }

}
void release(string RID)//释放单个资源。
{
     PCB runningProcess;
    ResourceCB r=get_RCB(RID);
    remove(runningProcess.Resources, r);//将r从进程self占用的资源中移走
    if (r.waiting_List == NULL) //没有进程在等待资源r
    {
    r.available++;
    }
    else
    {
    PCB q;
     r.waiting_List.pop(q);//q为waiting_list中第一个阻塞进程
    q.setType(ready);

    insert(q.resources, r);
    insert(rl, q); //q插入就绪队列中相应优先级队列的末尾
    scheduler();
    }
}
#endif // GENERIC_FUNCTIONS_H
//PCB get_PCB(string PID){
//    vector<string,PCB>::iterator  my_Itr=;PCB_Map.find(PID);
//    PCB pcb=my_Itr->second;
//    return pcb;
//}

#endif // GENERIC_FUNCTIONS_H_INCLUDED
