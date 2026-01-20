/*************************************************************************
                           RequestFilter - description
                             -------------------
    début                : $13/01/2026$
    copyright            : (C) $2026$ par $aeliasmene$
    e-mail               : $alexandre.elias-menet@insa-lyon.fr$
*************************************************************************/


#if ! defined ( REQUESTFILTER_H )
#define REQUESTFILTER_H


//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string> // Pour std::string
#include "Request.h"
#include "Stats.h" // Pour la classe Stats
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <RequestFilter>
//
//
//------------------------------------------------------------------------

class RequestFilter
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    void browseFile();
    // Mode d'emploi : 
    // Cette méthode parcourt le fichier logNameFile

    bool IsForbiddenFile(const std::string & url) const;
    // Mode d'emploi : 
    //

    void AddRequest(const Request & requestToFilter); // Suppression de 'const'
    // Mode d'emploi : 
    //  

//-------------------------------------------- Constructeurs - destructeur
    RequestFilter(const string & logFileName, const string & dotFileName, const bool graphFilter = false, const bool imageFilter = false, const int hourFilter = -1);
    // Mode d'emploi :
    //
    // Contrat : Le constructeur initialise les attributs de filtrage et l'objet Stats.
    //

    virtual ~RequestFilter ();
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    Stats statistics;
    string logFileName;
    string dotFileName;
    
    // Filters
    bool makeGraph;
    bool excludeImages;
    int hour;
//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <Ensemble>

#endif // REQUESTFILTER_H
