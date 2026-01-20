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
        else {
            logFileName = arg;
        }
    }

    if (logFileName.empty()) {
        cout << "Erreur : Aucun fichier log spécifié." << endl;
        return 1;
    }


    RequestFilter filter(logFileName, dotFileName, makeGraph, excludeImages, hourFilter);
    filter.browseFile();

    return 0;
}