#include <iostream>
#include <string>
#include "../include/Logstream.h"
#include "../include/Request.h"
using namespace std;

int main() {
    string nomFichier = "../../Fichier Fournis/access_log";
    Logstream logFile;
    logFile.open(nomFichier);

    string line;

    // On parcourt toutes les lignes du fichier
    while (getline(logFile, line)) {
        if (line.empty()) continue; // Si la ligne est vide on la saute
        Request request = logFile.NextLog(line);
        cout
    }
}
