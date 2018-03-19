# Arbre Lexical en C
> Programme C - Arbre Lexicographique - Tom Samaille, Florian Torres

### Différentes commandes possibles :

Charge le lexique **dico**
```shell
./Lexique dico
```

Affiche les mots du lexique **dico** en ordre alphabétique
```shell
./Lexique -l dico
```

Sauvegarde les mots du lexique **dico** en ordre alphabétique (au format .L)
```shell
./Lexique -s dico
```

Vérifier si un **mot** existe dans le **dico**
```shell
./Lexique -r mot dico
```

Sauvegarde l'arbre lexical **dico** au format .DICO
```shell
./Lexique -S dico
```

### A faire :
- [x] Afficher les mots du lexique
- [x] Sauvegarder les mots dans un fichier
- [x] Indiquer si un mot est présent dans le texte sous forme **present** ou **absent**
- [x] Option -l (afficher mots du lexique)
- [x] Option -s (sauvegarder mots du lexique)
- [x] Option -r (Vérifier si un mot existe dans le lexique)
- [x] option -S (Enregistrer au format .DICO)
- [x] Si le .DICO existe, récupérer l'arbre déjà présent dans le fichier.DICO
- [ ] Rédiger le rapport
- [x] Commenter les fonctions
- [ ] Créer une constante TAILLE_MAX_MOT et gérer tous les tableaux de caractères avec cette variable (à  priori 51 : à revérifier)
- [ ] Vérifier l'intégrité des noms de fonctions / variables etc...
- [ ] Free la mémoire : viderArbre(Arbre *a);

### Améliorations : 
- [x] Possibilité d'afficher l'abre avec la création d'un fichier.dot
- [ ] Vérifier le .dot généré