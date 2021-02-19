#ifndef UPLOAD_FILE_H
#define UPLOAD_FILE_H
#include<bits/stdc++.h>
#include<unordered_map>
#include<mysql/mysql.h>
#include "sql_handler.h"
#include "file_opr.h"
#include "updatefilelength.h"
#include "retrieveID.h"
#include "createChunk.h"
namespace mysql_uploadFile
{
    MYSQL * connect_obj=connect();
    MYSQL_RES * res_set;
    MYSQL_ROW row;
}
using namespace std;
string fileLocation;
string fileName;
int retrieveFileId(string fileName)
{
    int fileId=0;
    string query="select userFileId from userFile where fileName= "+fileName+" ;";
    mysql_uploadFile::res_set=execute_query(mysql_uploadFile::connect_obj,query);
    unsigned int numrows =mysql_num_rows(mysql_uploadFile::res_set);
    int i=0;
    if (numrows!=0)
    {
        while (((mysql_uploadFile::row=mysql_fetch_row(mysql_uploadFile::res_set)) !=NULL))
        {
            fileId=stoi(mysql_uploadFile::row[i]);
        }
    }
    return fileId;
}
vector<int> retrieveShaId(int fileId)
{
    vector<int> arr;
    string query="select shaId from hashTable where userFileId= "+to_string(fileId)+" ;";
    mysql_uploadFile::res_set=execute_query(mysql_uploadFile::connect_obj,query);
    unsigned int numrows =mysql_num_rows(mysql_uploadFile::res_set);
    int i=0;
    if (numrows!=0)
    {
        while (((mysql_uploadFile::row=mysql_fetch_row(mysql_uploadFile::res_set)) !=NULL))
        {
            arr.push_back(stoi(mysql_uploadFile::row[i]));
        }
    }
    return arr;
}

void upload(int fileId,string fileName)
{
    int n=1;
    for(int i=0;i<n;i++)
    {
        fileLocation="file/"+fileName;
        createChunk(fileId,fileLocation);
        cout<<"--------------------------FILE "+to_string(i)+"--------------------------------------------"<<endl;
    }
    cout<<"Thank You: Files uploaded"<<endl;
}
void insertIntoFileTable(int FileId,string fileName )
{
    string query;
    vector<int> sha256Id=retriveshaID(FileId);
    for (int i: sha256Id)
    {
        query="insert into fileDetails values( "+to_string(FileId)+" , "+to_string(i)+" );";
        execute_query(mysql_uploadFile::connect_obj,query);
    }
}
void insertVersionFileTable(int fileId)
{
    string query;
    vector<int> sha256Id=retriveshaID(fileId);
    for(int i: sha256Id)
    {
        query="insert into fileDetails values( "+to_string(fileId)+" , "+to_string(i)+" ) ;";
        execute_query(mysql_uploadFile::connect_obj,query);
    }
}

void insertIntoUserFile(int userId)
{
    
    cout<<"Enter the name of the file:- ";
    cin>>fileName;
    cout<<endl;
    string query="insert into userFile (userId,fileName,versionNo) values( "+to_string(userId)+" , "+fileName+" , "+to_string(1)+" );";
    execute_query(mysql_uploadFile::connect_obj,query);
    int fileID=retrieveFileId(fileName);
    query="update userFile set versionOf= "+to_string(fileID)+" where userFileId= "+to_string(fileID)+" ;";
    execute_query(mysql_uploadFile::connect_obj,query);
    LengthOfOriginalFile(fileID,fileName);
    upload(fileID,fileName);
    insertIntoFileTable(fileID,fileName);
    vector<string> shavalue=retrieveShaValue(fileID);
    LengthOfChunkFile(shavalue);
}
#endif
/*
int main()
{
    insertIntoUserFile(1);
}*/
