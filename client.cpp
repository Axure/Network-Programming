//
// Created by 郑虎 on 15 年 五月. 2..
//

#include "client.h"
using namespace std;
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <time.h>
#include <arpa/inet.h>
#include <fstream.h>

#define PORT 8888
#define DEST_IP "127.0.0.1"

void process_conn_client(int s)
{
    ssize_t size = 0;
    char buffer[1024];

    //read from the file to be sent
    fstream outfile("programm.txt",ios::in|ios::out);

    if (outfile.fail())
    {
        printf("[process infro]cannot open the file to be sent\n");
        return ;
    }
    printf("[process infro]successfully open the file to be sent\n");

    while(!outfile.eof())
    {

        outfile.getline(buffer,1025,'\n');
        write(s,buffer,1024);
        size = read(s, buffer, 1024);
        if(size = 0)
        {
            return ;
        }
        //write to the server
        write(s,buffer,size);

        //get response from the server
        size=read(s,buffer,1024);
        write(1,buffer,size);

    }
    outfile.close();    //关闭文件
}

int main(int argc,char *argv[])
{
    int s;
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(DEST_IP);
    server_addr.sin_port =  htons(PORT);

    s = socket(AF_INET, SOCK_STREAM, 0);
    if(s < 0)
    {
        cout<<"[process infro]socke error"<<endl;
        return -1;
    }
    cout<<"[process infro] socket built successfully\n";



    //inet_pton(AF_INET, argv[1], &server_addr.sin_addr);


    connect(s, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));
    cout<<"[process infor] connected\n";
    process_conn_client(s);

    close(s);

    return 0;
}