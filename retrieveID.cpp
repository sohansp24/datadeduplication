#include<bits/stdc++.h>
#include<unordered_map>
#include<mysql/mysql.h>
#include<vector>
#include "sql_handler.cpp"
#include "sha256.cpp"
using namespace std;
MYSQL* connect_obj=connect();
unordered_map <string,int> countmap;
MYSQL_RES* res_set;
MYSQL_ROW row;
int i=0;

vector<int> retriveshaID(int fileID)
{
    vector<int> arr;
    string query="select shaId from fileDetails where userFileId= "+to_string(fileID)+";";
    res_set=execute_query(connect_obj,query);
    MYSQL_ROW row;
    int i=0;
    unsigned int numrows =mysql_num_rows(res_set);
    if (numrows!=0)
    {
        while (((row=mysql_fetch_row(res_set)) !=NULL))
        {
            arr.push_back(stoi(row[i]));
        }
    }
    return arr;
}

int retrieveFileId(int userId,string fileName)
{
    int userFileID=0;
    string query="select userFileId from userFile where userId= "+to_string(userId)+"and fileName= "+fileName+" ;";
    res_set=execute_query(connect_obj,query);
    unsigned int numrows =mysql_num_rows(res_set);
    if (numrows!=0)
    {
        while (((row=mysql_fetch_row(res_set)) !=NULL))
        {
            userFileID=stoi(row[i]);
        }
    }
    return userFileID;
}

vector<string> retrieveSha(vector<int> shaid)
{
    vector<string> arrSha;
    for(int i:shaid)
    {
        string query="select sha256 from hashtable where shaid= "+to_string(i)+";";
        res_set=execute_query(connect_obj,query);
        unsigned int numrows =mysql_num_rows(res_set);
        if (numrows!=0)
        {
            while (((row=mysql_fetch_row(res_set)) !=NULL))
            {
                arrSha.push_back(row[i]);
            }
        }
    }
    return arrSha;
}

int showFiles(int UserId)
{
    string query="select userFileId,fileName from userFile where userId= "+to_string(UserId)+" ;";
    res_set=execute_query(connect_obj,query);
    unsigned int numrows =mysql_num_rows(res_set);
    cout<<"FileID\tFileName"<<endl;
    if (numrows!=0)
    {
        while (((row=mysql_fetch_row(res_set)) !=NULL))
        {
            cout<<row[i]<<"\t"<<row[i+1]<<endl;
        }
    }
    cout<<"Enter FileID: ";
    int fileid;
    cin>>fileid;
    cout<<endl;
    return fileid;
}

string showFilesName(int fileId)
{
    string query="select fileName from userFile where userfileId= "+to_string(fileId)+" ;";
    res_set=execute_query(connect_obj,query);
    string fileName;
    unsigned int numrows =mysql_num_rows(res_set);
    if (numrows!=0)
    {
        while (((row=mysql_fetch_row(res_set)) !=NULL))
        {
            fileName=row[i];
        }
    }
    return fileName;
}

vector<int> retrieveAllFileId(int userId)
{
    string query="select userFileId from userFile where userId= "+to_string(userId)+" ;";
    vector<int> allFileId;
    unsigned int numrows =mysql_num_rows(res_set);
    if (numrows!=0)
    {
        while (((row=mysql_fetch_row(res_set)) !=NULL))
        {
            allFileId.push_back(stoi(row[i]));
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
        string query="select sha256 from hashTable where userFileId= "+to_string(j)+" ;";
        res_set=execute_query(connect_obj,query);
        unsigned int numrows =mysql_num_rows(res_set);
        if (numrows!=0)
        {
            while (((row=mysql_fetch_row(res_set)) !=NULL))
            {
                allShaValues.push_back(row[i]);
            }
        }
    }
    return allShaValues;
}

int retrieveVersionNo(int fileId)
{
    string query="select MAX(versionNo) from userFile where versionOf= "+to_string(fileId)+" ;";
    res_set=execute_query(connect_obj,query);
    int versionNo;
    unsigned int numrows =mysql_num_rows(res_set);
    if (numrows!=0)
    {
        while (((row=mysql_fetch_row(res_set)) !=NULL))
        {
            versionNo=stoi(row[i]);
        }
    }
    return versionNo;
}

int showFileVersion(int fileId)
{
    string query="select fileName,versionNo from userFile where versionOf= "+to_string(fileId)+" ;";
    res_set=execute_query(connect_obj,query);
    unsigned int numrows =mysql_num_rows(res_set);
    cout<<"Version No.\tFile Name"<<endl;
    if (numrows!=0)
    {
        while (((row=mysql_fetch_row(res_set)) !=NULL))
        {
            cout<<row[i]<<"\t"<<row[i+1];
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
    string query="select fileName from userFile where userId= "+to_string(userId)+ "and versionNo= 1 ";
    res_set=execute_query(connect_obj,query);
    unsigned int numrows =mysql_num_rows(res_set);
    cout<<"File names are: "<<endl;
    if (numrows!=0)
    {
        while (((row=mysql_fetch_row(res_set)) !=NULL))
        {
            cout<<row[i]<<endl;
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
    int versionno=0;
    string query="select versionNo from userfile where userFileId= "+to_string(fileId)+" ;";
    res_set=execute_query(connect_obj,query);
    unsigned int numrows =mysql_num_rows(res_set);
    if (numrows!=0)
    {
        while (((row=mysql_fetch_row(res_set)) !=NULL))
        {
            versionno=stoi(row[i]);
        }
    }
    return versionno;
}

vector<string> retrieveShaValue(int fileId)
{
    vector<string> arr;
    string query="select sha256 from hashTable where userFileId= "+to_string(fileId)+" ;";
    res_set=execute_query(connect_obj,query);
    unsigned int numrows =mysql_num_rows(res_set);
    if (numrows!=0)
    {
        while (((row=mysql_fetch_row(res_set)) !=NULL))
        {
            arr.push_back(row[i]);
        }
    }
    return arr;
}
/*
int main()
{
    retriveshaID(1);
}
*/
