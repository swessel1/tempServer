#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <iostream>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
int sockfd, newsockfd, portno;
int passValue;
char* pass;
socklen_t clilen;
char buffer[256];
struct sockaddr_in serv_addr, cli_addr;
int n;
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0)
    error("ERROR opening socket");
bzero((char *) &serv_addr, sizeof(serv_addr));
portno = 6001;
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(portno);

if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    error("ERROR on binding");
while(1)
{
  listen(sockfd,4);
  bzero((char *) &cli_addr, sizeof(cli_addr));
  clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
  if (newsockfd < 0)
    error("ERROR on accept");
  bzero(buffer,256);
  while(1)
  {
    n = read(newsockfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");

    //this is where we handle the requests
    
    //DO NOT forget to break out of this loop upon errors or window closes
        //otherwise the server won't move on to the next client
  }

  close(newsockfd);
  close(sockfd);
  
  return 0;
}
