#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "messages.h"
#include "utils_v1.h"

/**
 * PRE: serverIP : a valid IP address
 *      serverPort: a valid port number
 * POST: on success, connects a client socket to serverIP:serverPort
 *       on failure, displays error cause and quits the program
 * RES: return socket file descriptor
 */
int initSocketClient(char * serverIP, int serverPort)
{
  int sockfd = ssocket();
  sconnect(serverIP, serverPort, sockfd);
  return sockfd;
}

int main(int argc, char **argv)
{
  /* retrieve player name */
  printf("Bienvenue dans le programe d'inscription au serveur de jeu\n");
  printf("Pour participer entrez votre nom :\n");
  StructMessage msg;
  int ret = sread(0, msg.messageText, MAX_PSEUDO);
  msg.messageText[ret - 1] = '\0';
  msg.code = INSCRIPTION_REQUEST;

  int sockfd = initSocketClient(SERVER_IP, SERVER_PORT);
  swrite(sockfd, &msg, sizeof(msg));

  /* wait server response */
  sread(sockfd, &msg, sizeof(msg));

  if (msg.code == INSCRIPTION_OK)
  {
    printf("Réponse du serveur : Inscription acceptée\n");
  }
  else if (msg.code == INSCRIPTION_KO)
  {
    printf("Réponse du serveur : Inscription refusée\n");
  }

  char buf[MESSAGE_SIZE];
  /* wait server response */
  sread(sockfd, buf, MESSAGE_SIZE);
  printf("%s\n", buf);

  char play;
  sread(0, &play, 1);
  swrite(sockfd, &play, 1);

  sclose(sockfd);
  return 0;
}
