#ifndef  FILE_OPR
#define FILE_OPR
#include<bits/stdc++.h>
#include<fstream>
using namespace std;
void showprogress(float progress)
{
    int barWidth = 70;
    cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) 
    {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    cout << "] " << int(progress * 100.0) << " %\r";
    cout.flush();
}
void createFile(int hash_val,string word, string hash256val)
{
    ofstream fout;
    //ifstream fin;
    string fileName = "chunks/"+hash256val;
    //string fileName=hash256val;
    fout.open(fileName,ios::binary);
    fout<<word;
    fout.flush();
    //cout<<"-----------------"<<endl;
    fout.close();

}
void createOriginal(vector<string> sha256,string fileName)
{
    ofstream fout;
    ifstream fin;
    string str;
    string str1;
    string finalname="download/"+fileName;
    fout.open(finalname,ios::binary);
    for(string i: sha256)
    {
        str1="";
        string chunkname="chunks/"+i;
        fin.open(chunkname,ios::binary);
        while ( getline (fin,str) )
        {
            str1+=(str+"\n");
        }
        fout<<str1;
        fin.close();
    } 
    fout.flush();
    fout.close();
}
void deletefile(string shaValue)
{
    string fileName="chunks/"+shaValue;
    if(remove(fileName.c_str())!=0)
        cout<<"\nFile "+shaValue+" Deletion Failed"<<endl;
}
#endif
/*
int main()
{
    createFile(54554,"sdsddsd","f6421aea0e10c0c24f970a7ba350350f4674401999525c3e1c2e43d11cc8a764");
    string arr[]={"dsdds","dsdssd"};
    //createOriginal(arr,"sdddssd");
}*/
