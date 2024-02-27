#if ! defined _TRACK_H_ 
#define _TRACK_H_

#define ARTISTE_LENGTH 80
#define TITLE_LENGTH 80


/// Définition de types

// TODO: définir le type Track
typedef struct {
	char artiste[ARTISTE_LENGTH+1];
	char titre[TITLE_LENGTH+1];
	int duree;
} Track;

/// Déclaration de fonctions

/** 
 * Initialise une track
 * PRE: ariste, titre chaines de caractere non null
 * POST: renvoie un pointeur vers une Track contenant la duree et la copie 
 *       des chaines de caractères passées en paramètre ou NULL si la 
 *       création n'a pas pû être faite.
 *       
 */
Track* initTrack (char* artiste, char* titre, int duree);


/** 
 * Compare deux tracks
 * PRE: t1, t2 pointeurs non null vers deux tracks
 * POST: compare les artistes puis s'ils sont égaux les titres puis
 *       s'ils sont égaux les durées et renvoie
 *          - un nombre négatif si t1 et plus petit que 2
 *          - zéro si t1 et t2 sont structurellement égaux
 *          - un nombre positif si t1 est plus grand que t2
 */
int compareTrack (Track* t1, Track* t2);


/** 
 * Affiche uen track
 * PRE: t pointeur non null vers un track
 * POST: affiche la track
 */
void printTrack (Track* t);

#endif