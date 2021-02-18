#include<bits/stdc++.h>
#include<unordered_map>
#include<mysql/mysql.h>
#include<fstream>
#include<vector>
#include "sql_handler.cpp"
#include "sha256.cpp"
#include "file_opr.cpp"
using namespace std;

MYSQL * connect_obj=connect();
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
    //cout<<bufferptr;
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
	return prevhash;
}
void getShaCount()
{
    string query="select * from shaTable;";
    MYSQL_ROW row;
    MYSQL_RES* res_set=execute_query(connect_obj,query);
    unsigned int numrows = mysql_num_rows(res_set);
    if(numrows==0)
    {
        cout<<"Empty"<<endl;
    }
    else
    {
        while (((row=mysql_fetch_row(res_set)) !=NULL))
        {
            string s=row[0];
            int i=stoi(row[1]);
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
    int curr=size;
    curr-=fin.gcount()*1024;
    //cout<<fin.gcount();
    //curr-=tmp_size;
    //cout<<curr<<"  "<<size<<endl;
    //cout<<"* "<<string_w.size()<<" bytes read\n* Contents Read are:-\n"<<string_w<<"\n* Size of the file to be fetched "<<curr<<endl;
    //int j=0;
    //ofstream fout;
    //fout.open("testing.txt",ios_base::app);
    while(curr<size)
    {
        //fout<<string_w;
        if ((hash & mask)==0 || curr==size-1)
        {
            //cout<<"----";
            string hashIn256=sha256(string_w);
            cout<<string_w<<endl;
            cout<<curr<<"    "<<(hash & mask);
            cout<<"Hash Value  "<<hashIn256<<endl;
            cout<<"if iffff";
            array_of_file_sha.push_back(hashIn256);
            cout<<"-----";
            string ID=to_string(fileId);
            string has=to_string(hash);
            cout<<"In if";
            vector<string> it=map1.find(hash)->second;
            //cout<<"----------";
            if(map1.find(hash)==map1.end())
            {
                map1.insert(make_pair(hash,(vector<string>){hashIn256}));
                //MYSQL_RES* res_set;
                string query="Insert into hashTable (userFileId,rollHash,sha256) values ('"+ID+"','"+has+"','"+hashIn256+"')";
                execute_query(connect_obj,query);
                createFile(hash,string_w,hashIn256);
            }
            else if(find(it.begin(),it.end(),hashIn256)==it.end())
            {
                cout<<"------";
                map1.find(hash)->second.push_back(hashIn256);
                string query="Insert into hashTable (userFileId,rollHash,sha256) values ('"+ID+"','"+has+"','"+hashIn256+"')";
                execute_query(connect_obj,query);
                createFile(hash,string_w,hashIn256);
            }
            else
            {
                cout<<counter++<<"=> YES hash\tYES 256\t"<<"  =>  "<<has<<"\tsha256\t"<<hashIn256;
            }
            string_w="";
        }
        hash = nexthash(hash);
        //cout<<fin.gcount()*1024<<"    "<<curr<<endl;
        //cout<<"\t"<<curr++;
        curr++;
    }
    //fout.close();
    cout<<"=====";
    //str.clear();
    //copy(array_of_file_sha.begin(), array_of_file_sha.end()-1,std::ostream_iterator<string>(str, ","));
    //str << array_of_file_sha.back();
    //cout<<str.str();
    getShaCount();
    for(string s: array_of_file_sha)
    {
        cout<<" --   ";
        bool res=isAvailSha(s);
        string query;
        if(res)
        {
            int count=map4count.find(s)->second;
            query="update shaTable set shacount "+to_string(count)+" where sha256Value ="+s+";";
        }
        else
            query="Insert into shaTable values ("+s+",1);";
        execute_query(connect_obj,query);
    }
    array_of_file_sha.clear();
}
/*
int main()
{
    createChunk(1,"/home/admin/sample.txt");
}
*/
