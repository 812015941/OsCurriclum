#ifndef PROCESSINPUT_FUNCTIONS_H_INCLUDED
#define PROCESSINPUT_FUNCTIONS_H_INCLUDED
#include "generic_functions.h"
string readFileIntoString(char * filename);
void processInstrctions(string command);
//读取文件操作并且调用指令相关
string readFileIntoString(char * filename)
{
    ifstream ifile(filename);
    int countLines=0;
    char tmpLine[100];
    string strResult;
     while(!ifile.eof())
    {
        ifile.getline(tmpLine,100);
        ++countLines;
        string strLine(tmpLine);
        cout<<strLine<<endl;
        processInstrctions(strLine);//进行操作！
        strResult+=strLine+string("\n");
    }
    ifile.clear();
    ifile.close();
    return strResult;
}
void processInstrctions(string command)
{
    //先拆分指令。
    string strTarget=" ";
    const int targetLocTO=command.find("to");//对于init=4,cr=2,to=-1 req=3 de=2
     if(targetLocTO==0)
    {
        //cout<<"command:to!"<<endl;
        return;
    }
    const int targetLocINIT=command.find("init");
      if(targetLocINIT==0)
    {
        ResourceCB resourceCB1(string("r1"));
        ResourceCB resourceCB2(string("r2"));
        create(string("p0"),0);
        return;
    }
    const int targetLocCR=command.find("cr");
    if(targetLocCR==0)
    {
        string PID="cr ";
        const int targetLocPID=command.find_first_not_of(PID);
        const int targetLocPID_End=command.find(string(" "),targetLocPID);
        PID="";
        for(int i=targetLocPID;i<targetLocPID_End;i++)
            PID=PID+command.at(i);
        int priority;
        const int targetLocpPriority=targetLocPID_End+1;
        string tempPriority;
        for(unsigned int i=targetLocpPriority;i<command.size();i++){
            tempPriority=tempPriority+command.at(i);}
        while(tempPriority.find(" ")!=-1){//神来之笔
            tempPriority.erase(tempPriority.size()-1);}
        priority=atoi(tempPriority.c_str());
        create(PID,priority);
        return;
    }
    const int targetLocREQ=command.find("req");
    if(targetLocREQ==0)
    {
        string ResourceID="q";
        int targetLocRID=command.find(ResourceID);///////??????
        ResourceID="";
        for(int i=targetLocRID+2;i<command.size();i++)
            ResourceID=ResourceID+command.at(i);
        while(ResourceID.find(" ")!=-1){//神来之笔
            ResourceID.erase(ResourceID.size()-1);}
        cout<<ResourceID<<"///"<<endl;
        request(ResourceID);
    }
    const int targetLocDE=command.find("de");//删除资源
     if(targetLocDE==0)
    {
        string PID="de ";
        const int targetLocPID=command.find_first_not_of(PID);
        PID="";
        for(int i=targetLocPID;i<command.size();i++)
            PID=PID+command.at(i);
        while(PID.find(" ")!=-1){//神来之笔
            PID.erase(PID.size()-1);}
        destroy(PID);
    }

}
#endif // PROCESSINPUT_FUNCTIONS_H_INCLUDED
