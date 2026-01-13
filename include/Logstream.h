//---------- Interface de la classe <Logstream> (fichier Logstream.h) ----------------
#if ! defined ( LOGSTREAM_H )
#define LOGSTREAM_H

//--------------------------------------------------- Interfaces utilisées

#include <fstream>
#include <string>
#include "Request.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Logstream>
//
//
//------------------------------------------------------------------------

class Logstream : public std::ifstream
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Méthodes publiques
    // type Méthode ( liste des paramètres );
    // Mode d'emploi :
    //
    // Contrat :
    //

    Request NextLog(const std::string& logLine);
    // Mode d'emploi :
    // créer un objet Requete à partir d'une ligne de Log


//------------------------------------------------- Surcharge d'opérateurs
    //Xxx & operator = ( const Xxx & unXxx );
    // Mode d'emploi :
    //
    // Contrat :
    //


//-------------------------------------------- Constructeurs - destructeur
    //Xxx ( const Xxx & unXxx );
    // Mode d'emploi (constructeur de copie) :
    //
    // Contrat :
    //

    Logstream() = default;
    // Mode d'emploi : appelle le constructeur par défaut de ifstream



//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Méthodes protégées

//----------------------------------------------------- Attributs protégés

};

//-------------------------------- Autres définitions dépendantes de <Logstream>

#endif // LOGSTREAM_H

