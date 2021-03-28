#ifndef FILE_LEN_H
#define FILE_LEN_H
#include<bits/stdc++.h>
#include<mysql/mysql.h>
#include<fstream>
#include "sql_handler.h"
namespace mysql_filelen
{
    MYSQL * connect_obj=connect();
    MYSQL_RES * res_set;
    MYSQL_ROW row;
}
using namespace std;
void LengthOfOriginalFile(int fileId,string FileName)
{
    string location="File/"+FileName;
    ifstream fin;
    long filesize=0;
    if(fin)
    {
        fin.open(location);
        long begin=fin.tellg();
        fin.seekg(0,ios::end);
        long end=fin.tellg();
        filesize=(end-begin);
    }
    string query="update userFile set fileSize= "+to_string(filesize+1) +" where userFileId= "+to_string(fileId)+" ;";
    execute_query(mysql_filelen::connect_obj,query);
    fin.close();
}
void LengthOfChunkFile(vector<string> sha256list)
{
    ifstream fin;
    string fileLocation="";
    int filelen;
    for (string i:sha256list)
    {
        cout<<i<<endl;
        fileLocation="chunks/"+i;
        fin.open(fileLocation);
        //cout<<fin;
        if (fin)
        {
            fin.seekg(0,ios::end);
            filelen=fin.tellg();
            cout<<"Length"<<filelen;
            string query="update hashTable set chunkSize= "+to_string(filelen+1)+ " where sha256= '"+i+"' ;";
        }
        else
            cout<<"File not found"<<endl;
        fin.close();
    }
}
#endif
/*
int main()
{
    LengthOfOriginalFile(1,"ff");
}*/
