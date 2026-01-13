/*************************************************************************
                           RequestFilter  -  description
                             -------------------
    début                : $13/01/2026$
    copyright            : (C) $2026$ par $aeliasmene$
    e-mail               : $alexandre.elias-menet@insa-lyon.fr$
*************************************************************************/

#if ! defined ( REQUESTFILTER_H )
#define REQUESTFILTER_H


//--------------------------------------------------- Interfaces utilisées
#include <iostream>
#include <string>
using namespace std;
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


    bool IsForbidenFile(const string url);
    // Mode d'emploi : 
    //


    void AddRequest(const Request RequestToFilter) const;
    // Mode d'emploi : 
    //

    

//-------------------------------------------- Constructeurs - destructeur
    RequestFilter(const bool ExtensionFilter, const int hourfilter) : filter(typefilter), hour(hourfilter){};
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~RequestFilter ();
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées
    bool ExtensionFilter;
    int hour;
//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <Ensemble>

#endif // REQUESTFILTER_H