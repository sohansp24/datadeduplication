#ifndef DOWNLOAD_FILE_H
#define DOWNLOAD_FILE_H
#include<bits/stdc++.h>
#include "file_opr.h"
#include "retrieveID.h"
void DownloadFile(int userId)
{
    cout<<"---------------------------Download File---------------------------"<<endl;
    cout<<"Files you have:- "<<endl;
    int fileId=showFiles(userId);
    if(fileId!=-1)
    {
        string filename=showFilesName(fileId);
        vector <int> shaId=retriveshaID(fileId);
        vector<string> sha256=retrieveSha(shaId);
        vector<string> changename;
        char *token = strtok((char*)filename.c_str(), "[_.]"); 
        changename.push_back((string)token);
        while (token != NULL) 
        { 
            changename.push_back((string)token);
            token = strtok(NULL, "-"); 
        }  
        int len=changename.size()-1;
        filename=changename.at(0)+"(v"+to_string(getVersionNo(fileId))+")."+changename.at(len);
        createOriginal(sha256,filename);
        cout<<"File downloaded sucessfully.."<<endl;
    }
}
/*
int main()
{
    DownloadFile(1);
}*/
#endif
