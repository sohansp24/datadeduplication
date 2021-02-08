#include<bits/stdc++.h>
#include<unordered_map>
#include<mysql/mysql.h>
#include<fstream>
#include<vector>
#include "sql_handler.cpp"
#include "sha256.cpp"

MYSQL * connect_obj=connect();
int hconst=69069;
int mult;
int buffer[1024];
int bufferptr;
unordered_map<int,string> map1;
unordered_map<string,int> map4count;
vector <string> array_of_file_sha;
ifstream fin;
string string_w;
int inithash()
{
    int hash=0;
    for (int i=0;i<1024;i++)
    {
        char *c;
        fin.read(c,1);
        string_w+=c;
        buffer[bufferptr]=atoi(c);
        bufferptr++;
        bufferptr=bufferptr% (sizeof(buffer)/sizeof(int));
        hash*=hconst;
        hash+=atoi(c);
        if(i>0)
		{
			mult *= hconst;
		}
    }
	return hash ;
}
int nexthash(int prevhash)
{
    char* c;
    fin.read(c,1);
	string_w+= c;
	prevhash -= mult * buffer[bufferptr]; 
	prevhash *= hconst; 
	prevhash += atoi(c);
	buffer[bufferptr] = atoi(c); 
	bufferptr++;
	bufferptr = bufferptr % (sizeof(buffer)/sizeof(int));
	return prevhash;
}
void createChunk(int fileId,string fileLocation)
{   
    int mask=1<<13;
    mult=1;
    bufferptr=0;
    mask--;
    ifstream tempfin(fileLocation);
    fin.swap(tempfin);
    streambuf* pbuf=fin.rdbuf();
    streamsize size=pbuf->in_avail();
    cout<<"Size of the file is: "<<size<<endl;
    int counter=0;
    long hash=inithash();
    int curr=size;
    size=pbuf->in_avail();
    curr-=size;
    cout<<"Size of the file is: "<<curr<<endl;
    vector <char> buffer; 
    cout<<"---"<<size<<" "<<curr;
    while(curr<size)
    {
        if ((hash  & mask==0) || curr==size-1)
        { 
            //char* wordarray=new char [string_w.size()+1];
            //strcpy(wordarray,string_w.c_str());
            string hashIn256=sha256(string_w);
            array_of_file_sha.push_back(hashIn256);
            if(map1.find(hash)==map1.end())
            {
                map1.insert(make_pair(hash,hashIn256));
                ostringstream str;
                str<<fileId;
                string ID=str.str();
                str<<hash;
                string has=str.str();
                //MYSQL_RES* res_set;
                string query="Insert into hashtable (userFileId,rollHash,sha256) values ('"+ID+"','"+has+"','"+hashIn256+"')";
                execute_query(connect_obj,query);
            }
        }
    
    }
    //fin=pbuf;
}
//*
int main()
{
    createChunk(1,"/home/admin/sample.class");
}
//*
