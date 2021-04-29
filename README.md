# DataDeduplication
Three directories needed to be created  in parent directory for execution: (if you are downloading zip from GitHub or cloning the repo then this step is not necessary)
1)  chunks
2)  download 
3)  file<br>

<I>Directory names are case sensitive<br>
<br>
Refer MySQL installation process on Google corresponding to which Linux flavour/variant you are currently using<br>
Change mysql username and password in sql_handler.h (line no. 17) to what you've setup during MySQL installation in your PC<br></I>
<br><br>
<b> How to run this program: (For LINUX based systems only) </b><br>
<ul>
<li>First navigate to the folder to which you've  downloaded and extracted the code</li><br>
<li>Execute the following commands in Linux Terminal</li><br></ul>
<ol>
  <li><code>g++ -o index index.cpp -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql</code></li>
  <br>
  <li><code>./index</code></li>
</ol>
<b>If you are getting Database connection failed message</b><br>
Execute the following command in Linux Terminal<br>
<code>sudo systemctl start mysqld</code><br>
Enter password if prompted
and  again execute <code>./index</code> <br>
<b>If you are still getting Database connection failed message then Change mysql username and password in sql_handler.h (line no. 17) to what you've setup during MySQL installation in your PC</b><br>
<b>Note: </b>While uploading a file please use the same filenames contained in <I>file</I> directory. If you want to upload your own file, then copy first it in <I>file</I> directory and then enter filename while execution of the project