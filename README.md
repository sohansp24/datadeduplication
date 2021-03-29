# DataDeduplication
Three directories needed to be created  in parent directory for execution:
1) chunks
2) download 
3) file<br>

<I>Directory names are case sensitive<br>
Change mysql username and password in sql_handler.h to what you've setup during MySQL installation in your PC<br></I>
<b> How to run this program: (For LINUX based systems only) </b><br>
<ul>
  <li>
First navigate to the folder to which you've  downloaded and extracted the code<br>
<li>
Run the following commands in Linux Terminal<br></ul>
``1.  g++ -o index index.cpp -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql``
<br>
``2. ./index``

