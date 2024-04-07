# Projet STL : Extraction de Motifs Graduels Fermés Fréquents sous Contrainte de Temporalité

## Description 
Le projet "STL" vise à développer des algorithmes en langage C permettant d'extraire efficacement des motifs graduels fermés fréquents à partir de données commerciales. Ces motifs sont cruciaux pour améliorer divers aspects tels que la gestion des stocks, l'agencement des produits en rayon et les recommandations en ligne.

## Installation 
Pour installer le projet, suivez ces étapes :
$ cd main_project/
$ make
$ ./main


## Exécution
Au lancement du programme, vous serez invité à choisir parmi les options suivantes :

- 1 pour exécuter l'algorithme Apriori
- 2 pour exécuter les tests

### Algorithme Apriori 
Lors de l'exécution de l'algorithme Apriori, suivez ces étapes :

Here's how you can include the code snippet in your README file:

markdown
Copy code
# Projet STL : Extraction de Motifs Graduels Fermés Fréquents sous Contrainte de Temporalité

## Description 
Le projet "STL" vise à développer des algorithmes en langage C permettant d'extraire efficacement des motifs graduels fermés fréquents à partir de données commerciales. Ces motifs sont cruciaux pour améliorer divers aspects tels que la gestion des stocks, l'agencement des produits en rayon et les recommandations en ligne.

## Installation 
Pour installer le projet, suivez ces étapes :

$ cd main_project/
$ make
$ ./main

markdown
Copy code

## Exécution
Au lancement du programme, vous serez invité à choisir parmi les options suivantes :

- 1 pour exécuter l'algorithme Apriori
- 2 pour exécuter les tests

### Algorithme Apriori 
Lors de l'exécution de l'algorithme Apriori, suivez ces étapes :

$- Entrez le nom du fichier : (choisissez le nom du fichier .csv à exécuter)
$- Entrez votre support : (choisissez le support)
$- Entrez le numéro de la colonne contenant les identifiants des articles : (indiquez à l'algorithme la colonne correspondant aux articles dans le fichier csv)
$- Entrez le numéro de la colonne contenant les identifiants des paniers : (indiquez à l'algorithme la colonne correspondant aux transactions dans le fichier csv)
$- Choisissez l'une des méthodes suivantes : (sélectionnez une méthode d'exécution de l'algorithme, soit 1 pour la méthode standard avec lecture du fichier à chaque passage, soit 2 où l'algorithme lit le fichier une seule fois (cette méthode a été ajoutée pour des raisons expérimentales))
### Tests
Les tests généreront des courbes expérimentales sur des données artificielles préalablement générées. Ils fourniront les résultats en termes de temps de calcul et de mémoire, en faisant varier les paramètres pertinents tels que :

- La probabilité d'apparition d'un article
- Le support
- Le nombre d'articles
- Le nombre de transactions

Lors de l'exécution de ces tests, le programme vous demandera de choisir quels paramètres faire varier (respectivement 1, 2, 3 ou 4).

