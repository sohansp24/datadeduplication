#include<bits/stdc++.h>
#include<unordered_map>
#include<mysql/mysql.h>
#include<fstream>
#include "sql_handler.cpp"

MYSQL * connect_obj=connect();
int hconst=69069;
int mult;
//int buffer[];
int bufferptr;
unordered_map<int,string> map;
unordered_map<string,int> map4count;
string string_w;
int inithash(int from,int to)
{
    return 0;
}
void createChunk(int fileId,string fileLocation)
{   
    int mask=1<<13;
    mult=1;
    bufferptr=0;
    mask--;
    ifstream fin(fileLocation);
    streambuf* pbuf=fin.rdbuf();
    streamsize size=pbuf->in_avail();
    cout<<"Size of the file is: "<<size<<endl;
    int counter=0;
    long hash=inithash(1024-1,0);
    int curr=size;
    size=pbuf->in_avail();
    curr-=size;
    cout<<"Size of the file is: "<<curr<<endl;
    while(curr<size)
    {
        if ((hash  & mask==0) || curr==size-1)
        { 
            strcpy( char buffer,string_w);
        }
    
    }
    //fin=pbuf;
}
//*
int main()
{
    createChunk(1,"/home/admin/file1.txt");
}
//*/
