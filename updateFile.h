#ifndef UPDATE_FILE_H
#define UPDATE_FILE_H
#include<bits/stdc++.h>
#include<ctime>
#include<vector>
#include "sql_handler.h"
#include "createChunk.h"
#include "updatefilelength.h"
#include "uploadFile.h"
#include "retrieveID.h"
namespace mysql_updatefile
{
    MYSQL * connect_obj=connect();
    MYSQL_RES * res_set;
    MYSQL_ROW row;
}
using namespace std;

bool checkFileName(int userId,string filename)
{
    string query="select * from userFile where userId= "+to_string(userId)+" and fileName= '"+filename+"' ;";
    mysql_updatefile::res_set=execute_query(mysql_updatefile::connect_obj,query);
    unsigned int numrows = mysql_num_rows(mysql_updatefile::res_set);
    if (numrows!=0)
        return true;
    else
        return false;
}

void update(int userId)
{
    int versionCount=0;
    cout<<"Enter name of the file : ";
    string filename;
    cin>>filename;
    cout<<endl;
    int fileId=retrieveFileId(userId,filename);
    int versionNo=retrieveVersionNo(fileId);
    string newFileLocation="File/"+filename;
    if(checkFileName(userId,filename))
    {
        time_t now=time(0);
        tm *ltm=localtime(&now);
        string current_datentime=to_string(ltm->tm_mday)+"-"+to_string(1+ltm->tm_mon) +"-"+to_string(1900+ltm->tm_year)+"|"+to_string(5+ltm->tm_hour)+":"+to_string(30+ ltm->tm_hour)+":"+to_string(ltm->tm_sec);
        vector<string> tokens;
        char *token = strtok((char*)filename.c_str(), "."); 
        tokens.push_back((string)token);
        cout<<token<<"  ";
        while (token != NULL) 
        { 
            tokens.push_back((string)token);
            token = strtok(NULL, "."); 
            //cout<<token;
        }  
        /*char* intermediate;
        char name[filename.length()];
        strcpy(name,filename.c_str());
        strtok(name,"//");
        while (intermediate != NULL)
        {
            tokens.add(intermediate);
            intermediate = strtok (NULL, "//");
        }*/
        string newFileName=tokens.at(0)+"_"+current_datentime+"."+tokens.at(1);
        cout<<tokens.at(0)<<"\t"<<tokens.at(1)<<"\t"<<tokens.size();
        versionCount=versionNo+1;
        string query="insert into userFile (userId,fileName,versionNo,versionOf) values ("+to_string(userId)+",'"+newFileName+"',"+to_string(versionCount)+","+to_string(fileId)+");";
        execute_query(mysql_updatefile::connect_obj,query);
        int versionId=retrieveVersionId(fileId,versionCount);
        createChunk(versionId,newFileLocation);
        cout<<versionId<<endl;
        insertVersionFileTable(versionId);
        LengthOfOriginalFile(versionId,filename);
        cout<<versionId<<endl;
        vector <string> shaValue=retrieveShaValue(versionId);
        LengthOfChunkFile(shaValue);
    }
    else
        cout<<"File not found"<<endl;
}
/*
int main()
{
    update(1);
    return 0;
}*/
#endif