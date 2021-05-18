#include<bits/stdc++.h>
#include<mysql/mysql.h>
#include "sql_handler.h"
#include "file_opr.h"
#include "downloadFile.h"
#include "uploadFile.h"
#include "deleteData.h"
#include "updateFile.h"

namespace mysql_main
{
    MYSQL * connect_obj=connect();
    MYSQL_RES * res_set;
    MYSQL_ROW row;
}
using namespace std;

void userMenu(int UserId, string username)
{
    while(true){
    cout<<"Welcome "+ username + "\n** Please Select a option **\n\t1. Upload File\n\t2. Download File\n\t3. Update File\n\t4. Delete File\n\t5. Delete Version\n\t6. Show My Uploaded Files\n\t7. Delete User\n\t8. Exit"<<endl;
    int ch;
    cin>>ch;
    switch(ch)
    {
        case 1:
            insertIntoUserFile(UserId);
            break;
        case 2:
            DownloadFile(UserId);
            break;
        case 3:
            update(UserId);
            break;
        case 4:
            deleteFile(UserId);
            break;
        case 5:
            deleteVersion(UserId);
            break;
        case 6:
            cout<<"Files you have uploaded are :-"<<endl;
            showFiles(UserId,1);
            break;
        case 7:
            deleteUser(UserId);
            break;
        case 8:
            cout<<"Bye..."<<endl;
            exit(0);
            break;    
        default:
            cout<<"Invalid Input"<<endl;
            break;
    }
    }
}

int main(int argc, char const *argv[])
{

    int choice;
    cout<<"Enter Choice:\n\t1.Login\n\t2.Register"<<endl;
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
        mysql_main::res_set =execute_query(mysql_main::connect_obj,query);
        cout<<"Registeration Successfull... :)\nThanks for registering with us..\nNow please login to continue.."<<endl;
    }
    mysql_close (mysql_main::connect_obj);
    return 0;
}
