#include "arbre.h"

int main(int argc, char const *argv[])
{
	/* Déclaration et Initialisation des variables */
	Arbre a = NULL;
	FILE* fichier = NULL;
	char fichier_in[TAILLE_MAX];
	char mot_a_chercher[TAILLE_MAX_MOT] = {'\0'};
	int mode = 0;
	
	/* Prise en compte des options */
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
			/* Affichage du menu */
			printf("Bienvenue dans le gestionnaire d'arbre lexical.\n");
			printf("Que souhaitez-vous faire ?\n");
			/* Choix de la fonctionnalité */
			while (mode < 1 || mode > 4) {
				printf(" 1: Afficher le lexique \n 2: Sauvegarder le lexique \n 3: Vérifier si un mot est présent \n 4: Sauvegarder au format .DICO\n");
				scanf(" %d", &mode);
			}
		}
		
		/* Test de connexion avec le fichier sprintf("%s.DICO,fichier_in) auquel cas on recréer l'arbre à partir du fichier et on l'utilise */
		char fichier_dico_name[TAILLE_MAX];
		sprintf(fichier_dico_name, "%s.DICO", fichier_in);
		FILE *fichier_dico = fopen(fichier_dico_name, "r+");
		if (fichier_dico != NULL && mode != 4) {
			printf("Le fichier DICO existe déjà. Création de l'arbre à partir du fichier.\n");
			a = chargerArbre(fichier_dico);
		} else {
			/* Lecture d'un fichier */
			char tmp[TAILLE_MAX_MOT];
			fichier = fopen(fichier_in, "r+");
			if (fichier != NULL) {
				while (fscanf(fichier, "%s", tmp) != EOF)
					ajouterMot(&a, tmp);
				fclose(fichier);
			} else
				printf("Impossible d'ouvrir le fichier.\n");
		}
	} else
		printf("Traitement impossible. Veuillez entrer le nom du fichier à traiter.\n");
	
	/* Exécution de la fonctionnalité choisie */
	switch (mode) {
		case 1:
			/* Affichage du lexique */
			afficherMots(a);
			creerDot(a,fichier_in);
			system("dot -Tpdf dico.dot -o dico.pdf");
			break;
		case 2:
			/* Sauvegarde de la liste de mots */
			sauvegarderMots(a, fichier_in);
			break;
		case 3:
			/* Recherche de mot dans le lexique */
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
			/* Sauvegarde de l'arbre dans un fichier DICO */
			sauvegarderArbre(a, fichier_in);
			printf("\n");
			break;
		default:
			break;
	}
	
	/* Libération de la mémoire allouée */
	libererArbre(&a);
	return 0;
}