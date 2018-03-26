#include "arbre.h"

/* Affiche les mots du lexique passé en paramètre en ordre alphabétique */
void afficherMots(Arbre a) {
    static char buffer[TAILLE_MAX_MOT]; /* Buffer servant à stocker les mots à écrire */
    static int cur = 0; /* Case courante à remplir */
    if (a != NULL){
        buffer[cur++]=a->lettre;
        if (a->lettre == '\0'){
            printf("%s \n", buffer);
        }
        else 
            afficherMots(a->filsg);
        cur--;
        if (a->frered != NULL)
            afficherMots(a->frered);
    }
    else 
        printf("Rien à afficher --> L'arbre est vide\n");
}

/* Fonction récursive qui écrit les mots de l'arbre passé en paramètre dans le fichier lui aussi passé en paramètre */
void ecrireMots(Arbre a, FILE *fichier) {
    static char buffer[TAILLE_MAX_MOT]; /* Buffer servant à stocker les mots à écrire */
        static int cur = 0; /* Case courante à remplir */
        if (a != NULL) {
            buffer[cur++]=a->lettre;
            if (a->lettre == '\0') {
                if (strcmp(buffer, "") != 0)
                    fprintf(fichier, "%s ", buffer);
            } else
                ecrireMots(a->filsg, fichier);
            cur--;
            if (a->frered != NULL)
                ecrireMots(a->frered, fichier);
        } else
            fprintf(fichier, "Rien à afficher --> L'arbre est vide\n");
}

/* Sauvegarde les mots du lexique entré en paramètre dans un fichier donc le nom est entré en paramètre */
void sauvegarderMots(Arbre a, char *nomOut) {
   	FILE *fichier;
   	char nomOutExt[TAILLE_MAX];
   	sprintf(nomOutExt, "%s.L", nomOut);
   	fichier = fopen(nomOutExt, "w+");
   	if (fichier != NULL) {
   	    ecrireMots(a, fichier);
       	fclose(fichier);
   	} else
   	    printf("Erreur lors de l'ouverture du fichier : Nom du fichier invalide ou non communiqué\n");
}


/* Indique si le mot est présent dans le texte sous forme "present" ou "absent" */
int estPresent(Arbre a, const char *mot) {
    if (a == NULL)
        return 0;
    if (*mot < a->lettre)
        return 0;
    if (*mot == a->lettre){
        if (*mot == '\0')
            return 1;
        return estPresent(a->filsg, mot+1);
    }
    return estPresent(a->frered, mot);
}

/* Alloue l'espace mémoire nécessaire pour un Noeud et l'initialise avec la lettre passée en paramètre et ses fils/frére à NULL */
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

/* LE PROBLEME DU CARACTERE \0 AU DEBUT VIENS DE LA CREATION DE L'ARBRE !!!!!!!!!!!!! */

/* Ajoute une branche (symbolisée par un mot passé en paramètre) à l'arbre lui aussi passé en paramètre */
void ajouterBranche(Arbre *a, char *mot) {
    *a = allouerNoeud(*mot);
    if (*a != NULL && *mot != '\0') {
        ajouterBranche(&((*a)->filsg), mot+1);
    }
}

/* Ajoute un mot passé en paramètre dans le lexique lui-même passé en paramètre */
void ajouterMot(Arbre *a, char *mot) {
    if (*a == NULL) {
        ajouterBranche(a, mot);
    } else {
        if ((*a)->lettre < *mot)
            ajouterMot(&((*a)->frered), mot);
        else {
            if (((*a)->lettre == *mot) && (*mot != '\0')) {
                ajouterMot(&((*a)->filsg), mot+1);
            } else {
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

/* Affiche dans le terminal l'arbre passé en paramètre selon la syntaxe du sujet (format DICO) */
void afficherArbre(Arbre a) {
    if (a!=NULL) {
        if (a->lettre != '\0'){
		    printf("%c", a->lettre);
		    afficherArbre(a->filsg);
        } else 
            printf(" ");
        if (a->frered == NULL)
            printf("\n");
		afficherArbre(a->frered);
	}
}

/* Fonction récursive qui écrit les caractères de l'arbre passé en paramètre dans le fichier lui aussi passé en paramètre selon la syntaxe du sujet */
void ecrireDICO(Arbre a, FILE *fichier){
    if (a!=NULL){
        if (a->lettre != '\0'){
		    fprintf(fichier, "%c", a->lettre);
		    ecrireDICO(a->filsg, fichier);
        } else 
            fprintf(fichier, " ");
        if (a->frered == NULL)
            fprintf(fichier ,"\n");
		ecrireDICO(a->frered, fichier);
	}
}

/* Fonction qui sauvegarde l'arbre passé en paramètre dans un fichier dont le nom sera celui passé en paramètre suivi de l'extension .DICO */
void sauvegarderArbre(Arbre a, char *nomOut){
    FILE *fichier;
   	char nomOutExt[TAILLE_MAX];
   	sprintf(nomOutExt, "%s.DICO", nomOut);
   	fichier = fopen(nomOutExt, "w+");
   	if (fichier != NULL) {
   	    ecrireDICO(a, fichier);
       	fclose(fichier);
   	} else
   	    printf("Erreur lors de l'ouverture du fichier : Nom du fichier invalide ou non communiqué\n");
}


/* Création d'un arbre à partir d'un fichier .DICO. Retourne l'arbre créé */
Arbre chargerArbre(FILE *fichier_dico) {
    Arbre a = NULL;
	if (fichier_dico != NULL) {
	    char ligne[TAILLE_MAX];
        char buf[TAILLE_MAX_MOT];
        int j = 0;
        while (fgets(ligne, sizeof ligne, fichier_dico) != NULL)
        {
            int i = 0;
            while (ligne[i] != '\n') {
                if (ligne[i] == ' ') {
                    ajouterMot(&a, buf);
                } else {
                    buf[j] = ligne[i];
                    j++;
                }
                i++;
            }
            buf[j] = '\0';
            j--;
        }
        fclose (fichier_dico);
	}
    return a;
}

/* Nettoyage de la mémoire allouée par les éléments de l'arbre */
void libererArbre(Arbre *a) {
    Arbre tmp = *a;
    if(*a == NULL)
        return;
    if(tmp->filsg) 
        libererArbre(&tmp->filsg);
    if(tmp->frered)
        libererArbre(&tmp->frered);
    free(tmp);
    *a = NULL;
}

/* Création arbre dans un fichier DOT */
void creerDot(Arbre a, char *nomFichierIn){
	FILE *out;
	char name[TAILLE_MAX];
	sprintf(name,"%s.dot", nomFichierIn);
	out=fopen(name,"w"); /* suppose OK*/
	ecrireDebut(out);
	ecrireArbre(out,a);
	ecrireFin(out);
	fclose(out);
}
void ecrireDebut(FILE* stream){
	fprintf(stream, "digraph arbre {\nnode [shape=record, height=.1]\n");
	fprintf(stream, "edge [tailclip=false, arrowtail=dot, dir=both];\n\n");
}
void ecrireFin(FILE* stream){
	fprintf(stream, "\n}\n");
}
void ecrireArbre(FILE* stream, Arbre a){
	if (a != NULL){
	    if (a->lettre == '\0')
	        fprintf(stream, "n%p [label=\"{<lettre> %s |<here>}| <droit>\";]\n", a, "\\\\0");
		else
		    fprintf(stream, "n%p [label=\"{<lettre> %c |<here>}| <droit>\";]\n", a, a->lettre);
		if (a->filsg != NULL){
			fprintf(stream, "n%p:here -> n%p:lettre;\n", a, a->filsg);
			ecrireArbre(stream, a->filsg);
		}
		if (a->frered != NULL){
			fprintf(stream, "n%p:droit:c -> n%p:lettre;\n", a, a->frered);
			ecrireArbre(stream, a->frered);
		}
	}
}