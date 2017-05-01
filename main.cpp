#include "generic_functions.h"
#include "processInput_functions.h"
int main ()
{
    //create 2 sources

    create(string("p1"),1);
    PCB p1=PCB::get_PCB(string("p1"));
    p1.create(string("p3"),2);
    char *fn="input.txt";
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

   string running=findRunning();
    displayAllMaps();
}
