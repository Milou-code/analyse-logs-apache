/*************************************************************************
                           RequestFilter - description
                             -------------------
    début                : $DATE$
    copyright            : (C) $YEAR$ par $AUTHOR$
    e-mail               : $EMAIL$
*************************************************************************/

//---------- Réalisation de la classe <RequestFilter> (fichier
//RequestFilter.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <string>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Logstream.h"
#include "Request.h"
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

/**
 * Parcourt le fichier de logs, applique les filtres et génère les statistiques.
 */
void RequestFilter::browseFile() {
  if (hour != -1) {
    cout << "Warning : prise en compte des logs entre " << hour << "h et "
         << hour + 1 << "h !" << endl;
  }
  Logstream logFile;
  logFile.open(logFileName);
  string line;

  // On parcourt toutes les lignes du fichier
  while (getline(logFile, line)) {
    if (line.empty())
      continue; // Gère le cas ou la ligne est vide

    Request request = logFile.NextLog(line);

    // Vérification de la validité globale de la requête
    // Si l'URL est "-" ou vide, on ignore.
    if (request.targetURL.empty() || request.targetURL == "-") {
      continue;
    }

    AddRequest(request);
  }

  // On a finit de parcourir le fichier, on peut créer le graphe si nécessaire
  if (makeGraph) {
    if (dotFileName.empty()) {
      cout
          << "Erreur : Vous n'avez pas sécifié de nom de fichier pour le graphe"
          << endl;
    } else {
      statistics.CreateGraph(dotFileName);
    }
  }

  // Dans tous les cas on affiche le top10
  statistics.Top10();
} //----- Fin de browseFile

/**
 * Vérifie si l'URL correspond à un fichier interdit (images, CSS, JS).
 * @param url URL à vérifier.
 * @return true si l'URL est interdite, false sinon.
 */
bool RequestFilter::IsForbiddenFile(const string &url) const {
  // Vérification si l'URL se termine par une extension interdite en comparant la fin de la chaîne
  static const string extensions[] = {".jpeg", ".gif", ".jpg",
                                      ".png",  ".css", ".js"};

  for (const string &ext : extensions) {
    if (url.size() >= ext.size() &&
        url.compare(url.size() - ext.size(), ext.size(), ext) == 0) {
      return true;
    }
  }
  return false;
}

/**
 * Ajoute une requête aux statistiques si elle passe tous les filtres.
 * @param requestToFilter Requête à filtrer et ajouter.
 */
void RequestFilter::AddRequest(const Request &requestToFilter) {
  bool passesFilters = true;

  // Appliquer le filtre d'exclusion d'images
  if (excludeImages) {
    if (IsForbiddenFile(requestToFilter.targetURL)) {
      passesFilters = false;
    }
  }

  // Appliquer le filtre horaire (seulement si les filtres précédents sont
  // passés)
  if (hour != -1 && passesFilters) {
    // Filtre horaire : accepte seulement les requêtes dans l'intervalle [hour, hour+1[
    if (!((requestToFilter.hour >= hour) &&
          (requestToFilter.hour < (hour + 1)))) {
      passesFilters = false;
    }
  }

  // Si tous les filtres sont passés, ajouter la requête aux statistiques
  if (passesFilters) {
    // Correction de l'ordre des arguments : refererURL, targetURL
    statistics.AddRequest(requestToFilter.refererURL,
                          requestToFilter.targetURL);
  }
}

//-------------------------------------------- Constructeurs - destructeur

// Implémentation du constructeur (déplacée du .h pour une meilleure pratique)
/**
 * Constructeur de la classe RequestFilter.
 * @param logFileName Nom du fichier de logs.
 * @param dotFileName Nom du fichier DOT pour le graphe.
 * @param graphFilter Indicateur pour générer le graphe.
 * @param imageFilter Indicateur pour exclure les images.
 * @param hourFilter Heure pour le filtre horaire (-1 si aucun).
 */
RequestFilter::RequestFilter(const string &logFileName,
                             const string &dotFileName, const bool graphFilter,
                             const bool imageFilter, const int hourFilter)
    : statistics(), logFileName(logFileName), dotFileName(dotFileName),
      makeGraph(graphFilter), excludeImages(imageFilter), hour(hourFilter) {
#ifdef MAP
  cout << "Appel au constructeur de <RequestFilter>" << endl;
#endif
}

/**
 * Destructeur de la classe RequestFilter.
 */
RequestFilter::~RequestFilter()
// Algorithme :
//
{
#ifdef MAP
  cout << "Appel au destructeur de <RequestFilter>" << endl;
#endif
} //----- Fin de ~RequestFilter

//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Méthodes protégées
