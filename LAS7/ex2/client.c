#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "utils_v1.h"

#define SITEMAP "sitemap.txt"
#define PORT 80
#define MAX_LENGTH 255
#define MAX_IP_LENGTH 15
#define GET "GET"

char* getHostName(char* url) {
	char* hostname = malloc(strlen(url)*sizeof(char));
	if(hostname == NULL) return NULL;
	strcpy(hostname, url);
	hostname = strchr(hostname, '/')+2;
	strtok(hostname, "/");
}

int main(int argc, char const *argv[])
{
	int fd = sopen(SITEMAP, O_RDONLY, 0);
	char** siteMap = readFileToTable(fd);
	char* hostname = getHostName(*siteMap);
	if(hostname == NULL) {
		perror("malloc error");
		exit(1);
	}

	printf("Host: %s\n", hostname);

	char ip[MAX_IP_LENGTH];
	hostname_to_ip(hostname, &ip);

	printf("IP: %s\n", ip);

	while(*siteMap != NULL) {
		int sockfd = ssocket();
		sconnect(ip, PORT, sockfd);

		char request[MAX_LENGTH];
		sprintf(request, "%s %s HTTP/1.0\r\nHost:%s\r\n\r\n", GET, *siteMap, hostname);
		swrite(sockfd, &request, sizeof(request));

		printf("Request: \n%s\n", request);

		char filename[MAX_LENGTH];
		sprintf(filename, "pages/%s", strrchr(*siteMap, '/')+1);
		int filefd = sopen(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);

		char buf[MAX_LENGTH];
		while(sread(sockfd, buf, MAX_LENGTH) != 0) {
			swrite(filefd, buf, MAX_LENGTH);
		}
		*siteMap++;
	}
}