#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 1024

typedef struct noeud{
	unsigned char lettre;
	struct noeud *filsg, *frered;
}Noeud, *Arbre;

/* Affiche les mots du lexique passé en paramètre en ordre alphabétique */
void afficherMots(Arbre a);

void ecrireMot(Arbre a, FILE *fichier);

/* Sauvegarde les mots du lexique entré en paramètre dans un fichier donc le nom est entré en paramètre */
void sauvegarderMots(Arbre a, char *nomOut);

/* Indique si le mot est présent dans le texte sous forme "present" ou "absent" */
int estPresent(Arbre a, const char *mot);

/* Alloue l'espace mémoire nécessaire pour un Noeud */
Noeud* allouerNoeud(char lettre);

/* Ajoute une branche à l'arbre */
void ajouterBranche(Arbre *a, char *mot);

/* Ajoute un mot passé en paramètre dans le lexique lui-même passé en paramètre */
void ajouterMot(Arbre *a, char *mot);

void afficherArbre(Arbre a);
