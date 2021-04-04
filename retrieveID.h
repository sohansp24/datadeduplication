#ifndef RETRIEVE_H
#define RETRIEVE_H
#include<bits/stdc++.h>
#include<unordered_map>
#include<mysql/mysql.h>
#include<vector>
#include "sql_handler.h"
namespace mysql_retrieve
{
    MYSQL * connect_obj=connect();
    MYSQL_RES * res_set;
    MYSQL_ROW row;
}
using namespace std;
vector<int> retriveshaID(int fileID)
{
    vector<int> arr;
    int i=0;
    string query="select shaId from fileDetails where userFileId= "+to_string(fileID)+";";
    mysql_retrieve::res_set=execute_query(mysql_retrieve::connect_obj,query);
    unsigned int numrows =mysql_num_rows(mysql_retrieve::res_set);
    if (numrows!=0)
    {
        while (((mysql_retrieve::row=mysql_fetch_row(mysql_retrieve::res_set)) !=NULL))
        {
            arr.push_back(stoi(mysql_retrieve::row[i]));
        }
    }
    return arr;
}

int retrieveFileId(int userId,string fileName)
{
    int userFileID=0;
    int i=0;
    string query="select userFileId from userFile where userId= "+to_string(userId)+" and fileName= '"+fileName+"' ;";
    mysql_retrieve::res_set=execute_query(mysql_retrieve::connect_obj,query);
    unsigned int numrows =mysql_num_rows(mysql_retrieve::res_set);
    if (numrows!=0)
    {
        while (((mysql_retrieve::row=mysql_fetch_row(mysql_retrieve::res_set)) !=NULL))
        {
            userFileID=stoi(mysql_retrieve::row[i]);
        }
    }
    return userFileID;
}

vector<string> retrieveSha(vector<int> shaid)
{
    vector<string> arrSha;
    for(int i:shaid)
    {
        string query="select sha256 from hashTable where shaId= "+to_string(i)+";";
        mysql_retrieve::res_set=execute_query(mysql_retrieve::connect_obj,query);
        int j=0;
        unsigned int numrows =mysql_num_rows(mysql_retrieve::res_set);
        if (numrows!=0)
        {
            while (((mysql_retrieve::row=mysql_fetch_row(mysql_retrieve::res_set)) !=NULL))
            {
                arrSha.push_back(mysql_retrieve::row[j]);
            }
        }
    }
    return arrSha;
}

int showFiles(int UserId)
{
    string query="select userFileId,fileName from userFile where userId= "+to_string(UserId)+" ;";
    mysql_retrieve::res_set=execute_query(mysql_retrieve::connect_obj,query);
    unsigned int numrows =mysql_num_rows(mysql_retrieve::res_set);
    int i=0;
    cout<<"FileID\tFileName"<<endl;
    if (numrows!=0)
    {
        while (((mysql_retrieve::row=mysql_fetch_row(mysql_retrieve::res_set)) !=NULL))
        {
            cout<<mysql_retrieve::row[i]<<"\t"<<mysql_retrieve::row[i+1]<<endl;
        }
        cout<<"Enter FileID: ";
        int fileid;
        cin>>fileid;
        cout<<endl;
        return fileid;
    }
    else
        cout<<"You don't have any files uploaded...\nTry uploading a file and then come back here..."<<endl;
    return -1;
}

string showFilesName(int fileId)
{
    string query="select fileName from userFile where userFileId= "+to_string(fileId)+" ;";
    mysql_retrieve::res_set=execute_query(mysql_retrieve::connect_obj,query);
    string fileName;
    int i=0;
    unsigned int numrows =mysql_num_rows(mysql_retrieve::res_set);
    if (numrows!=0)
    {
        while (((mysql_retrieve::row=mysql_fetch_row(mysql_retrieve::res_set)) !=NULL))
        {
            fileName=mysql_retrieve::row[i];
        }
    }
    return fileName;
}

vector<int> retrieveAllFileId(int userId)
{
    string query="select userFileId from userFile where userId= "+to_string(userId)+" ;";
    vector<int> allFileId;
    int i=0;
    mysql_retrieve::res_set=execute_query(mysql_retrieve::connect_obj,query);
    unsigned int numrows =mysql_num_rows(mysql_retrieve::res_set);
    if (numrows!=0)
    {
        while (((mysql_retrieve::row=mysql_fetch_row(mysql_retrieve::res_set)) !=NULL))
        {
            allFileId.push_back(stoi(mysql_retrieve::row[i]));
        }
    }
    return allFileId;
}

vector<string> retrieveAllShaValue(int userId)
{
    vector<string> allShaValues;
    vector<int> AllFileID=retrieveAllFileId(userId);
    for(int j: AllFileID)
    {
        cout<<"FILE IDs\t"<<j<<endl;
        int i=0;
        string query="select sha256 from hashTable where userFileId= "+to_string(j)+" ;";
        mysql_retrieve::res_set=execute_query(mysql_retrieve::connect_obj,query);
        unsigned int numrows =mysql_num_rows(mysql_retrieve::res_set);
        if (numrows!=0)
        {
            while (((mysql_retrieve::row=mysql_fetch_row(mysql_retrieve::res_set)) !=NULL))
            {
                allShaValues.push_back(mysql_retrieve::row[i]);
            }
        }
    }
    return allShaValues;
}

int retrieveVersionNo(int fileId)
{
    string query="select MAX(versionNo) from userFile where versionOf= "+to_string(fileId)+" ;";
    mysql_retrieve::res_set=execute_query(mysql_retrieve::connect_obj,query);
    int versionNo;
    int i=0;
    unsigned int numrows =mysql_num_rows(mysql_retrieve::res_set);
    if (numrows!=0)
    {
        while (((mysql_retrieve::row=mysql_fetch_row(mysql_retrieve::res_set)) !=NULL))
        {
            versionNo=stoi(mysql_retrieve::row[i]);
        }
    }
    return versionNo;
}
int retrieveVersionId(int fileId,int versionNo)
{
    string query="select userFileId from userFile where versionOf= "+to_string(fileId)+" and versionNo= "+to_string(versionNo)+" ;";
    mysql_retrieve::res_set=execute_query(mysql_retrieve::connect_obj,query);
    int versionId;
    int i=0;
    unsigned int numrows =mysql_num_rows(mysql_retrieve::res_set);
    if (numrows!=0)
    {
        while (((mysql_retrieve::row=mysql_fetch_row(mysql_retrieve::res_set)) !=NULL))
        {
            versionId=stoi(mysql_retrieve::row[i]);
        }
    }
    return versionId;
}

int showFileVersion(int fileId)
{
    string query="select fileName,versionNo from userFile where versionOf= "+to_string(fileId)+" ;";
    mysql_retrieve::res_set=execute_query(mysql_retrieve::connect_obj,query);
    unsigned int numrows =mysql_num_rows(mysql_retrieve::res_set);
    cout<<"Version No.\tFile Name"<<endl;
    int i=0;
    if (numrows!=0)
    {
        while (((mysql_retrieve::row=mysql_fetch_row(mysql_retrieve::res_set)) !=NULL))
        {
            cout<<mysql_retrieve::row[i]<<"\t"<<mysql_retrieve::row[i+1];
        }
    }
    int temp;
    cout<<"Enter the Version number to delete: ";
    cin>>temp;
    cout<<endl;
    return temp;
}

string showVerionFiles(int userId)
{
    string query="select fileName from userFile where userId= '"+to_string(userId)+ "' and versionNo= 1 ";
    mysql_retrieve::res_set=execute_query(mysql_retrieve::connect_obj,query);
    unsigned int numrows =mysql_num_rows(mysql_retrieve::res_set);
    cout<<"File names are: "<<endl;
    int i=0;
    if (numrows!=0)
    {
        while (((mysql_retrieve::row=mysql_fetch_row(mysql_retrieve::res_set)) !=NULL))
        {
            cout<<mysql_retrieve::row[i]<<endl;
        }
    }
    cout<<"Enter name of the file: ";
    string filename;
    cin>>filename;
    cout<<endl;
    return filename;
}

int getVersionNo(int fileId)
{
    int i=0;
    int versionno=0;
    string query="select versionNo from userFile where userFileId= "+to_string(fileId)+" ;";
    mysql_retrieve::res_set=execute_query(mysql_retrieve::connect_obj,query);
    unsigned int numrows =mysql_num_rows(mysql_retrieve::res_set);
    if (numrows!=0)
    {
        while (((mysql_retrieve::row=mysql_fetch_row(mysql_retrieve::res_set)) !=NULL))
        {
            versionno=stoi(mysql_retrieve::row[i]);
        }
    }
    return versionno;
}

vector<string> retrieveShaValue(int fileId)
{
    int i=0;
    vector<string> arr;
    string query="select sha256 from hashTable where userFileId= "+to_string(fileId)+" ;";
    mysql_retrieve::res_set=execute_query(mysql_retrieve::connect_obj,query);
    unsigned int numrows =mysql_num_rows(mysql_retrieve::res_set);
    if (numrows!=0)
    {
        while (((mysql_retrieve::row=mysql_fetch_row(mysql_retrieve::res_set)) !=NULL))
        {
            arr.push_back(mysql_retrieve::row[i]);
        }
    }
    return arr;
}
#endif
/*
int main()
{
    retriveshaID(1);
}
*/
