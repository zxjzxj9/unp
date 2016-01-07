// Server to provide echo service (port 7)


#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#define MAXLINE 255
#define WPORT 7 // define work port
#define LISTENQ 5 // max listen queue

int str_echo(int sockfd)
{
    ssize_t n;
    char buff[MAXLINE];
    do{ 
        while( (n = read(sockfd,buff,MAXLINE)) > 0)
        {
             write(sockfd,buff,n);
        }
    } while(n < 0 && errno == EINTR);
    
    return 0;
}


int main(int argc,char** argv)
{

    int listenfd, connfd;
    socklen_t len;
    pid_t pid;
    struct sockaddr_in servaddr,cliaddr;
    char buff[MAXLINE];

    listenfd = socket(AF_INET,SOCK_STREAM,0);
    
    bzero(&servaddr,sizeof(servaddr));
    bzero(&cliaddr,sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(WPORT);

    bind(listenfd, (struct sockaddr*) &servaddr,sizeof(servaddr));
    listen(listenfd,LISTENQ);

    for(;;)
    {
        connfd = accept(listenfd, (struct sockaddr*) &cliaddr , &len);
        printf("connection form %s, port %d\n", inet_ntop(AF_INET,&cliaddr.sin_addr,buff,sizeof(buff)),
                                                ntohs(cliaddr.sin_port));
        if((pid=fork())==0) // if child process
        {
            close(listenfd);
            str_echo(connfd);   
            close(connfd);
            exit(0);
        }
        close(connfd);
    } 

    return 0;
}
