#include <iostream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <limits>
#include <cstring>
#include <vector> 
#include <fstream>
#include <algorithm>

bool hasExtension(const std::string& filename, const std::string& extension) {
    size_t extLen = extension.length();
    size_t filenameLen = filename.length();

    // Vérifier si le nom de fichier est assez long pour avoir une extension
    if (filenameLen < extLen) {
        return false;
    }

    // Comparer la fin de la chaîne avec l'extension attendue
    return std::strcmp(filename.c_str() + filenameLen - extLen, extension.c_str()) == 0;
}

void seperatePathFile(std::string& sPathFile, std::string& sPath) {
    // Extraire le chemin et le nom de fichier de arg4
    size_t lastSlash = sPathFile.find_last_of('/');
    size_t lastBackslash = sPathFile.find_last_of('\\');

    if (lastSlash > 99999999) lastSlash = 0;
    if (lastBackslash > 99999999) lastBackslash = 0;
    size_t lastSeparator = std::max(lastSlash, lastBackslash);

    if (lastSeparator) {
        sPath = sPathFile.substr(0, lastSeparator + 1);
        sPathFile = sPathFile.substr(lastSeparator + 1);
    }
    else {
        sPath = ""; // Aucun chemin trouvé
    }
}

bool isValidMireFormat(const std::string& input) {
    // Vérifier que la chaîne commence par "mire"
    if (input.substr(0, 4) != "mire") {
        return false;
    }

    // Vérifier que le reste de la chaîne est composé uniquement de chiffres
    for (size_t i = 4; i < input.length(); ++i) {
        if (!std::isdigit(input[i])) {
            return false;
        }
    }
    return true;
}

// Fonction pour convertir une chaîne en minuscules
void toLower(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

// Fonction pour lire et analyser le fichier de configuration
bool readConfigFile(const std::string& filename,
    std::pair<unsigned int, unsigned int>& pPreProMinMax,
    unsigned int& uiSplitStrat,
    unsigned int& uiNeighStrat,
    unsigned int& uiMergeStrat,
    bool& bPreproNii,
    bool& bSplitNii,
    bool& bMergeNii,
    bool& bDetails) {
    std::ifstream configFile(filename);

    if (!configFile.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier de configuration." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(configFile, line)) {
        // Ignorer les commentaires et les lignes vides
        if (line.empty() || line[0] == '#' || line[0] == ';') {
            continue;
        }

        // Convertir la ligne en minuscules pour être insensible à la casse
        toLower(line);

        std::istringstream iss(line);
        std::string key, value;

        // Extraire la clé et la valeur
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            // Supprimer les espaces autour de la clé et de la valeur
            key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
            value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());

            // Analyser la clé et la valeur
            if (key == "prepro") {
                std::istringstream valueStream(value);
                char comma;
                if (valueStream >> pPreProMinMax.first >> comma >> pPreProMinMax.second && comma == ',') {
                    bPreproNii = true;
                }
                else {
                    std::cerr << "Erreur : Format invalide pour la clé 'prepro'." << std::endl;
                    return false;
                }
            }
            else if (key == "split") {
                if (std::istringstream(value) >> uiSplitStrat) {
                    bSplitNii = true;
                }
                else {
                    std::cerr << "Erreur : Format invalide pour la clé 'split'." << std::endl;
                    return false;
                }
            }
            else if (key == "neighbourg") { // Note : corriger la faute de frappe "neighbourg" à "neigh"
                if (std::istringstream(value) >> uiNeighStrat) {
                    // ...
                }
                else {
                    std::cerr << "Erreur : Format invalide pour la clé 'neighbourg'." << std::endl;
                    return false;
                }
            }
            else if (key == "merge") {
                if (std::istringstream(value) >> uiMergeStrat) {
                    bMergeNii = true;
                }
                else {
                    std::cerr << "Erreur : Format invalide pour la clé 'merge'." << std::endl;
                    return false;
                }
            }
            else if (key == "preproimg") {
                std::istringstream(value) >> std::boolalpha >> bPreproNii;
            }
            else if (key == "splitimg") {
                std::istringstream(value) >> std::boolalpha >> bSplitNii;
            }
            else if (key == "mergeimg") {
                std::istringstream(value) >> std::boolalpha >> bMergeNii;
            }
            else if (key == "details") {
                std::istringstream(value) >> std::boolalpha >> bDetails;
            }
            else {
                std::cerr << "Avertissement : Clé non reconnue '" << key << "'." << std::endl;
            }
        }
        else {
            std::cerr << "Erreur : Format invalide pour la ligne '" << line << "'." << std::endl;
            return false;
        }
    }

    return true;
}