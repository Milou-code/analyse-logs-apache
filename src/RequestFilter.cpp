/*************************************************************************
                           Ensemble  -  description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <Ensemble> (fichier Ensemble.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include<string>
using namespace std;

//------------------------------------------------------ Include personnel
#include "RequestFilter.h"
#include "Stats.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Ensemble::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

RequestFilter::IsForbidenFile(const string url){
    static const string extensions[] = { ".jpg", ".png", ".css", ".js"};

    for (const string & ext : extensions)
    {
        if (url.size() >= ext.size() && url.compare(url.size() - ext.size(), ext.size(), ext) == 0)
        {
            return true;
        }
    }
    return false;
}

RequestFilter::AddRequest(const Request RequestToFilter){
    if (ExtensionFilter && HourFilter){
        if (!IsForbidenFile(.url)){
            if ((RequestToFilter.hour >= hour) && (RequestToFilter.hour) <= (hour+1) ){
                AddTarget(RequestToFilter.url,RequestToFilter.referer);
            }
        }
    }   
    else if (HourFilter){
        if ((RequestToFilter.hour >= hour) && (RequestToFilter.hour) <= (hour+1) ){
            AddTarget(RequestToFilter.url,RequestToFilter.referer);
        }
    }
    else if (ExtensionFilter){
        if (!IsForbidenFile(.url)){
            AddTarget(RequestToFilter.url,RequestToFilter.referer);
        }
    }
    else{
        AddTarget(RequestToFilter.url,RequestToFilter.referer); 
    }
}

//-------------------------------------------- Constructeurs - destructeur


RequestFilter::~RequestFilter( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Ensemble>" << endl;
#endif
} //----- Fin de ~Ensemble


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
