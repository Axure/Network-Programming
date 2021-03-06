//
// Created by 郑虎 on 15 年 五月. 2..
//

#include "server.h"
//using namespace std;
#include<iostream>
#include <netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define PORT 8888
#define BACKLOG 20
//#define DEST_IP "127.0.0.1"


int process_conn_server(int s)
{
    ssize_t size =0;
    char buffer[1024];

    for( ; ; )
    {
        size = read(s,buffer,1024);
        if(size == 0)
        {
            return 0;
        }
    }
    sprintf(buffer, "%d bytes altogether\n", (int)size);
    write(s, buffer,strlen(buffer)+1);



    return 0;
}

int main(int argc,char *argv[])
{
    //cout<<"?";
    int ss, sc, r, err;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int   opt=1;
    pid_t pid;

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    ss = socket(AF_INET, SOCK_STREAM, 0);
    if(ss<0)
    {
        std::cout<<"[process infro]socket error"<<std::endl;
        return -1;
    }
    std::cout<<"[process infro]socket successful"<<std::endl;

    r = setsockopt(ss, SOL_SOCKET,SO_REUSEADDR, (void*)&opt,sizeof(opt));
    if (r == -1)
    {
        perror("setsockopt(listen)");
        return 0;
    }
    std::cout<<"[process infro]sockopt successful"<<std::endl;

    std::cout<<"?";
    err = bind(ss, (struct sockaddr*) &server_addr, sizeof( server_addr));
    std::cout<<"err";
    if(err < 0)
    {
        std::cout<<"[process infro]bind error"<<std::endl;
        return -1;
    }
    std::cout<<"[process infro]bind successful";


    err=listen(ss, BACKLOG);
    if(err <0)
    {
        std::cout<<"[process infro]listen error"<<std::endl;
        return -1;
    }
    std::cout<<"[process infro]listen successful";

    for( ; ; )
    {
        int addrlen = sizeof(struct sockaddr);

        sc = accept(ss, (struct sockaddr*)&client_addr, (socklen_t *)&addrlen);

        if(sc < 0)
        {
            continue;
        }

        pid =  fork();
        if (pid == 0)
        {
            close(ss);
            process_conn_server(sc);
        }
        else
        {
            close(sc);
        }
    }
    //opt=0;

    //setsockopt(ss,SOL_SOCKET,SO_REUSEADDR,(void*)&opt,sizeof(len));
}