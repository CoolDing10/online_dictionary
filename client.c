
#include<stdio.h>

#include<stdlib.h>

#include<sys/socket.h>

#include<unistd.h>

#include<sys/types.h>

#include<netinet/in.h>

#include<string.h>

#include<arpa/inet.h>

#include"online_dic.h"


#define begin 1
#define functon 2

#define serv_ip "10.67.189.30"

#define serv_port 4999



int main(void){
    int cmd_view = begin;
    int cmd = 0;
    int sockfd;
    struct sockaddr_in servaddr;
    char buf[132];
    Messg messg;
    int ret;

    client_init(&sockfd, &servaddr, serv_port, serv_ip);

    while(1){
        if(cmd_view=begin){
            view_begin();
            scanf("%d", &cmd);
            if(cmd==1){
                ret = do_login(&messg, buf, sockfd, &servaddr);
                if(ret==1){
                    cmd_view = functon;
                }
            }else if(cmd==2){
                ret = do_register(&messg, buf, sockfd, &servaddr);
                
            }else if(cmd==3){
                exit(0);
            }else{
                printf("error input\n");
                cmd_view = begin;
            }
        }

        if(cmd_view==functon){
            view_function();
            scanf("%d", &cmd);
            if(cmd==1){
                do_search(&messg, buf, sockfd);
            }else if(cmd==2){
                do_history(&messg, buf, sockfd);
            }else if(cmd==3){
                view_begin();
            }else if(cmd==4){
                exit(0);
            }else{
                printf("error input\n");
                cmd_view = functon;
            }
        }
    }
}