//---------- Interface de la classe <Stats> (fichier Stats.h) ----------------
#if ! defined ( STATS_H )
#define STATS_H

#include <map>
#include <string>
//--------------------------------------------------- Interfaces utilisées

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Permet de créer et modifier la collection de cibles, et de l'utiliser
// pour soit créer un top 10 des sites cibles les plus populaires (avec des
// filtres particuliers ou non), soit créer un graphe qui représente tous 
// hits entre un chaques URL deux à deux.
//------------------------------------------------------------------------

class Stats 
{
//----------------------------------------------------------------- PUBLIC


public:
//----------------------------------------------------- Méthodes publiques

    void CreateGraph() const;

    void Top10() const;

    void AddRequest(const std::string& refererURL, const std::string& targetURL);
    

//-------------------------------------------- Constructeurs - destructeur

    Stats ( );

    ~Stats ( );

//------------------------------------------------------------------ PRIVE

protected:

//----------------------------------------------------- Attributs protégés

    std::map<std::string, std::map<std::string, int>> targetCollection;

};

#endif // STATS_H