//---------- Réalisation de la classe <Logstream> (fichier Logstream.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <sstream>
#include <string>

//------------------------------------------------------ Include personnel
#include "Logstream.h"
#include "Request.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques
// type Xxx::Méthode ( liste des paramètres )
// Algorithme :
//
//{
//} //----- Fin de Méthode

Request Logstream::NextLog(const string& logLine)
{
    // Variables pour stocker les données parsées
    string ip;
    string userLogname;
    string authentificatedUser;
    string rawDateTime;
    string requestLine;
    string returnCode;
    string answerLength;
    string refererURL;
    string browser;

    // Variables temporaires pour le parsing
    size_t currentPos = 0;
    size_t nextPos;

    // 1. Adresse IP
    nextPos = logLine.find(' ', currentPos);
    if (nextPos == string::npos) return Request("", "", "", "", "", "", "", "", "", "", ""); // Ligne malformée
    ip = logLine.substr(currentPos, nextPos - currentPos);
    currentPos = nextPos + 1;

    // 2. Nom d'utilisateur distant souvent '-'
    nextPos = logLine.find(' ', currentPos);
    if (nextPos == string::npos) return Request("", "", "", "", "", "", "", "", "", "", "");
    userLogname = logLine.substr(currentPos, nextPos - currentPos);
    currentPos = nextPos + 1;

    // 3. Utilisateur authentifié souvent '-'
    nextPos = logLine.find(' ', currentPos);
    if (nextPos == string::npos) return Request("", "", "", "", "", "", "", "", "", "", "");
    authentificatedUser = logLine.substr(currentPos, nextPos - currentPos);
    currentPos = nextPos + 1;

    // 4. Date et Heure entre crochets []
    nextPos = logLine.find('[', currentPos);
    if (nextPos == string::npos) return Request("", "", "", "", "", "", "", "", "", "", "");
    currentPos = nextPos + 1;
    nextPos = logLine.find(']', currentPos);
    if (nextPos == string::npos) return Request("", "", "", "", "", "", "", "", "", "", "");
    rawDateTime = logLine.substr(currentPos, nextPos - currentPos);
    currentPos = nextPos + 2; // Passer ']' et l'espace suivant

    // Parser rawDateTime pour la date et l'heure
    string datePart;
    string hourPart;
    size_t firstColonPos = rawDateTime.find(':');
    if (firstColonPos != string::npos) {
        datePart = rawDateTime.substr(0, firstColonPos); // ex: "10/Oct/2000"
        hourPart = rawDateTime.substr(firstColonPos + 1, 2); // ex: "13"
    } else {
        datePart = rawDateTime; // Fallback si pas de ':'
        hourPart = "-1"; // Indiquer une heure inconnue
    }

    // 5. Ligne de Requête entre guillemets ""
    nextPos = logLine.find('"', currentPos);
    if (nextPos == string::npos) return Request("", "", "", "", "", "", "", "", "", "", "");
    currentPos = nextPos + 1;
    nextPos = logLine.find('"', currentPos);
    if (nextPos == string::npos) return Request("", "", "", "", "", "", "", "", "", "", "");
    requestLine = logLine.substr(currentPos, nextPos - currentPos);
    currentPos = nextPos + 2; // Passer '"' et l'espace suivant

    // Parser requestLine pour actionType et targetURL
    istringstream requestIss(requestLine);
    string actionTypePart;
    string targetURLPart;
    requestIss >> actionTypePart >> targetURLPart;

    // 6. Code de Statut
    nextPos = logLine.find(' ', currentPos);
    if (nextPos == string::npos) return Request("", "", "", "", "", "", "", "", "", "", "");
    returnCode = logLine.substr(currentPos, nextPos - currentPos);
    currentPos = nextPos + 1;

    // 7. Taille de la Réponse
    nextPos = logLine.find(' ', currentPos);
    if (nextPos == string::npos) return Request("", "", "", "", "", "", "", "", "", "", "");
    answerLength = logLine.substr(currentPos, nextPos - currentPos);
    currentPos = nextPos + 1;

    // 8. Référent entre guillemets ""
    nextPos = logLine.find('"', currentPos);
    if (nextPos == string::npos) refererURL = "-"; // Le référent peut être vide ou malformé
    else {
        currentPos = nextPos + 1;
        nextPos = logLine.find('"', currentPos);
        if (nextPos == string::npos) refererURL = "-";
        else {
            refererURL = logLine.substr(currentPos, nextPos - currentPos);
            currentPos = nextPos + 2; // Passer '"' et l'espace
        }
    }

    // 9. Agent Utilisateur entre guillemets "" (prend le reste de la ligne)
    // On cherche le prochain guillemet pour le début de l'User-Agent
    nextPos = logLine.find('"', currentPos);
    if (nextPos == string::npos) browser = "-"; // L'User-Agent peut être vide ou malformé
    else {
        currentPos = nextPos + 1;
        nextPos = logLine.find('"', currentPos);
        if (nextPos == string::npos) browser = "-";
        else {
            browser = logLine.substr(currentPos, nextPos - currentPos);
        }
    }

    // Créer et retourner l'objet Request
    return Request(ip, userLogname, authentificatedUser, answerLength, browser,
                   datePart, hourPart, refererURL, returnCode, targetURLPart, actionTypePart);
} //----- Fin de la Méthode NextLog

//------------------------------------------------- Surcharge d'opérateurs

//-------------------------------------------- Constructeurs - destructeur

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
