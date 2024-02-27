#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "track.h"


Track* initTrack (char* artiste, char* titre, int duree) {
    // TODO
    struct Track* t = malloc(sizeof(Track));
    strncpy(t->artiste, artiste, ARTISTE_LENGTH);
    strncpy(t->titre, titre, TITLE_LENGTH);
    t->duree = duree;
    return t;
}

int compareTrack (Track* t1, Track* t2) {
    // TODO
    int i = strcmp((*t1)->artiste, (*t2)->artiste);
    if(i != 0) return i;
    i = strcmp((*t1)->titre, (*t2)->titre);
    if(i != 0) return i;
    return (*t1)->duree - (*t2)->duree;
}

void printTrack (Track *t) {
    printf("%s - %s - %d", t->artiste, t->titre, t->duree);
}

