#if ! defined PLAYLIST_H_ 
#define _PLAYLIST_H_

#include <stdbool.h>
#include "track.h"


/// Définition de types

// TODO: définir le type Noeud
typedef struct Noeud {
	Track* track;
	struct Noeud* svt;
} Noeud;

// TODO: définir le type Playlist
typedef struct {
	Noeud* tete;
	Noeud* queue;
} Playlist;

/// Déclaration de fonctions

/** 
 * Initialise une playlist
 * PRE: /
 * POST: renvoie un pointeur vers une playliste vide
 */
Playlist* initPlaylist ();

/** 
 * Ajoute un track dans la playliste en queue de liste
 * PRE: p: une playlist
 *      t: pointeur non null vers track à ajouter
 * POST: renvoie vrai si t a été ajouté à la playlist p;
 *       faux sinon
 */
bool addTrack (Playlist* p, Track* t);

/** 
 * Fusionne les playlists p1 et p2 en conservant l'ordre des tracks et en 
 * enlevant les doublons. De plus les listes p1 et p2 sont vidées
 * PRE: p1, p2: pointeur non null vers les playlists triées
 * POST: renvoie une nouvelle playlist contenant les éléments des playlist p1 et p2
 *        p1 et p2 sont vides (la tête et la queue sont nulls).
 *        En cas de doublon, la mémoire de celui qui n'est pas repris dans la liste a été libérée.
 */
Playlist* destructiveMerge (Playlist* p1, Playlist* p2);

/** 
 * Affiche le contenu d'une playlist
 * PRE: p: pointeur non null vers la playtlist
 * POST: affiche le contenu de la playlist
 */
void printPlaylist (Playlist* p);

#endif  // _PLAYLIST_H_
