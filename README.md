
# Projet STL (2023-2024) : Extraction de Motifs Graduels Fermés Fréquents sous Contrainte de Temporalité 

## Description 
Le projet "STL" vise à développer des algorithmes en langage C permettant d'extraire efficacement des motifs graduels fermés fréquents à partir de données commerciales. Ces motifs sont cruciaux pour améliorer divers aspects tels que la gestion des stocks, l'agencement des produits en rayon et les recommandations en ligne.

## Contributeurs 
- Muhannad Alabdullah
- Lea El Abboud
- Esma Hocini

## Installation 
Pour installer le projet, suivez ces étapes :
```
 $ cd main_project/
 $ make
 $ ./main
```

## Exécution
Au lancement du programme, vous serez invité à choisir parmi les options suivantes :

- 1 pour exécuter l'algorithme Apriori
- 2 pour exécuter les tests

### Algorithme Apriori 
Lors de l'exécution de l'algorithme Apriori, suivez ces étapes :
```
$- Enter the file's name :
//choisissez le nom du fichier .csv à exécuter
$- Enter your support :
//choisissez le support
$- In your file, which column do the items' ids exist in ? :
//indiquez à l'algorithme la colonne correspondant aux articles dans le fichier csv
$- In your file, which column do the transactions' ids exist in ? :
//indiquez à l'algorithme la colonne correspondant aux transactions dans le fichier csv
$- Choose one of the following methods : (
//sélectionnez une méthode d'exécution de l'algorithme, soit 1 pour la méthode standard avec lecture du fichier à chaque passage, soit 2 où l'algorithme lit le fichier une seule fois (cette méthode a été ajoutée pour des raisons expérimentales)
```
### Tests
Les tests généreront des courbes expérimentales sur des données artificielles préalablement générées. Ils fourniront les résultats en termes de temps de calcul et de mémoire, en faisant varier les paramètres pertinents tels que :

- 1 La probabilité d'apparition d'un article
- 2 Le nombre de transactions
- 3 Le nombre d'items
- 4 Le support

Lors de l'exécution de ces tests, le programme vous demandera de choisir quels paramètres faire varier (respectivement 1, 2, 3 ou 4).

