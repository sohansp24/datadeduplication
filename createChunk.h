#ifndef CREATE_CHUNK
#define CREATE_CHUNK
#include<bits/stdc++.h>
#include<unordered_map>
#include<mysql/mysql.h>
#include<fstream>
#include<vector>
#include "retrieveID.h"
#include "sql_handler.h"
#include "sha256_main.h"
#include "file_opr.h"

namespace mysql_createchunk
{
    MYSQL * connect_obj=connect();
    MYSQL_RES * res_set;
    MYSQL_ROW row;
}
using namespace std;


int hconst=69069;
int mult;
int buffer[1024];
int bufferptr;
unordered_map<int,vector<string>> map1;
unordered_map<string,int> map4count;
vector <string> array_of_file_sha;

ifstream fin;
string string_w;
int inithash()
{
    long hash=0;
    for (int i=0;i<=1023;i++)
    {
        int c;
        char d;
        fin.read(&d,1);
        c=(int)d;
        //cout<<d<<"  "<<c<<"\t";
        //cout<<"INIT:- "<<bufferptr;
        string_w+=d;
        buffer[bufferptr]=c;
        bufferptr++;
        bufferptr=bufferptr% (sizeof(buffer)/sizeof(int));
        hash*= hconst;
        hash+= c;
        if(i>0)
			mult *= hconst;
    }
    /*string st="";
    for(int i: buffer)
    {
        st += to_string(i);
    }
    cout<<st<<"\n";*/
    //cout<<"INIT STRING"<<string_w;
	return hash ;
}
int nexthash(int prevhash)
{
    int c;
    char d;
    fin.read(&d,1);
    c=(int)d;
	string_w+= d;
	prevhash -= mult * buffer[bufferptr];
	prevhash *= hconst;
	prevhash += c;
	buffer[bufferptr] =c;
	bufferptr++;
	bufferptr = bufferptr % (sizeof(buffer)/sizeof(buffer[0]));
    //cout<<"Buffer:=   "<<bufferptr<<endl;
    //cout<<string_w;
    /*string st="";
    for(int i: buffer)
    {
        st += to_string(i);
    }
    cout<<st<<endl;*/
    //cout<<"Next:- "<<bufferptr;
	return prevhash;
}
void getShaCount()
{
    string query="select * from shaTable;";
    mysql_createchunk::res_set=execute_query(mysql_createchunk::connect_obj,query);
    unsigned int numrows = mysql_num_rows(mysql_createchunk::res_set);
    map4count.clear();
    if(numrows==0)
    {
        cout<<"\nSHA Table Empty"<<endl;
    }
    else
    {
        while (((mysql_createchunk::row=mysql_fetch_row(mysql_createchunk::res_set)) !=NULL))
        {
            string s=mysql_createchunk::row[0];
            int i=stoi(mysql_createchunk::row[1]);
            map4count.insert(make_pair(s,i));
        }
    }
}
bool isAvailSha(string hashIn256)
{
    if(map4count.find(hashIn256)!=map4count.end())
        return true;
    else
        return false;
}
void createChunk(int fileId,string fileLocation)
{
    //array_of_file_sha.reserve(200);
    map1.clear();
    map1=retrieveMap();
    int mask=1<<13;
    mult=1;
    bufferptr=0;
    mask--;
    ifstream tempfin(fileLocation,ios::binary);
    fin.swap(tempfin);
    fin.seekg(0,ios::end);
    int size=fin.tellg();
    cout<<"* Size of the file is: "<<size<<endl;
    int counter=0;
    fin.seekg (0,ios::beg);
    long hash=inithash();
    cout<<"* INT Hash:-\t"<<hash<<endl;
    int curr=fin.gcount()*1024;
    //cout<<fin.gcount();
    //curr-=tmp_size;
    //cout<<curr<<"  "<<size<<endl;
    //cout<<"* "<<string_w.size()<<" bytes read\n* Contents Read are:-\n"<<string_w<<"\n* Size of the file to be fetched "<<curr<<endl;
    //int j=0;
    //ofstream fout;
    //fout.open("testing.txt",ios_base::app);
    int flag;
    float progress=0;
    while(curr<=size)
    {
        //fout<<string_w;
        if ((hash & mask)==0 || curr==size-1)
        {
            //cout<<"----";
            string hashIn256=sha256(string_w);
            //cout<<string_w<<endl;
            //cout<<curr<<"    "<<(hash & mask);
            //cout<<"Hash Value  "<<hashIn256<<endl;
            //cout<<"if iffff";
            array_of_file_sha.push_back(hashIn256);
            //cout<<"-----";
            string ID=to_string(fileId);
            string has=to_string(hash);
            //cout<<"In if";
            //cout<<"----------";
            flag=0;
            if(map1.find(hash)==map1.end())
            {
                flag=1;
                map1.insert(make_pair(hash,(vector<string>){hashIn256}));
                //MYSQL_RES* mysql_createchunk::res_set;
                string query="Insert into hashTable (userFileId,rollHash,sha256) values ('"+ID+"','"+has+"','"+hashIn256+"')";
                execute_query(mysql_createchunk::connect_obj,query);
                createFile(hash,string_w,hashIn256);
            }
            vector<string> it=map1.find(hash)->second;
            if((find(it.begin(),it.end(),hashIn256)==it.end()) && flag==0)
            {
                flag=1;
                //cout<<"------";
                map1.find(hash)->second.push_back(hashIn256);
                string query="Insert into hashTable (userFileId,rollHash,sha256) values ('"+ID+"','"+has+"','"+hashIn256+"')";
                execute_query(mysql_createchunk::connect_obj,query);
                createFile(hash,string_w,hashIn256);
            }
            if(flag==0)
            {
                cout<<counter++<<"\n => YES hash\tYES 256\t"<<"  =>  "<<has<<"\tsha256\t"<<hashIn256<<endl;
                cout.flush();
                string query="Insert into hashTable (userFileId,rollHash,sha256) values ('"+ID+"','"+has+"','"+hashIn256+"')";
                execute_query(mysql_createchunk::connect_obj,query);
            }
            progress+=string_w.length();
            string_w="";
            showprogress((float)progress/size);
        }
        hash = nexthash(hash);
        //cout<<fin.gcount()*1024<<"    "<<curr<<endl;
        //cout<<"\t"<<curr++;

        curr++;
        //cout<<"curr"<<curr;
    }
    //fout.close();
    //cout<<"=====";
    //str.clear();
    //copy(array_of_file_sha.begin(), array_of_file_sha.end()-1,std::ostream_iterator<string>(str, ","));
    //str << array_of_file_sha.back();
    //cout<<str.str();
    getShaCount();
    for(string s: array_of_file_sha)
    {
        //cout<<" --   ";
        bool res=isAvailSha(s);
        //cout<<"Res"<<res<<endl;
        string query;
        if(res==true)
        {
            int count=map4count.find(s)->second;
            query="update shaTable set shacount= "+to_string(++count)+" where sha256Value = '"+s+"';";
            execute_query(mysql_createchunk::connect_obj,query);
        }
        else
        {            
            query="Insert into shaTable values ('"+s+"',1);";
            execute_query(mysql_createchunk::connect_obj,query);
        }
    }
    array_of_file_sha.clear();
    fin.close();
    tempfin.close();
}
#endif
/*
int main()
{
    createChunk(1,"/home/admin/sample.txt");
}
*/