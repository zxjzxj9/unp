// Server to provide daytime service


#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#define MAXLINE 255
#define LISTENQ 5 // max listen queue


int main(int argc,char **argv)
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    assert((listenfd = socket(AF_INET,SOCK_STREAM,0))>0);
    //if((listenfd = socket(AF_INET,SOCK_STREAM,0))<0)
    //{
    //    printf("socket error\n");
    //    exit(-1);
    //}
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);
        
    assert(bind(listenfd, (struct sockaddr*) &servaddr,sizeof(servaddr))==0);
    assert(listen(listenfd,LISTENQ)==0);

    while(1)
    {
        assert((connfd = accept(listenfd, (struct sockaddr*) NULL, NULL))>0);
        
        ticks = time(NULL);

        snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
        assert(write(connfd,buff,strlen(buff)) > 0);

        assert(close(connfd) >= 0);
    
    }

    return 0;
}
