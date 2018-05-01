#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main()
{
	//Create socket
	int sockfd,newsockfd;
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
		error("socket system call");

	//Bind socket with server address
	struct sockaddr_in srvadr,cliadr;
	bzero(&srvadr,sizeof(srvadr));
	srvadr.sin_family=AF_INET;
	srvadr.sin_addr.s_addr=inet_addr("127.0.0.1");
	srvadr.sin_port=2005;

	if(bind(sockfd,(struct sockaddr *)&srvadr,sizeof(srvadr))<0)
		error("bind system call");

	int clilen=sizeof(cliadr);

	//listen for clints
	listen(sockfd,5);

	//Accept the client request.
	newsockfd=accept(sockfd,(struct sockaddr *)&cliadr,&clilen);
	if(newsockfd<0)
		perror("accept system call");

	printf("connected to client:%s\n",inet_ntoa(cliadr.sin_addr));

	char buff[50]={'\0'};
	int n=read(newsockfd,&buff,sizeof(buff));
	if(n<0)
		perror("read system call");

	printf("Red from client: %s",buff);
	write(newsockfd,"Helli clint\n",20);
	close(newsockfd);
	close(sockfd);
}

