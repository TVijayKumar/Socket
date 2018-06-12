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

int main(int argc, char *argv[])
{
	int sockfd,i,size;
	struct sockaddr_in cliadr;

	if(argc<3){
		printf("Use : client <server ip> <port>\n");
		return;
	}
	char serverIp[16]={'\0'};
	memcpy(&serverIp,argv[1],strlen(argv[1]));

	char port[6]={'\0'};
	memcpy(&port,argv[2],strlen(argv[2]));

	int portNum = atoi(port);
	printf("Connecting to server : %s:%d\n",serverIp,portNum);

	//create socket
	sockfd=socket(AF_INET,SOCK_STREAM,0);

	if(sockfd<0)
		error("sockt system call");
	cliadr.sin_family=AF_INET;
	cliadr.sin_port=portNum;
	cliadr.sin_addr.s_addr=inet_addr(serverIp);

	//connect to server
	connect(sockfd,(struct sockaddr *)&cliadr,sizeof(cliadr));
	
	char buff[50]="Hello all this is vijay\n";
	write(sockfd,buff,sizeof(buff));
	read(sockfd,&buff,50);
	printf("red from server : %s \n",buff);

	
}
