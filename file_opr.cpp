#include<bits/stdc++.h>
#include<fstream>
using namespace std;
void createFile(int hash_val,string word, string hash256val)
{
    ofstream fout;
    ifstream fin;
    string fileName = "chunks/"+hash256val;
    //string fileName=hash256val;
    fout.open(fileName);
    fout<<word;
    cout<<"-----------------"<<endl;
    fout.close();

}
void createOriginal(string sha256[],string fileName)
{
    ofstream fout;
    ifstream fin;
    string str;
    string str1="";
    for(int i=0;i<(sizeof(sha256)/sizeof(string));i++)
    {
        string chunkname="chunks/"+sha256[i];
        fin.open(chunkname);
        while ( getline (fin,str) )
        {
            str1+=str;
        }
    }
    fin.close();
    string finalname="download/"+fileName;
    fout.open(finalname);
    fout<<str1;
    fout.close();
}
void deleteFile(string shaValue)
{
    string fileName="chunks/"+shaValue;
    if(remove(fileName.c_str()))
        cout<<"File Deleted Sucessfully"<<endl;
    else 
        cout<<"File Deletion Failed"<<endl;
}
/*
int main()
{
    createFile(54554,"sdsddsd","f6421aea0e10c0c24f970a7ba350350f4674401999525c3e1c2e43d11cc8a764");
    string arr[]={"dsdds","dsdssd"};
    //createOriginal(arr,"sdddssd");
}*/