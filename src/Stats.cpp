//----- Réalisation de la classe <Stats> (fichier Stats.cpp) -----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

//------------------------------------------------------ Include personnel
#include "Stats.h"

using namespace std;

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

/**
 * Génère un fichier DOT représentant le graphe des références entre URLs.
 * @param dotFileName Nom du fichier DOT à créer.
 */
void Stats::CreateGraph(const string &dotFileName) const {
  // Algorithme de génération du graphe DOT : collecte des nœuds uniques et écrit les arcs avec les compteurs de hits
  string filePath = dotFileName;
  streambuf *coutBuffer = cout.rdbuf(); // sert à sauvegarder pour réutiliser le terminal plus tard
  ofstream dotFile(filePath);
  cout.rdbuf(dotFile.rdbuf());

  cout << "digraph {" << endl;

  set<string> allNodes; // set permet de ne pas garder les doublons

  for (const pair<const string, map<string, int>> &targetPair : targetCollection) {
    const string &targetURL = targetPair.first;
    allNodes.insert(targetURL); // on ajoute toutes les targets dans les noeuds du graphe

    const map<string, int> &refererMap = targetPair.second;
    for (const pair<const string, int> &refererPair : refererMap) {
      allNodes.insert(refererPair.first); // on ajoute tous les referers dans les noeuds du graphe
    }
  }
  map<string,string> NodeNames; // map pour stocker les noms des noeuds dans le fichier .dot
  int nodeIndex=0;
  for (const string &node : allNodes) {
    NodeNames[node]= "node"+to_string(nodeIndex++);
    cout << "\t" << NodeNames[node] << " [label = \"" << node << "\"]" << ";" << endl; // on écrit les noeuds dans le fichier .dot
  }

  // Créer tous les arcs avec leurs labels
  for (const pair<const string, map<string, int>> &targetPair : targetCollection) {
    const string &targetURL = targetPair.first;
    const map<string, int> &refererMap = targetPair.second;

    for (const pair<const string, int> &refererPair : refererMap) {
      const string &refererURL = refererPair.first;
      int hitCount = refererPair.second;

      cout << "\t" << NodeNames[refererURL] << " -> " << NodeNames[targetURL] << " [label=\""
                << hitCount << "\"];" << endl;
    }
  }

  dotFile << "}" << endl;

  dotFile.close();

  cout.rdbuf(coutBuffer); // redirige pour écrire dans le terminal
  cout << "Fichier .dot créé (dans le répertoire graphes): " << filePath
            << endl;
} //----- Fin de CreateGraph

/**
 * Affiche le top 10 des URLs les plus visitées.
 */
void Stats::Top10() const {

  map<string, int>
      totalHits; // création d'une MAP avec le nombre de hits par target

  for (const pair<const string, map<string, int>> &targetPair : targetCollection) {
    const string &targetURL = targetPair.first;
    const map<string, int> &refererMap = targetPair.second;

    int sum = 0;
    for (const pair<const string, int> &refererPair : refererMap) {
      sum += refererPair.second;
    }

    totalHits[targetURL] = sum;
  }

  vector<pair<string, int>> sortedHits;

  for (const pair<const string, int> &pair : totalHits) {
    sortedHits.push_back(pair);
  }

  sort(sortedHits.begin(),
            sortedHits.end(), // on trie les URL par ordre décroissant de hits
            // Tri des URLs par nombre de hits décroissant en utilisant une fonction lambda pour comparer les paires
            [](const pair<string, int> &a,
               const pair<string, int> &b) {
              if (a.second != b.second)
                return a.second > b.second; // hits décroissants
              return a.first < b.first;     // ordre alphabétique
            });

  int rank = 1;
  int limit = (sortedHits.size() < 10) ? sortedHits.size() : 10;

  for (int i = 0; i < limit; i++) {
    cout << sortedHits[i].first << " (" << sortedHits[i].second << " hits)"
              << endl;
    rank++;
  }

} //----- Fin de Top10

/**
 * Ajoute une requête aux statistiques en incrémentant le compteur pour la paire (referer, target).
 * @param refererURL URL de provenance.
 * @param targetURL URL cible.
 */
void Stats::AddRequest(const string &refererURL,
                       const string &targetURL) {
  // Architecture utilisant une map imbriquée pour compter les hits par paire (referer, target)
  {
    if (targetCollection.find(targetURL) ==
        targetCollection.end()) // target n'existe pas encore
    {
      map<string, int> newRefererMap;
      newRefererMap[refererURL] = 1;
      targetCollection[targetURL] = newRefererMap;
    }

    else {
      map<string, int> &refererMap = targetCollection[targetURL];

      if (refererMap.find(refererURL) == refererMap.end()) // referer n'existe pas encore pour cette cible
      {
        refererMap[refererURL] = 1;
      }

      else {
        refererMap[refererURL]++;
      }
    }
  }
} //----- Fin de AddRequest

//---------------------------------------------------------- Constructeur

/**
 * Constructeur de la classe Stats.
 */
Stats::Stats() : targetCollection() {

#ifdef MAP
  cout << "Appel au constructeur de <Stats>" << endl;
#endif

} //----- Fin du constructeur de Stats

//------------------------------------------------------------ Destructeur

/**
 * Destructeur de la classe Stats.
 */
Stats::~Stats() {

#ifdef MAP
  cout << "Appel au destructeur de <Stats>" << endl;
#endif
} //----- Fin du destructeur de Stats
