#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 1024
#define TAILLE_MAX_MOT 51

typedef struct noeud{
	unsigned char lettre;
	struct noeud *filsg, *frered;
}Noeud, *Arbre;

/* Affiche les mots du lexique passé en paramètre en ordre alphabétique */
void afficherMots(Arbre a);

/* Fonction récursive qui écrit les mots de l'arbre passé en paramètre dans le fichier lui aussi passé en paramètre */
void ecrireMots(Arbre a, FILE *fichier);

/* Sauvegarde les mots du lexique entré en paramètre dans un fichier donc le nom est entré en paramètre */
void sauvegarderMots(Arbre a, char *nomOut);

/* Indique si le mot est présent dans le texte sous forme "present" ou "absent" */
int estPresent(Arbre a, const char *mot);

/* Alloue l'espace mémoire nécessaire pour un Noeud et l'initialise avec la lettre passée en paramètre et ses fils/frére à NULL */
Noeud* allouerNoeud(char lettre);

/* Ajoute une branche (symbolisée par un mot passé en paramètre) à l'arbre lui aussi passé en paramètre */
void ajouterBranche(Arbre *a, char *mot);

/* Ajoute un mot passé en paramètre dans le lexique lui-même passé en paramètre */
void ajouterMot(Arbre *a, char *mot);

/* Affiche dans le terminal l'arbre passé en paramètre selon la syntaxe du sujet (format DICO) */
void afficherArbre(Arbre a);

/* Fonction récursive qui écrit les caractères de l'arbre passé en paramètre dans le fichier lui aussi passé en paramètre selon la syntaxe du sujet (format DICO) */
void ecrireDICO(Arbre a, FILE *fichier);

/* Fonction qui sauvegarde l'arbre passé en paramètre dans un fichier dont le nom sera celui passé en paramètre suivi de l'extension .DICO */
void sauvegarderArbre(Arbre a, char *nomOut);

/* Création d'un arbre à partir d'un fichier .DICO. Retourne l'arbre créé */
Arbre chargerArbre(FILE *fichier_dico);

/* Création arbre dans un fichier DOT */
void creerDot(Arbre a, char *nomFichierIn);
void ecrireDebut(FILE* stream);
void ecrireFin(FILE* stream);
void ecrireArbre(FILE* stream, Arbre a);