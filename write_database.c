/*
   此程序可将单词文本文件写入sqlite数据库，程序运行的第一个参数为文本文件，第二个参数为要创建的数据库名。
   */

#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<sqlite3.h>

int main(int argc,char *argv[]){
	FILE *fp;
	sqlite3 *db;
	char *errmsg;
	char buf[256],dictionary[24],note[128];
	int i,temp,num=0;
	char sql[64];

	//判断参数是否输入错误。
	if(argc<2){
		printf("Usage : %s <src_file> <dst_file>\n",argv[0]);
		return 0;
	}
	//打开单词文本文件。	
	if((fp=fopen(argv[1],"r"))==NULL){
		perror("fopen");
		return 0;
	}
	//创建数据库。
	if(sqlite3_open(argv[2],&db)!=SQLITE_OK){
		printf("%s\n",sqlite3_errmsg(db));
		return 0;
	}else{
		printf("create database success\n");
	}
	//创建表。
	if(sqlite3_exec(db,"create table stu(id Integer,dictionary char,note char);",NULL,NULL,&errmsg)!=SQLITE_OK){
		printf("%s\n",errmsg);
	}else{
		printf("create table success\n");
	}

	//循环遍历，将文本所有单词加入数据库中。
	//读取文件的一行字符并放入缓冲区,通过判断字符前后位置是否有空格来拆分成单词字符串和注释字符串。
	while(fgets(buf,256,fp)){
		printf("%s\n",buf);
		for(i=1;i<sizeof(buf);i++){
			if(buf[i-1]>='a'&&buf[i-1]<='z'&&buf[i]==' '){
				strncpy(dictionary,buf,i);
				dictionary[i]='\0';
			}
			if(buf[i]!=' '&&buf[i-1]==' '){
				temp=i;
				break;
			}
		}
		strncpy(note,buf+temp,sizeof(buf)-temp);
		printf("%s\t%s\n",dictionary,note);
		// 将单词和注释字符串插入数据库表中。
		num++;
		sprintf(sql,"insert into stu values(%d,'%s','%s');",num,dictionary,note);
		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg)!=SQLITE_OK){
			printf("%s\n",errmsg);
		}else{
			printf("add table success\n");
		}
	}
	return 0;
}
