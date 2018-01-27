#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <iostream>
using namespace std;


#define DATA "Hello, World!"

int main(int argc, char* argv[])
{
	string data;

	int sock;
	struct sockaddr_in server;
	struct hostent *hp;
	char buff[1024];


	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("Faild to create socket");
		exit(1);
	}

	server.sin_family = AF_INET;

    if (argv[1]){
        hp = gethostbyname(argv[1]);
    } else {
        hp = gethostbyname("localhost");
    }
	
	if(hp == 0){
		perror("gethostbyname failed");
		close(sock);
		exit(1);
	}

	memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
	server.sin_port = htons(5000);


	if(connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0)
	{
		perror("Connect failed");
		close(sock);
		exit(1);
	}

	if(send(sock, DATA, sizeof(DATA), 0) < 0)
	{
		perror("send failure");
		close(sock);
		exit(1);
	}

	return 0;
}
