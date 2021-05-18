#ifndef DELETE_H
#define DELETE_H
#include<bits/stdc++.h>
#include<unordered_map>
#include<vector>
#include "retrieveID.h"
#include "file_opr.h"
namespace mysql_delete
{
    MYSQL * connect_obj=connect();
    MYSQL_RES * res_set;
    MYSQL_ROW row;
}
using namespace std;
unordered_map<string,int> mapCountFile;
unordered_map<string,int> mapCountUser;

void deleteFile(int userId)
{
    cout<<"---------------------------Delete File---------------------------"<<endl;
    cout<<"Files you have:- "<<endl;
    int fileId=showFiles(userId);
    if(fileId!=-1)
    {
        vector<int> shaId=retriveshaID(fileId);
        vector<string> sha256=retrieveSha(shaId);
        string query="delete from userFile where userFileId= "+to_string(fileId)+" ;";
        execute_query(mysql_delete::connect_obj,query);
        query="delete from fileDetails where userFileId= "+to_string(fileId)+" ;";
        execute_query(mysql_delete::connect_obj,query);
        query="select * from shaTable;";
        mysql_delete::res_set=execute_query(mysql_delete::connect_obj,query);
        unsigned int numrows =mysql_num_rows(mysql_delete::res_set);
        if (numrows!=0)
        {
            int i=0;
            mapCountFile.clear();
            while (((mysql_delete::row=mysql_fetch_row(mysql_delete::res_set)) !=NULL))
                mapCountFile.insert(make_pair(mysql_delete::row[i],stoi(mysql_delete::row[i+1])));
        }
        int del_progress=0;
        int length=mapCountFile.size();
        for(string i: sha256)
        {
            if(mapCountFile.find(i)!=mapCountFile.end())
            {
                int count=mapCountFile.find(i)->second;
                //cout<<i<<" "<<count<<endl;
                if(count==1)
                {
                    string query="delete from shaTable where sha256Value= '"+i+"' ;";
                    execute_query(mysql_delete::connect_obj,query);
                    deletefile(i);
                }
                else
                {
                    string query="update shaTable set shacount= "+to_string(--count)+" where sha256Value= '"+i+"' ;";
                    //cout<<query<<endl;
                    execute_query(mysql_delete::connect_obj,query);
                }
                showprogress((float)++del_progress/length);
            }
            else
            {
                cout<<"Nothing found"<<endl;
            }
        }
        query="delete from hashTable where userFileId= "+to_string(fileId)+" ;";
        execute_query(mysql_delete::connect_obj,query); 
        cout<<"\nFile Deleted"<<endl;
    }
}
void deleteUser(int userId)
{
    int count=0;
    cout<<"---------------------------Delete User---------------------------"<<endl;
    vector<int> allFileId=retrieveAllFileId(userId);
    vector<string> allShaValue=retrieveAllShaValue(userId);
    string query="delete from userTable where userId= "+to_string(userId)+" ;";
    execute_query(mysql_delete::connect_obj,query);
    query="delete from userFile where userId= "+to_string(userId)+" ;";
    execute_query(mysql_delete::connect_obj,query);
    query="select * from shaTable";
    mysql_delete::res_set=execute_query(mysql_delete::connect_obj,query);
    unsigned int numrows =mysql_num_rows(mysql_delete::res_set);
    int i=0;
    if (numrows!=0)
    {
        mapCountUser.clear();
        while (((mysql_delete::row=mysql_fetch_row(mysql_delete::res_set)) !=NULL))
        {
            mapCountUser.insert(make_pair(mysql_delete::row[i],stoi(mysql_delete::row[i+1])));
        }
    }
    cout<<"Deleting all the files user has uploaded"<<endl;
    int del_progress=0;
    int length=allShaValue.size();
    for (string s:allShaValue)
    {
        count=mapCountUser.find(s)->second;
        if (count==1)
        {
            query="delete from shaTable where sha256Value= '"+s+"' ;";
            map4count.erase(s);
            execute_query(mysql_delete::connect_obj,query);
            deletefile(s);
        }
        else
        {
            query="update shaTable set shacount = "+to_string(--count)+" where sha256Value = '"+s+"' ;";
            execute_query(mysql_delete::connect_obj,query);
            mapCountUser.insert(make_pair(s,--(mapCountUser.find(s)->second)));
        }
        for(int i:allFileId)
        {
            query="delete from hashTable where userFileId= "+to_string(i)+" ;";
            execute_query(mysql_delete::connect_obj,query);
            query="delete from fileDetails where userFileId= "+to_string(i)+" ;";
            execute_query(mysql_delete::connect_obj,query);
        }
        showprogress((float)++del_progress/length);
    }
    cout<<"\nUser deleted"<<endl;
    exit(0);
}
void deleteVersion(int userId)
{
    cout<<"---------------------------Delete File Version---------------------------"<<endl;
    cout<<"Files you have:"<<endl;
    string fileName=showVerionFiles(userId);
    int fileId=retrieveFileId(userId,fileName);
    cout<<"---------------------------Versions of the File--------------------------"<<endl;
    int versionNo=showFileVersion(fileId);
    int versionId=retrieveVersionId(fileId,versionNo);
    vector<int> shaId=retriveshaID(versionId);
    vector<string> sha256=retrieveSha(shaId);
    string query="delete from userFile where userFileId= "+to_string(versionId)+" ;";
    execute_query(mysql_delete::connect_obj,query);
    query="delete from fileDetails where userFileId= "+to_string(versionId)+" ;";
    execute_query(mysql_delete::connect_obj,query);
    query="select * from shaTable;";
    mysql_delete::res_set=execute_query(mysql_delete::connect_obj,query);
    unsigned int numrows =mysql_num_rows(mysql_delete::res_set);
    int i=0;
    if (numrows!=0)
    {
        while (((mysql_delete::row=mysql_fetch_row(mysql_delete::res_set)) !=NULL))
        {
            mapCountFile.insert(make_pair(mysql_delete::row[i],stoi(mysql_delete::row[i+1])));
        }
    }
    int del_progress=0;
    int length=mapCountFile.size();
    for(string i:sha256)
    {
        if(mapCountFile.find(i)!=mapCountFile.end())
        {
            int count=mapCountFile.find(i)->second;
            if(count==1)
            {
                query="delete from shaTable where sha256Value= '"+i+"' ;";
                execute_query(mysql_delete::connect_obj,query);
            }
            else
            {
                query="update shaTable set shacount= "+to_string(--count) + " where sha256Value= '"+i+"' ;";
                execute_query(mysql_delete::connect_obj,query);
            }
            showprogress((float)++del_progress/length);
            query="delete from hashTable where userFileId= "+to_string(versionId)+" ;";
            execute_query(mysql_delete::connect_obj,query);
        }

    }
    cout<<"Version of the "<<fileName<<" has been deleted"<<endl;
}
#endif
