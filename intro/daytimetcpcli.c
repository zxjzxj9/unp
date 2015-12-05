//#include <linux/in.h>

// Program to get nettime
// possible server (provided by NIST): 
// 98.175.203.200

#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define MAXLINE 255

extern int err;

int main(int argc,char **argv)
{
    int sockfd,n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if(argc != 2)
    {   
        printf("usage: a.out <IPaddress>\n");
        exit(0);
    }

    if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)
    {
        printf("socket error\n");
        char * mesg = strerror(errno);
        printf("Mesg:%s\n",mesg); 
        exit(-1);
    }

    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);

    if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr)<=0)
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
