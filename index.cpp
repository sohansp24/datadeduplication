#include<bits/stdc++.h>
#include "sql_handler.cpp"
#include<mysql/mysql.h>
using namespace std;

int main(int argc, char const *argv[])
{
    static MYSQL * connect_obj=connect();
    static MYSQL_RES * res_set;
    int choice;
    cout<<"Enter Choice:\n1.Login\n2.Register"<<endl;
    cin>>choice;
    if(choice==1)
    {
        string username;
        string password;
        cout<<"Enter Username: ";
        cin>>username;
        cout<<"Enter Password: ";
        cin>>password;
        string query="select userID from  userTable where userName='"+username+"' and passwords='"+password+"';";
        res_set=execute_query(connect_obj,query);
        //show_result(res_set);
        
    }
    else
    {
        string username,email,password;
        cout<<"Create Username: ";
        cin>>username;
        cout<<"Create Password: ";
        cin>>password;
        cout<<"Enter Email ID: ";
        cin>>email;
        string query="insert into userTable(userName,passwords,emailID) values('"+username+"','"+password+"','"+email+"');";
        res_set =execute_query(connect_obj,query);
        cout<<query<<endl;
    }
    return 0;
}
