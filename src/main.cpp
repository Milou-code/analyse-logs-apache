#include <iostream>
#include <string>
#include "RequestFilter.h"

using namespace std;


int main(int argc, char* argv[]) {
    string logFileName;
    bool makeGraph = false;
    string dotFileName;
    bool excludeImages = false;
    int hourFilter = -1;
    bool logFileFound = false;

    // Analyse des arguments (on commence à i = 1 car argv[0] est le nom du programme)
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "-g" && i + 1 < argc) {
            makeGraph = true;
            dotFileName = argv[++i]; // Récupère le nom du fichier .dot et avance l'indice
        }
        else if (arg == "-e") {
            excludeImages = true;
        }
        else if (arg == "-t" && i + 1 < argc) {
            hourFilter = stoi(argv[++i]);
        }
        else if (arg[0] == '-') {
            cout << "Erreur : Option invalide '" << arg << "', commande non exécutée. " << endl;
            // Rien est exécuté même s'il y a d'autres options valides
            return 1;
        }
        else {
            if (logFileFound) {
                // Un fichier log a déjà été trouvé, donc cet argument est en trop
                cout << "Erreur : Caractère inattendu dans l'exécution, commande non exécutée. " << endl;
                return 1;
            }
            logFileName = arg;
            logFileFound = true;
        }
    }

    RequestFilter filter(logFileName, dotFileName, makeGraph, excludeImages, hourFilter);
    filter.browseFile();

    return 0;
}