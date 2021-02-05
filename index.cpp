#include<bits/stdc++.h>
#include "sql_handler.cpp"
#include<mysql/mysql.h>

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
    static MYSQL * connect_obj=connect();
    static MYSQL_RES * res_set;
    static MYSQL_ROW row;
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
        unsigned int numrows=mysql_num_rows(res_set);
        if (numrows==0)
            cout<<"You've entered incorrect username or Password\nTry again..."<<endl;
        else
        {
            int userID,i=0;
            while (((row=mysql_fetch_row(res_set)) !=NULL))
                userID=atoi(row[i]);
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
        res_set =execute_query(connect_obj,query);
    }
    mysql_close (connect_obj);
    return 0;
}
