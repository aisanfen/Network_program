//
// Created by sanfen on 18-9-20.
//
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8010
#define MAXDATASIZE 100

int main(int argc,char *argv[])
{
    int socketfd;
    struct sockaddr_in server;
    struct sockaddr_in client;
    socklen_t len;
    int num;
    char buf[MAXDATASIZE];
    if((socketfd=socket(AF_INET,SOCK_DGRAM,0))==-1)
    {
        perror("Creating socket faild");
        _exit(1);
    }
    bzero(&server, sizeof(server));
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    int opt=SO_REUSEADDR;
    setsockopt(socketfd,SOL_SOCKET,SO_REUSEADDR,&opt, sizeof(opt));
    if(bind(socketfd,(struct sockaddr *)&server, sizeof(server))==-1)
    {
        perror("server bind error");
        _exit(1);
    }
    len= sizeof(client);
    while(1)
    {
        num=recvfrom(socketfd,buf,MAXDATASIZE,0,(struct sockaddr *)&client,&len);
        if(num<0)
        {
            perror("server recvfrom faild");
            _exit(1);
        }
        buf[num]='\0';
        printf("You got a message <%s> from client.\nIt's ip is %s,port is %d.\n",buf,inet_ntoa(client.sin_addr),htons(client.sin_port));
        sendto(socketfd,"Welcome! \n ",8,0,(struct sockaddr *)&client,len);
        if(!strcmp(buf,"bye"))
            break;
    }
    close(socketfd);
}
