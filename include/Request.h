//---------- Interface de la classe <Request> (fichier Request.h)
//----------------
#if !defined(REQUEST_H)
#define REQUEST_H

//--------------------------------------------------- Interfaces utilisées
#include <ctime>
#include <iostream>
#include <string>
using namespace std;
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Rôle de la classe <Request>
//
//
//
//------------------------------------------------------------------------

class Request {
  //----------------------------------------------------------------- PUBLIC

public:
  //----------------------------------------------------- Méthodes publiques
  // type Méthode ( liste des paramètres );
  // Mode d'emploi :
  //
  // Contrat :
  //

  //-------------------------------------------- Constructeurs - destructeur
  Request(const string &anIP, const string &aUserLogName,
          const string &anAutentificatedUser, const string &anAnswerLength,
          const string &aBrowser, const string &aDate, const string &anHour,
          const string &aRefererURL, const string &aReturnCode,
          const string &aTargetURL, const string &anActionType);
  ~Request();

  // friend class declaration
  friend class RequestFilter;
  // Surcharge de l'opérateur de flux de sortie
  friend std::ostream &operator<<(std::ostream &os, const Request &request);
  
  //------------------------------------------------------------------ PRIVE

protected:
  //----------------------------------------------------- Méthodes protégées

  //----------------------------------------------------- Attributs protégés
  string IP;
  string userLogname;
  string authentificatiedUser;
  string answerLenght;
  string browser;
  string date;
  int hour;
  string refererURL;
  string returnCode;
  string targetURL;
  string actionType;
};

//-------------------------------- Autres définitions dépendantes de <Xxx>

#endif // REQUEST_H
