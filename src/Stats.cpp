//----- Réalisation de la classe <Stats> (fichier Stats.cpp) -----

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>

//------------------------------------------------------ Include personnel
#include "Stats.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

void Stats::CreateGraph(const std::string& dotFileName) const{
    std::string filePath = "graphes/" + dotFileName;
    std::streambuf* coutBuffer = std::cout.rdbuf(); //sert à sauvegarder pour réutiliser le terminal plus tard
    std::ofstream dotFile(filePath);
    std::cout.rdbuf(dotFile.rdbuf());
    
    std::cout << "digraph {" << std::endl;
    
    std::set<std::string> allNodes; //set permet de ne pas garder les doublons
    
    for (const auto& targetPair : targetCollection)
    {
        const std::string& targetURL = targetPair.first;
        allNodes.insert(targetURL); //on ajoute toutes les targets dans les noeuds du graphe
        
        const std::map<std::string, int>& refererMap = targetPair.second;
        for (const auto& refererPair : refererMap) 
        {
            allNodes.insert(refererPair.first); //on ajoute tous les referers dans les noeuds du graphe
        }
    }
    
   
    for (const auto& node : allNodes)
    {
        std::cout << "\t\"" << node << "\";" << std::endl; //on écrit les noeuds dans le fichier .dot
    }
    
    // Créer tous les arcs avec leurs labels
    for (const auto& targetPair : targetCollection)
    {
        const std::string& targetURL = targetPair.first;
        const std::map<std::string, int>& refererMap = targetPair.second;
        
        for (const auto& refererPair : refererMap)
        {
            const std::string& refererURL = refererPair.first;
            int hitCount = refererPair.second;
            
            std::cout << "\t\"" << refererURL << "\" -> \"" << targetURL 
                    << "\" [label=\"" << hitCount << "\"];" << std::endl;
        }
    }
    
    dotFile << "}" << std::endl;
    
    dotFile.close();
    
    std::cout.rdbuf(coutBuffer); //redirige pour écrire dans le terminal
    std::cout << "Fichier .dot créé (dans le répertoire graphes): " << filePath << std::endl;
} //----- Fin de CreateGraph


void Stats::Top10() const{
 
    std::map<std::string, int> totalHits; // création d'une MAP avec le nombre de hits par target
    
    for (const auto& targetPair : targetCollection)
    {
        const std::string& targetURL = targetPair.first;
        const std::map<std::string, int>& refererMap = targetPair.second;
        
        int sum = 0;
        for (const auto& refererPair : refererMap)
        {
            sum += refererPair.second; 
        }
        
        totalHits[targetURL] = sum;
    }
    
    std::vector<std::pair<std::string, int>> sortedHits;
    
    for (const auto& pair : totalHits)
    {
        sortedHits.push_back(pair); 
    }
    
    std::sort(sortedHits.begin(), sortedHits.end(), // on trie les URL par ordre décroissant de hits
              [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                  return a.second > b.second; 
              });
    
    int rank = 1;
    int limit = (sortedHits.size() < 10) ? sortedHits.size() : 10;
    
    for (int i = 0; i < limit; i++)
    {
        std::cout << sortedHits[i].first << " (" << sortedHits[i].second << " hits)" << std::endl;
        rank++;
    }
    
} //----- Fin de Top10



void Stats::AddRequest(const std::string& refererURL, const std::string& targetURL){
{
    if (targetCollection.find(targetURL) == targetCollection.end())  //target n'existe pas encore
    {
        std::map<std::string, int> newRefererMap;
        newRefererMap[refererURL] = 1;
        targetCollection[targetURL] = newRefererMap;
    }

    else
    {
        std::map<std::string, int>& refererMap = targetCollection[targetURL]; 
        
        if (refererMap.find(refererURL) == refererMap.end()) //referer n'existe pas encore pour cette cible
        {
            refererMap[refererURL] = 1;
        }
        
        else
        {
            refererMap[refererURL]++;
        }
    }
}
} //----- Fin de AddRequest

//---------------------------------------------------------- Constructeur

Stats::Stats() : targetCollection() {
    
#ifdef MAP
    cout << "Appel au constructeur de <Stats>" << endl;
#endif

} //----- Fin du constructeur de Stats

//------------------------------------------------------------ Destructeur

Stats::~Stats(){

#ifdef MAP
    cout << "Appel au destructeur de <Stats>" << endl;
#endif
} //----- Fin du destructeur de Stats