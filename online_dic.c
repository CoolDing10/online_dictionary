#include<stdio.h>
#include<stdlib.h>
#include"online_dic.h"
#include <sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
int view_begin(){
    system("clear");
    printf("###################在线词典#################\n");
    printf("\n");
    printf("    1,登录       2.注册          3.退出      \n");
    printf("\n");
    printf("###########################################\n");

    return 1;
}

int view_function(){
    system("clear");
    printf("###################在线词典#################\n");
    printf("\n");
    printf(" 1.查询词典  2.历史记录  3.返回上级  4.退出程序 \n");
    printf("\n");
    printf("###########################################\n");


    return 1;
}


int client_init(int *sockfd, struct sockaddr_in *addr, int serv_port, char serv_ip[]){
    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (*sockfd==-1)
    {
        perror("socket");
        return 0;
    }
    bzero(addr, sizeof(*addr));
    // memset(addr, 0, sizeof(*addr));

    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = inet_addr(serv_ip);
    addr->sin_port = htons(serv_port);

    if(connect(*sockfd,(struct sockaddr*)addr,sizeof(*addr))==-1){
        perror("connect");
        return 0;
    }
    return 1;
}


int do_login(Messg *messg, char *buf, int sockfd, struct sockaddr_in *servaddr){
    system("clear");
    bzero(messg,sizeof(*messg));

    messg->messg_type = 1;

    printf("请输入你的名字：\n");
    scanf("%s", messg->data.login_data.name);
    printf("请输入你的密码：\n");
    scanf("%d", messg->data.login_data.passwaord);

    memset(buf, 0, 132);

    buf = (char *)messg;

    send(sockfd, buf, 132, 0);
    memset(buf, 0, 132);
    if(recv(sockfd,buf,132,0)==-1){
        perror("recv");
        return 0;
    }
    if(strncmp(buf,"登录成功",sizeof(buf))==0){
        printf("%s\n", buf);
        sleep(1);
        return 1;
    }else{
        printf("%s\n", buf);
        return 0;
    }
    return 1;
}

int do_register(Messg *messg, char *buf, int sockfd, struct sockaddr_in *servaddr){
    system("clear");

    bzero(messg, sizeof(*messg));
    messg->messg_type = 2;

    printf("请输入你的名字：\n");
    scanf("%s", messg->data.login_data.name);
    printf("请输入你的密码：\n");
    scanf("%d", messg->data.login_data.passwaord);

    memset(buf, 0, 132);
    buf = (char *)messg;

    send(sockfd, buf, 132, 0);
    memset(buf, 0, 132);
    if(recv(sockfd,buf,132,0)==-1){
        perror("recv");
        return 0;
    }
    if(strncmp(buf,"注册成功",sizeof(buf))==0){
        printf("%s\n", buf);
        sleep(1);
        return 1;
    }else{
        printf("%s\n", buf);
        return 0;
    }
    return 1;

}

int do_search(Messg *messg, char *buf, int sockfd){
    char enter = '0';

    system("clear");
    bzero(messg, sizeof(*messg));
    messg->messg_type = 3;

    printf("请输入单词：\n");
    scanf("%s", messg->data.dictionary);
    memset(buf, 0, 132);

    buf = (char *)messg;
    send(sockfd, buf, 132, 0);

    memset(buf, 0, 132);
    if(recv(sockfd,buf,256,0)==-1){
        perror("recv");
        sleep(3);
        return 0;
    }
    printf("%s\n", buf);
    printf("按回车键退出");
    fflush(0);
    getchar();
    while(enter != '\n'){
        scanf("%c", &enter);
    }
    return 1;
}

int do_history(Messg *messg, char *buf, int sockfd){ 
    USER *user;
    int i;
    char enter='0';
    system("clear");
    bzero(messg, sizeof(*messg));
    messg->messg_type = 4;
    memset(buf, 0, 132);
    buf = (char *)messg;

    send(sockfd, buf, 132, 0);
    memset(buf, 0, 132);
    if(recv(sockfd,buf,132,0)==-1){
        perror("recv");
        sleep(3);
        return 0;
    }
    user = (USER *)buf;
    printf("##################历史记录#################\n");
    for(i=0;i<5;i++){
        printf("%d.%s\n",(i+1), user->history[i]);
    }
    printf("\n");
    printf("按回车键退出");
    getchar();
    while(enter != '\n'){   
        scanf("%c", &enter);
    }
    return 1;
}
