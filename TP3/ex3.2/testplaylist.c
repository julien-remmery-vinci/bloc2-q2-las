#include <stdlib.h>
#include <stdio.h>

#include "playlist.h"

int main(int argc, char **argv)
{
	Track *t1 = initTrack("Eminem", "Venom", 269);
	Track *t2 = initTrack("Happy Mondays", "Loose Fit", 257) ;
	Track *t3 = initTrack("Karl Biscuit", "La Morte", 236);
	Track *t4 = initTrack("Panda Dub", "Shankara", 403);
	Track *t5 = initTrack("Peter Tosh", "Equal Rights", 360);
	Track *t6 = initTrack("Peter Tosh", "Equal Rights", 360);
	Track *t7 = initTrack("Yves Simon", "Amazoniaque", 260);

    Playlist *p1 = initPlaylist();
    if (p1 == NULL) {
        printf("Probl création liste p1");
        exit(1);
    }

    // Test playlist vide
    printf("\nListe vide:\n");
    printPlaylist(p1);

    // Test ajout
    printf("\nListe 1:\n");
    addTrack(p1, t2);
    addTrack(p1, t4);
    addTrack(p1, t5);
    addTrack(p1, t7);

    printPlaylist(p1);

    // Test fusion
    Playlist *p2 = initPlaylist();
    if (p2 == NULL) {
        printf("Probl création liste p2");
        exit(1);
    }

    addTrack(p2, t1);
    addTrack(p2, t3);
    addTrack(p2, t6);
    printf("\nListe 2:\n");
    printPlaylist(p2);

    Playlist *mergedList = destructiveMerge(p1, p2);
    printf("\nListe fusionnée:\n");
    printPlaylist(mergedList);

    printf("\nListes vidées:\n");
    printPlaylist(p1);
    printPlaylist(p2);
}