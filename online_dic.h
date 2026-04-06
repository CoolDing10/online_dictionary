#ifndef _ONLINE_DIC_H_
#define _ONLINE_DIC_H_

typedef struct information{
    int messg_type;


    union {
        struct login_data{
            char name[16];
            int passwaord;
        } login_data;

        char dictionary[24];

        char note[128];

        char history[5][24];
    }data;
}Messg;


typedef struct{
    char name[16];
    int password;
    char history[5][24];
} USER;

int view_begin();

int view_function();

int client_init(int *sockfd, struct sockaddr_in *addr, int serv_port, char serv_ip[]);

int do_login(Messg *messg, char *buf, int sockfd, struct sockaddr_in *servaddr);

int do_register(Messg *messg, char *buf, int sockfd, struct sockaddr_in *servaddr);

int do_search(Messg *messg, char *buf, int sockfd);

int do_history(Messg *messg, char *buf, int sockfd);
#endif