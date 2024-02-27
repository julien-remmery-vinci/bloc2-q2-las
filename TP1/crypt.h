#ifndef _CRYPT_H_
#define _CRYPT_H_

/**Crypte une chaine de caracteres
 * PRE  : une chaine de caracteres non cryptée
 * RES  : La chaine de caracteres cryptée
 */
char* encrypt(char* msg);

/**Decrypte une chaine de caracteres
 * PRE  : une chaine de caracteres cryptée
 * RES  : La chaine de caracteres décryptée
 */
char* decrypt(char* msg);

#endif