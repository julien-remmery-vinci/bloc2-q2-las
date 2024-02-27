#include <stdlib.h>
#include <stdio.h>

#include "playlist.h"


Playlist* initPlaylist () {
    // TODO
    struct Playlist* p = (Playlist*) malloc(sizeof(Playlist));
    p->tete = NULL;
    p->queue = NULL;
    return p;
}


bool addTrack (Playlist* p, Track* t) {
    // TODO
    if(p == NULL || t == NULL) return false;
    struct Noeud* n = (Noeud*) malloc(sizeof(Neoud));
    n->track = t;
    n->svt = NULL;
    (*p)->queue = n;
    return true;
}


Playlist* destructiveMerge (Playlist* p1, Playlist* p2) {
    // TODO
}


/** 
 * Affiche le contenu d'une playlist
 * PRE: p: pointeur non null vers la playtlist
 * POST: affiche le contenu de la playlist
 */
void printPlaylist (Playlist* p) {
    Noeud *bal = p->tete;
    int trackCnt = 0;
    while (bal != NULL) {
        printf("%d ", ++trackCnt);
        printTrack(bal->track);
        printf("\n");
        bal = bal->svt;
    }
    if (trackCnt == 0)
        printf("/\n");
}

