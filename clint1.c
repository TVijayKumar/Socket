#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<string.h>

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

main()
{
	int sockfd,i,size;
	struct sockaddr_in cliadr;

	//create socket
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	if(sockfd<0)
		error("sockt system call");
	cliadr.sin_family=AF_INET;
	cliadr.sin_port=2005;
	cliadr.sin_addr.s_addr=inet_addr("127.0.0.1");

	//connect to server
	connect(sockfd,(struct sockaddr *)&cliadr,sizeof(cliadr));
	
	char buff[50]="Hello all this is vijay\n";
	write(sockfd,buff,sizeof(buff));
	read(sockfd,&buff,50);
	printf("red from server : %s \n",buff);

	
}
