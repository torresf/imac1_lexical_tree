#include "arbre.h"

void afficherMots(Arbre a) {
    static char buffer[TAILLE_MAX]; /* Buffer servant à stocker les mots à écrire */
    static int cur = 0; /* Case courante à remplir */
    if (a != NULL){
        buffer[cur++]=a->lettre;
        if (a->lettre == '\0')
            printf("%s \n", buffer);
        else 
            afficherMots(a->filsg);
        cur--;
        if (a->frered != NULL)
            afficherMots(a->frered);
    }
    else 
        printf("Rien à afficher --> L'arbre est vide\n");
}

void ecrireMot(Arbre a, FILE *fichier) {
    static char buffer[TAILLE_MAX]; /* Buffer servant à stocker les mots à écrire */
        static int cur = 0; /* Case courante à remplir */
        if (a != NULL) {
            buffer[cur++]=a->lettre;
            if (a->lettre == '\0')
                fprintf(fichier, "%s ", buffer);
            else 
                ecrireMot(a->filsg, fichier);
            cur--;
            if (a->frered != NULL)
                ecrireMot(a->frered, fichier);
        }
        else 
            fprintf(fichier, "Rien à afficher --> L'arbre est vide\n");
}

void sauvegarderMots(Arbre a, char *nomOut) {
   	FILE *fichier;
   	char nomOutExt[TAILLE_MAX];
   	sprintf(nomOutExt, "%s.L", nomOut);
   	fichier = fopen(nomOutExt, "w+");
   	if (fichier != NULL) {
   	    ecrireMot(a, fichier);
       	fclose(fichier);
   	} else
   	    printf("Erreur lors de l'ouverture du fichier : Nom du fichier invalide ou non communiqué\n");
}


int estPresent(Arbre a, const char *mot) {
    if (a == NULL)
        return 0;
    if (*mot < a->lettre)
        return 0;
    if (*mot==a->lettre){
        if (*mot == '\0')
            return 1;
        return estPresent(a->filsg, mot+1);
    }
    return estPresent(a->frered, mot);
}

Noeud *allouerNoeud(char lettre) {
    Noeud *tmp;
	tmp = (Noeud*) malloc(sizeof(Noeud));
	if (tmp != NULL){
		tmp->lettre = lettre;
		tmp->filsg = NULL;
		tmp->frered = NULL;
		return tmp;
	}
	exit(EXIT_FAILURE);
}

void ajouterBranche(Arbre *a, char *mot) {
    *a = allouerNoeud(*mot);
    if (*a != NULL) {
        if (*mot != '\0') 
            ajouterBranche(&((*a)->filsg), mot+1);
    }
}

void ajouterMot(Arbre *a, char *mot) {
    if (*a == NULL)
        ajouterBranche(a, mot);
    else {
        if ((*a)->lettre < *mot)
            ajouterMot(&((*a)->frered), mot);
        else {
            if (((*a)->lettre == *mot) && (*mot != '\0'))
                ajouterMot(&((*a)->filsg), mot+1);
            else {
                if (*mot != '\0') {
                    Arbre tmp = NULL;
                    ajouterBranche(&tmp, mot);
                    tmp->frered = *a;
                    *a = tmp;
                }
            }
        }
    }
}

void sauvegardeArbre(Arbre a){
    if (a!=NULL){
        if (a->lettre != '\0')
		printf("%c\n", a->lettre);
		sauvegardeArbre(a->filsg);
		sauvegardeArbre(a->frered);
	}
}