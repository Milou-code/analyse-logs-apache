# Analyseur de Logs Apache (Analog) - Projet de TP

## Présentation du projet
Ce petit logiciel a été développé dans le cadre d'un **Travaux Pratiques (TP)**. Il s'agit d'un outil en ligne de commande conçu en C++ pour analyser des fichiers de logs au format standard Apache. 

L'objectif principal est de fournir des statistiques de consultation et de visualiser les flux de navigation entre les différentes ressources d'un serveur web.

## Fonctionnalités principales
* **Top 10 des consultations** : Identifie et affiche les 10 documents les plus consultés par ordre décroissant de hits.
* **Filtrage horaire (`-t`)** : Permet de restreindre l'analyse aux requêtes effectuées dans un créneau d'une heure spécifique (ex: entre 11h et 12h).
* **Exclusion des ressources statiques (`-e`)** : Ignore les fichiers de type images (`.jpg`, `.png`), les feuilles de style (`.css`) et les scripts Javascript (`.js`) pour se concentrer sur les pages HTML.
* **Génération de graphes (`-g`)** : Produit un fichier au format GraphViz (`.dot`) représentant les relations entre les referers et les URLs cibles.
* **Création d’un PNG du graphe** : Afin de visualiser le graphe créé précédemment, il sera possible de générer une version au format PNG.

## Architecture logicielle
Le projet s'appuie sur une conception orientée objet :
* **`Request`** : Modélise une ligne de log avec ses différents attributs (IP, date, URL, etc.).
* **`Logstream`** : Gère le découpage (parsing) des lignes de logs.
* **`RequestFilter`** : Gère la lecture du fichier et applique les critères de sélection (heure, extensions) avant traitement.
* **`Stats`** : Stocke les données dans une structure de type `map` et génère les sorties (Top 10 ou fichier DOT).

## Installation et Utilisation
### Compilation
Le projet utilise un `Makefile`. Pour générer l'exécutable `analog` dans le dossier `bin/` :
```bash
make
```

## Exemples de commandes

* **Analyse standard** :  
    `./bin/analog logs/test.log`
* **Filtre horaire sur 11h** :  
    `./bin/analog -t 11 logs/test.log`
* **Exclusion d'images et génération de graphe** :  
    `./bin/analog -e -g mon_graphe.dot logs/test.log`
* **Création d’un PNG du graphe** :
`dot -Tpng -o graph.png mon_graph.dot`

## Tests

Une suite de tests automatisés est incluse pour valider le bon fonctionnement des filtres et de la logique de calcul :

* **`mktest.sh`** : Lance l'intégralité des tests et génère un rapport `results.csv`.
* **`test.sh`** : Permet d'exécuter un test spécifique en comparant la sortie réelle avec une sortie de référence (`std.out`).
