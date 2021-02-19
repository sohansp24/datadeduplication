#include<bits/stdc++.h>
#include<mysql/mysql.h>
#include "sql_handler.h"
namespace mysql_main
{
    MYSQL * connect_obj=connect();
    MYSQL_RES * res_set;
    MYSQL_ROW row;
}
using namespace std;

void userMenu(int UserID, string username)
{
    cout<<"Welcome "+ username + "\n** Please Select a option **\n\t1. Upload File\n\t2. Download File\n\t3. Delete File\n\t4. Delete Version\n\t5. Delete User\n\t6. updateFile\n\t7. Exit"<<endl;
    int ch;
    cin>>ch;
    switch(ch)
    {
        case 1:
            //insertIntoUserFile(userId);
            break;
        case 2:
            //download(userId);
            break;
        case 3:
            //deleteFile(userId);
            break;
        case 4:
            //deleteVersion(userId);
            break;
        case 5:
            //deleteUser(userId);
            break;
        case 6:
            //update(userId);
            break;
        case 7:
            cout<<"Bye..."<<endl;
            break;
        default:
            cout<<"Invalid Input"<<endl;
            break;
    }
}

int main(int argc, char const *argv[])
{

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
        mysql_main::res_set=execute_query(mysql_main::connect_obj,query);
        unsigned int numrows=mysql_num_rows(mysql_main::res_set);
        int i=0;
        if (numrows==0)
            cout<<"You've entered incorrect username or Password\nTry again..."<<endl;
        else
        {
            int userID,i=0;
            while (((mysql_main::row=mysql_fetch_row(mysql_main::res_set)) !=NULL))
                userID=atoi(mysql_main::row[i]);
            cout<<"User ID: "<<userID<<endl;
            userMenu(userID,username);
        }

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
        cout<<query<<endl;
        mysql_main::res_set =execute_query(mysql_main::connect_obj,query);
    }
    mysql_close (mysql_main::connect_obj);
    return 0;
}
