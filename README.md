# DataDeduplication
Three directories needed to be created  in parent directory for execution:
1) Chunk
2) Download 
3) File<br>

<I>Change mysql username and password in sql_handler.h to what you've setup during MySQL installation in your PC
</I><br>
<b> How to run this program: (For LINUX based systems only) </b><br>
Run the following commands in command prompt/terminal<br>
1. 
```g++ -o index index.cpp -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql```
<br>
2. 
```./index```
