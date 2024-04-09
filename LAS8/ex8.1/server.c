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

#define MAX_PLAYERS 2
#define BACKLOG 5

typedef struct Player
{
  char pseudo[MAX_PSEUDO];
  int sockfd;
} Player;

volatile sig_atomic_t inscription = 1;

void alarmHandler(int sig) {
  inscription = 0;
}

/**
 * PRE:  serverPort: a valid port number
 * POST: on success, binds a socket to 0.0.0.0:serverPort and listens to it ;
 *       on failure, displays error cause and quits the program
 * RES: return socket file descriptor
 */
int initSocketServer(int serverPort)
{
  int sockfd = ssocket();

  /* no socket error */

  sbind(serverPort, sockfd);

  /* no bind error */
  slisten(sockfd, BACKLOG);

  /* no listen error */
  return sockfd;
}

int main(int argc, char **argv)
{
  int nbPlayers = 0;
  StructMessage msg;
  Player tabPlayers[MAX_PLAYERS];

  ssigaction(SIGALRM, alarmHandler);

  int sockfd = initSocketServer(SERVER_PORT);
  printf("Le serveur tourne sur le port : %i \n", SERVER_PORT);

  // setsockopt -> to avoid Address Already in Use
  int option = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));

  struct pollfd fds[1024];
  int nbSockfd = 0;

  while (nbPlayers < 2 && inscription)
  {
    alarm(15);
    int newsockfd = accept(sockfd, NULL, NULL);

    sread(newsockfd, &msg, sizeof(msg));

    printf("Inscription demandée par le joueur : %s\n", msg.messageText);
    if (nbPlayers < MAX_PLAYERS)
    {
      msg.code = INSCRIPTION_OK;
      strcpy(tabPlayers[nbPlayers].pseudo, msg.messageText);
      tabPlayers[nbPlayers].sockfd = newsockfd;
      nbPlayers++;
      if (nbPlayers == MAX_PLAYERS)
        alarm(0);

      fds[nbSockfd].fd = newsockfd;
      fds[nbSockfd].events = POLLIN;
      nbSockfd++;
    }
    else
    {
      msg.code = INSCRIPTION_KO;
    }

    nwrite(newsockfd, &msg, sizeof(msg));
    printf("Nb Inscriptions : %i\n", nbPlayers);
  }

  printf("FIN DES INSCRIPTIONS\n");
  printf("Joueur '%s' inscrit\n", tabPlayers[0].pseudo);
  printf("Joueur '%s' inscrit\n", tabPlayers[1].pseudo);

  if(nbPlayers < 2) {
    printf("Pas assez de joueurs inscrits.%d/%d\n", nbPlayers, MAX_PLAYERS);
    exit(0);
  }

  printf("LE JEU COMMENCE\n");

  for (int i = 0; i < nbSockfd; ++i)
  {
    char* play = "Envoyer P pour papier, C pour ciseaux, R pour pierre\n";
    nwrite(tabPlayers[i].sockfd, play, strlen(play));
  }

  char play[2] = {0};

  while(1) {
    spoll(fds, nbSockfd, 1);

    for (int i = 0; i < nbSockfd; i++)
    {
      if (fds[i].revents & POLLIN)
      {
        sread(fds[i].fd, &play[i], sizeof(char));

        printf("%s joue %c\n", tabPlayers[i].pseudo, play[i]);

        sclose(fds[i].fd);
      }
    }
    if(play[0] != 0 && play[1] != 0) break;
  }

  if(play[0] == 'R' && play[1] == 'C') {
  }
  else if(play[0] == 'P' && play[1] == 'R') {
    printf("%s a gagné\n", tabPlayers[0].pseudo);
  }
  else if(play[0] == 'C' && play[1] == 'P') {
    printf("%s a gagné\n", tabPlayers[0].pseudo);
  }
  else if(play[1] == 'R' && play[0] == 'C') {
    printf("%s a gagné\n", tabPlayers[1].pseudo);
  }
  else if(play[1] == 'P' && play[0] == 'R') {
    printf("%s a gagné\n", tabPlayers[1].pseudo);
  }
  else if(play[1] == 'C' && play[0] == 'P') {
    printf("%s a gagné\n", tabPlayers[1].pseudo);
  }
  else if(play[0] == play[1]){
    printf("égalité\n");
  }

  sclose(sockfd);
}
