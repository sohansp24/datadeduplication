#include<iostream>
#include<cstring>
#include<mysql/mysql.h>
using namespace std;
MYSQL* connect()
{
    MYSQL *connect;
    connect=mysql_init(NULL);
    if(!connect)
    {
        cout<<"Connection failed"<<endl;
        return NULL;
    }
    connect = mysql_real_connect(connect, "localhost", "admin", "123456", "project", 0,NULL,0);
    if(connect)
    {
        cout<<"Connection Sucessfull"<<endl;
        return connect;
    }
    return NULL;
}
MYSQL_RES* execute_query(MYSQL* connect, string query)
{
    MYSQL_RES *res_set;
    char query_arr[query.length()];
    strcpy(query_arr,query.c_str());
    mysql_query(connect,query_arr);
    res_set=mysql_store_result(connect);
    return res_set;
}
void show_result(MYSQL_RES * res_set)
{
    
    int i=0;
    MYSQL_ROW row;
    unsigned int numrows = mysql_num_rows(res_set);
    if (numrows!=0)
    {
        while (((row=mysql_fetch_row(res_set)) !=NULL))
        {
            cout << row[i] << endl;
        }
    }
    else
    {
        cout<<"No entry found"<<endl;
        return;
    }
    //mysql_close (connect);
}
int main(int argc, char const *argv[])
{
    MYSQL* connect_obj=connect();
    MYSQL_RES* res_set= execute_query(connect_obj,"show tables;");
    show_result(res_set);
    return 0;
}
