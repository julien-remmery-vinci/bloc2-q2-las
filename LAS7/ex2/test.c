#include "utils_v1.h"
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
	struct hostent *he = gethostbyname("ochoquet.be");
	if(he==NULL) perror("gethostbyname");
	struct in_addr **addr_list = (struct in_addr **) he->h_addr_list;
	if(addr_list[0] == NULL) perror("No address found");
	char *adr = inet_ntoa(*addr_list[0]);
  	if(adr == 0) perror("PRB inet_ntoa");
  	printf("%s\n", adr);
}