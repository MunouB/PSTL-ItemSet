
# Projet STL (2023-2024) : Extraction de Motifs Graduels Fermés Fréquents sous Contrainte de Temporalité 

## Table des Matières

  - [Description](#description)
  - [Contributeurs](#contributeurs)
  - [Installation des dépendances](#installation-des-dépendances)
    - [Gnuplot : Pour l'affichage des courbes graphiques](#gnuplot--pour-laffichage-des-courbes-graphiques)
  - [Lancement du projet](#lancement-du-projet)
  - [Exécution](#exécution)
    - [Algorithme Apriori](#algorithme-apriori)

    - [Tests](#tests)

## Description 
Le projet "STL" vise à développer des algorithmes en langage C permettant d'extraire efficacement des motifs graduels fermés fréquents à partir de données commerciales. Ces motifs sont cruciaux pour améliorer divers aspects tels que la gestion des stocks, l'agencement des produits en rayon et les recommandations en ligne.

## Contributeurs 
- Muhannad Alabdullah
- Lea El Abboud
- Esma Hocini

## Installation des dépendances
### Gnuplot : Pour l'affichage des courbes graphiques

- **Windows**: Téléchargez et installez Gnuplot à partir du [site officiel](http://www.gnuplot.info/download.html).
- **Linux**: Utilisez votre gestionnaire de paquets, par exemple `sudo apt-get install gnuplot` pour Debian/Ubuntu.
- **macOS**: Utilisez Homebrew en exécutant `brew install gnuplot`.

## Lancement et compilation du projet 
Pour installer le projet, suivez ces étapes :
```
 $ cd main_project/
 $ make
```

## Exécution
Au lancement du programme, vous pouvez exécuter différentes fonctionnalités en utilisant des arguments en ligne de commande.
Le premier argument passé lors de l'exécution du programme (`1` ou `2`) détermine quelle fonctionnalité du programme doit être exécutée :
- Si le premier argument est `1`, cela indique que l'utilisateur souhaite exécuter l'algorithme Apriori.
- Si le premier argument est `2`, cela signifie que l'utilisateur souhaite exécuter les tests.

### Algorithme Apriori
#### Format du fichier CSV

Le fichier de données est au format CSV (Comma-Separated Values) et comprend deux colonnes :

```
Transaction, Items
1, 2
1, 18
2, 12
2, 1
2, 2
3, 13
3, 78
```
La première colonne représente les `transactions` et la deuxième colonne représente les `items` associés à chaque transaction.

- Pour exécuter l'algorithme de base, utilisez : 

```
./main 1 fichier.csv support algochoice
```

- Pour exécuter l'algorithme TID, utilisez : 

```
./main 2 fichier.csv support 
```
- Assurez-vous de remplacer `fichier.csv`, `support`, et `algochoice` par les valeurs appropriées.
`algochoice` est une option pour choisir la méthode d'exécution de l'algorithme, soit 1 pour la méthode standard avec lecture du fichier à chaque passage, ou bien 2 où l'algorithme lit le fichier une seule fois (cette méthode a été ajoutée pour des raisons expérimentales).


### Tests
Les tests généreront des courbes expérimentales sur des données artificielles préalablement générées. Ils fourniront les résultats en termes de temps de calcul et de mémoire, en faisant varier les paramètres pertinents tels que, pour executer les tests utilisez : 

```
./main 3 varchoice
```

Assurez-vous de remplacer `varchoice` par la valeur appropriée, telle que:

- 1 La probabilité d'apparition d'un article
- 2 Le nombre de transactions
- 3 Le nombre d'items
- 4 Le support

Lors de l'exécution de ces tests, le programme vous demandera de choisir quels paramètres faire varier (respectivement 1, 2, 3 ou 4).