//
// Created by sanfen on 18-9-15.
//

#include<stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netdb.h>

#define PORT 8888
#define MAXDATASIZE 100
int main(int argc,char *argv[])
{
    int socketfd,num;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in server;

    if(argc!=2)
    {
        printf("Usage:%s<IP Address>\n",argv[0]);
        _exit(1);
    }
    if((he=gethostbyname(argv[1]))==NULL)
    {
        perror("gethostbyname() error\n");
        _exit(1);
    }
    if((socketfd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        perror("socket() error\n");
        _exit(1);
    }
    bzero(&server, sizeof(server));
    server.sin_family=AF_INET;
    server.sin_port=htons(PORT);
    server.sin_addr= *((struct in_addr *)he->h_addr);
    if(connect(socketfd,(struct sockaddr *)&server, sizeof(server))==-1)
    {
        perror("connect() error");
        _exit(1);
    }
    if((num=recv(socketfd,buf,MAXDATASIZE,0))==-1)
    {
        perror("recv() error\n");
        _exit(1);
    }
    buf[num-1]='\0';
    printf("server message:%s\n",buf);
    close(socketfd);
    return 0;

}
