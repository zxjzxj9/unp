
// Program to get nettime
// possible server (provided by NIST): 
// 2610:20:6F15:15::27
// use IPv6

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 255


int main(int argc,char **argv)
{
    int sockfd,n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in6 servaddr;

    if(argc != 2)
    {   
        printf("usage: a.out <IPaddress>\n");
        exit(0);
    }

    if((sockfd = socket(AF_INET6,SOCK_STREAM,0))<0)
    {
        printf("socket error\n");
        exit(-1);
    }

    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin6_family = AF_INET6;
    servaddr.sin6_port = htons(13);

    if(inet_pton(AF_INET6,argv[1],&servaddr.sin6_addr)<=0)
    {
        printf("inet_pton error for %s\n",argv[1]);
        exit(-1);
    }

    if(connect(sockfd,(struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    {
        printf("connect error \n");
        exit(-1);
    }

    while((n=read(sockfd,recvline,MAXLINE))>0)
    {
        recvline[n] = 0;
        if(fputs(recvline,stdout) == EOF)
        {
            printf("fputs error \n");
            exit(-1);
        }
    }

    if(n<0)
    {
        printf("read error \n");
        exit(-1);
    }

    return 0;
}
