create table userTable
( userId int  unique not null auto_increment,
  userName varchar(20) primary key,
  passwords varchar(20) not null,
emailId varchar(30) not null );

create table userFile
( userFileId int unique not null auto_increment,
  userId int,
  fileName varchar(50),
	fileDateTime datetime default current_timestamp,
    versionNo int ,
    versionOf int ,
    fileSize int,
  Primary Key(userId, fileName),
  Foreign Key (userId) references userTable(userId) on delete cascade );
  
create table hashTable
( shaId int  unique not null auto_increment,
	userFileId int,
  rollHash int not null,
  sha256 varchar(100) not null,
  chunkSize int 
);

create table fileDetails
( userFileId int ,
  shaId int,
  foreign key (userFileId) references userFile(userFileId) on delete cascade ,
  foreign key (shaId) references hashTable(shaId) on delete cascade  );

create table shaTable
( sha256Value varchar(256),
	shacount int
);
	
