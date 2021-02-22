#ifndef DELETE_H
#define DELETE_H
#include<bits/stdc++.h>
#include<unordered_map>
#include<vector>
namespace mysql_delete
{
    MYSQL * connect_obj=connect();
    MYSQL_RES * res_set;
    MYSQL_ROW row;
}
using namespace std;
#include "retrieveID.h"
#include "file_opr.h"
unordered_map<string,int> mapCountFile;
unordered_map<string,int> mapCountUser;

void deleteFile(int userId)
{
    cout<<"---------------------------Delete File---------------------------"<<endl;
    cout<<"Files you have:- "<<endl;
    int fileId=showFiles(userId);
    vector<int> shaId=retriveshaID(fileId);
    vector<string> sha256=retrieveSha(shaId);
    string query="delete from userFile where userFileId= "+fileId+" ;";
    execute_query(mysql_delete::connect_obj,query);
    query="delete from fileDetails where userFileId= "+fileId+" ;";
    execute_query(mysql_delete::connect_obj,query);
    query="select * from shaTable;";
    mysql_delete::res_set=execute_query(mysql_delete::connect_obj,query);
    unsigned int numrows =mysql_num_rows(mysql_delete::res_set);
    if (numrows!=0)
    {
        int i=0;
        while (((mysql_delete::row=mysql_fetch_row(mysql_delete::res_set)) !=NULL))
        {   
               mapCountFile.insert(make_pair(stoi(row[i]),row[i+1]));
        }
    }
    for(string i: sha256)
    {
        if(mapCountFile.find(i)!=mapCountFile.end())
        {
            int count=mapCountFile.find(i)->second;
            if(count<=1)
            {
                string query="delete from shaTable where sha256Value= '"+i+"' ;";
                execute_query(mysql_delete::connect_obj,query);
                deletefile(i);
            }
            else
            {
                count--;
                string query="update shaTable set shacount= "+to_string(count)+" where sha256Value= '"+i+"' ;";
                execute_query(mysql_delete::connect_obj,query);
            }
        }
        else
        {
            cout<<"Nothing found"<<end;
        }
    }
    string query="delete from hashTable where userFileId= "+to_string(fileId)+" ;";
    execute_query(mysql_delete::connect_obj,query); 
}
void deleteUser(int userId)
{
    int count=0;
    cout<<"---------------------------Delete User---------------------------"<<endl;
    vector<int> allFileId=retrieveAllFileId(userId);
    vector<string> allShaValue=retrieveAllShaValue(userId);
    string user_query="delete from userTable where userId= "+to_string(userId)+" ;";
    


}
#endif