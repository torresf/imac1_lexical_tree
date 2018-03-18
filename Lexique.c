#include "arbre.h"

int main(int argc, char const *argv[])
{
	/* Test
	Arbre test;
	ajouterMot(&test, "ce");
	ajouterMot(&test, "ces");
	ajouterMot(&test, "des");
	ajouterMot(&test, "le");
	ajouterMot(&test, "les");
	ajouterMot(&test, "lettre");
	ajouterMot(&test, "mes");
	ajouterMot(&test, "mettre");
	ajouterMot(&test, "avion");
	ajouterMot(&test, "zebre");
	ajouterMot(&test, "zèbre");
	ajouterMot(&test, "feuille");
	ajouterMot(&test, "feuille");
	afficherMots(test);
	sauvegarderMots(test, "out"); */
	
	Arbre a;
	FILE* fichier = NULL;
	char fichier_in[TAILLE_MAX];
	char mot_a_chercher[TAILLE_MAX] = {'\0'};
	int mode = 0;
	
	if (argv[1] != NULL){
		if (strcmp(argv[1], "-l") == 0) {
			mode = 1;
			strcpy(fichier_in, argv[2]);
		} 
		else if (strcmp(argv[1], "-s") == 0) {
			mode = 2;
			strcpy(fichier_in, argv[2]);
		}
		else if (strcmp(argv[1], "-r") == 0) {
			strcpy(mot_a_chercher, argv[2]);
			strcpy(fichier_in, argv[3]);
			mode = 3;
		}
		else if (strcmp(argv[1], "-S") == 0) {
			strcpy(fichier_in, argv[2]);
			mode = 4;
		}
		else {
			strcpy(fichier_in, argv[1]);
			printf("Bienvenue dans le gestionnaire d'arbre lexical.\n");
			printf("Que souhaitez-vous faire ?\n");
			/* Choix du mode */
			while (mode < 1 || mode > 4) {
				printf(" 1: Afficher le Lexique \n 2: Sauvegarder le lexique \n 3: Vérifier si un mot est présent \n 4: sauvegarder au format .DICO\n");
				scanf(" %d", &mode);
			}
		}
		/* Lecture d'un fichier */
		char tmp[TAILLE_MAX];
		fichier = fopen(fichier_in, "r+");
		if (fichier != NULL) {
			while (fscanf(fichier, "%s", tmp) != EOF) {
	   			ajouterMot(&a, tmp);
	   		}
	    	fclose(fichier);
		} else {
	        printf("Impossible d'ouvrir le fichier.\n");
	    }
	} else {
		printf("Traitement impossible. Veuillez entrer le nom du fichier à traiter.\n");
	}
	
	switch (mode) {
		case 1:
			afficherMots(a);
			break;
		case 2:
			sauvegarderMots(a, fichier_in);
			break;
		case 3:
			while (strlen(mot_a_chercher) == 0){
				printf("Entrez le mot à rechercher : \n");
				scanf(" %s", mot_a_chercher);
			}
			if (estPresent(a, mot_a_chercher) == 1)
				printf("present\n");
			else 
				printf("absent\n");
			break;
		case 4:
			afficherArbre(a);
			printf("\n");
			break;
		default:
			break;
	}
	return 0;
}