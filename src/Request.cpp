//---------- Réalisation de la classe <Request> (fichier Re.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système

#include <ctime>
#include <iostream>
#include <sstream>
using namespace std;
//------------------------------------------------------ Include personnel
#include "Request.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Xxx::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

//-------------------------------------------- Constructeurs - destructeur
Request::Request(const string &anIP, const string aUserLogName,
                 const string anAutentificatedUser, const string anAnswerLength,
                 const string aBrowser, const string aDate, const string anHour,
                 const string aRefererURL, const string aReturnCode,
                 const string aTargetURL, const string anActionType)
    : IP(anIP), userLogname(aUserLogName),
      authentificatiedUser(anAutentificatedUser), answerLenght(anAnswerLength),
      browser(aBrowser), refererURL(aRefererURL), returnCode(aReturnCode),
      targetURL(aTargetURL), actionType(anActionType), date(aDate) {

  hour = atoi(anHour.c_str());

#ifdef MAP
  cout << "Appel au constructeur de copie de <Xxx>" << endl;
#endif
}
Request::~Request() {
// Algorithme :
//
#ifdef MAP
  cout << "Appel au destructeur de <Xxx>" << endl;
#endif
} //----- Fin de ~Xxx

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
