#include<bits/stdc++.h>
#include<unordered_map>
#include<mysql/mysql.h>
#include<fstream>
#include<vector>
#include "sql_handler.cpp"
#include "sha256.cpp"

using namespace std;

MYSQL * connect_obj=connect();
int hconst=69069;
int mult;
int buffer[1025];
int bufferptr;
unordered_map<int,vector<string>> map1;
unordered_map<string,int> map4count;
vector <string> array_of_file_sha;
ifstream fin;
string string_w;

int inithash()
{
    int hash=0;
    //cout<<"---";
    for (int i=0;i<=1023;i++)
    {
        int c;
        char d;
        //cout<<"---";
        fin.read(&d,1);
        c=(int)d;
        //cout<<c<<" ";
        //fread(c,1,1,fin);
        string_w+=d;
        //cout<<c<<" "<<d<<" "<<string_w<<endl;
        //cout<<"----";
        buffer[bufferptr]=c;
        bufferptr++;
        //cout<<bufferptr<<"  ";
        bufferptr=bufferptr% (sizeof(buffer)/sizeof(int));
        hash*=hconst;
        //cout<<c;
        hash+=c;
        if(i>0)
		{
			mult *= hconst;
		}
        //cout<<"inithash   "<<string_w<<"\t";
    }
    //cout<<"\n"<<hash<<endl;
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
    ifstream tempfin(fileLocation,ios::binary);
    fin.swap(tempfin);
    //streambuf* pbuf=fin.rdbuf();
    //streamsize size=pbuf->in_avail();
    fin.seekg(0,ios::end);
    int size=fin.tellg();
    cout<<"Size of the file is: "<<size<<endl;
    int counter=0;
    //cout<<"---";
    fin.seekg (0,ios::beg);
    long hash=inithash();
    cout<<"INT Hash:-   "<<hash<<endl;
    int curr=size;
    size=fin.gcount();
    cout<<size<<endl;
    //size=pbuf->in_avail();
    curr-=size;
    //cout<<"Size of the file is: "<<curr<<endl;
    //cout<<string_w;
    //vector <char> buffer; 
    //cout<<"---"<<curr<<" "<<size<<" "<<"  "<<string_w.size()<<" "<<(curr<size);
    cout<<string_w.size()<<" bytes read\nContents Read are:-\n"<<string_w<<"\nLength of the file to be fetched "<<curr<<endl;
    //cout<<len(string_w);
    while(curr<size)
    {
        //cout<<"    "<<(hash & mask);
        if ((hash  & mask==0) || curr==size-1)
        {
            //cout<<"---"; 
            //char* wordarray=new char [string_w.size()+1];
            //strcpy(wordarray,string_w.c_str());
            string hashIn256=sha256(string_w);
            cout<<"Hash Value"<<hashIn256<<endl;
            array_of_file_sha.push_back(hashIn256);
            //cout<<"----------";
            vector<string> it=map1.find(hash)->second;
            if(map1.find(hash)==map1.end())
            {
                map1.insert(make_pair(hash,vector<string>{hashIn256}));
                ostringstream str;
                str<<fileId;
                string ID=str.str();
                str<<hash;
                string has=str.str();
                //MYSQL_RES* res_set;
                string query="Insert into hashTable (userFileId,rollHash,sha256) values ('"+ID+"','"+has+"','"+hashIn256+"')";
                execute_query(connect_obj,query);
            }
            /*
            else if(find(it.begin(),it.end(),hashIn256)==map1.find(hash)->second.end())
            {
                map1.find(hash)->second.push_back(hashIn256);
            }
            else
            {
                continue;
            }*/
        }
        curr+=10;
    }
    //fin.close();
}
//*
int main()
{
    createChunk(1,"/home/admin/file1.txt");
}
//*
