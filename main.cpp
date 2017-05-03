#include "generic_functions.h"
#include "processInput_functions.h"
#define wcb
#include <queue>
int main ()
{
    //create 2 sourcesuck
  #ifndef wcb
    cout<<"fuck"<<endl;
    create(string("p1"),1);
    PCB p1 = PCB::get_PCB(string("p1"));
    p1.create(string("p3"),2);
    char *fn = "input.txt";
    string str;
    str=readFileIntoString(fn);
    //ofstream fout;//out put!
    //fout.open("test_surveillance-output2.txt");
    //fout.clear();
    //fout.close();

    request(string("r1"));
    request(string("r2"));

    //p1.create(string("p2"),1);
//    p1.setType(running);
//    cout<<" "<<p1.getPID()<<r1.getRID()<<endl;
//    cout<<" "<<p1.getPtatus_Type()<<endl;
   //havefun();

   string running = findRunning();
    displayAllMaps();
    #endif
    #ifdef wcb
    //    priority_queue<PCB> pq;
    create(string("p1"), 1);
    PCB p1 = PCB::get_PCB(string("p1"));
    p1.create(string("p2"), 1);
    //create(string("p2"), 1);
    PCB p2 = PCB::get_PCB(string("p2"));
    p1.create(string("p3"), 1);
    //create(string("p4"), 1);
    PCB p3 = PCB::get_PCB(string("p3"));

        //pq.push(p1);
        //pq.push(p2);
    //    pq.push(p3);
      //  pq.push(p4);
    int i = 4;
    while (i > 0)
    {
      //PCB p = rl.top();
        PCB p = PCB::get_PCB(findRunning());
      cout << "pid: " << p.getPID() << endl;
      cout << "priority: " << p.getPriority() << endl;
      cout << "status: " << p.getPtatus_Type() << endl;
      timeout();
      i--;
      cout << "pq size: " << rl.size() << endl;
      cout << "------------------------------" << endl;

      //rl.pop();
    }


    #endif

}
