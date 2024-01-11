#include <iostream>
#include <cstdlib>
#include <sstream>
#include <limits>
#include <cstring>
#include <vector> 
#include <boost/multi_array.hpp>

#include "nifti1.h"
#include "CNiftiImage.h"
#include "CNiftiImageData.h"
#include "CMultiArrayOperation.h"
#include "CGrapheCreator.h"
#include "COperationsSurGraphes.h"


typedef struct Parameters {

    //user inputs
    float           fHomogeneityCrit =0.0f;   
    unsigned int    uiMinSize       =0;
    std::string     sSourceNii;
    std::string     sOutNiiName;
    std::string     sOutNiiPath;
    std::string     sSettingFile;

    //Process
    std::pair <unsigned int, unsigned int> pPreProMinMax;
    unsigned int    uiSplitStrat    =0;
    unsigned int    uiNeighStrat    =0;
    unsigned int    uiMergeStrat    =0;
    //Outputs
    bool            bPreproNii  =false;
    bool            bSplitNii   =false;
    bool            bMergeNii   =true;
    bool            bDetails    =false;
} Parameters;

typedef struct Times {

    //general
    double         TotalExecution;
    
    //algorithm
    double         Split;
    double         Neighboring;
    double         Merge;

    //sections
    double         Startup;
    double         Reading;
    double         Spliting;
    double         Merging;
    double         Writring;

    //detailled

} Times;


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

int main(int argc, char* argv[]) {

    // Vérifier le nombre d'arguments
    if (argc < 5 || argc > 6) {
        std::cerr << "Usage: " << argv[0] << " [float entre 0 et 1] [entier entre 1 et 1000] [Input Nifti image.nii] [Output Nifti image.nii] [optionel settings.txt]" << std::endl;
        return 1;
    }

    // Convertir les arguments et vérifier les conditions
    float arg1;
    int arg2;
    std::string arg3, arg4, arg5, sOutPath;

    try {
        arg1 = std::stof(argv[1]);
        arg2 = std::stoi(argv[2]);
        arg3 = argv[3];
        arg4 = argv[4];

        if (arg1 < 0.0f || arg1 > 1.0f) {
            throw std::invalid_argument("Les valeurs des arguments 1 ne respectent pas les conditions:\nHomogeneity criterion [float entre 0 et 1]");
        }


        if (arg2 < 1 || arg2 > 1000) {
            throw std::invalid_argument("Les valeurs des arguments 2 ne respectent pas les conditions:\nDimension minimale de decoupe [entier entre 1 et 1000]");
        }

        // Vérifier que les fichiers .nii existent et ont la bonne extension
        if (!hasExtension(arg3, ".nii") || !hasExtension(arg4, ".nii")) {
            throw std::invalid_argument("Les fichiers images NIfTI doivent avoir l'extension '.nii'");
        }

        seperatePathFile( arg4, sOutPath);
        

        if (argc == 6) {
            arg5 = argv[5];
            // Vérifier que le fichier .txt existe et a la bonne extension
            if (!hasExtension(arg5, ".txt")) {
                throw std::invalid_argument("Le fichier .txt doit avoir l'extension '.txt'");
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    std::cout << arg1 << ", " << arg2 << ", " << arg3 << ", " << arg4 << ", " << sOutPath << std::endl;

    Times Times;
    Parameters Parameters;
    Parameters.fHomogeneityCrit = arg1;
    Parameters.uiMinSize = arg2;
    Parameters.sSourceNii = arg3;
    Parameters.sOutNiiName = arg4;
    Parameters.sOutNiiPath = sOutPath;
    Parameters.sSettingFile = arg5;

    if (argc == 6) {
        //read setting file

        //si tout est bon :
        //Parameters.tPreProMinMax =
        //Parameters.uiSplitStrat =
        //Parameters.uiNeighStrat =
        //Parameters.uiMergeStrat =

        //Parameters.bPreproNii = false;
        //Parameters.bSplitNii = false;
        //Parameters.bMergeNii = true;
        //Parameters.bDetails = false;
    }

    std::cout << "[NiiSplitMerge.exe] Programme parameters configuration:"
        << "\n[NiiSplitMerge.exe] Inputs:"
        << "\n[NiiSplitMerge.exe]\tHomogeneity criterion:\t"    << Parameters.fHomogeneityCrit
        << "\n[NiiSplitMerge.exe]\tMinimum chunk dimension:"    << Parameters.uiMinSize
        << "\n[NiiSplitMerge.exe]\tSource NIfTI image:\t"       << Parameters.sSourceNii
        << "\n[NiiSplitMerge.exe]\tResult NIfTI image:\t"       << Parameters.sOutNiiPath << Parameters.sOutNiiName
        << "\n[NiiSplitMerge.exe]\tAdvanced Settings:\t"        << (Parameters.sSettingFile.empty() ? "Default" : Parameters.sSettingFile)
        << "\n[NiiSplitMerge.exe] Process:"
        << "\n[NiiSplitMerge.exe]\tImage data preprocessing:"   << Parameters.pPreProMinMax.first << "," << Parameters.pPreProMinMax.second
        << "\n[NiiSplitMerge.exe]\tSplit strategy:\t\t"         << Parameters.uiSplitStrat
        << "\n[NiiSplitMerge.exe]\tNeighboring strategy:\t"     << Parameters.uiNeighStrat
        << "\n[NiiSplitMerge.exe]\tMerge strategy:\t\t"         << Parameters.uiMergeStrat
        << "\n[NiiSplitMerge.exe] Outputs:"
        << "\n[NiiSplitMerge.exe]\tPreprocessed image:\t"       << (Parameters.bPreproNii ? "True" : "False")
        << "\n[NiiSplitMerge.exe]\tSplit image:\t\t"            << (Parameters.bSplitNii ? "True" : "False")
        << "\n[NiiSplitMerge.exe]\tMerge image:\t\t"            << (Parameters.bMergeNii ? "True" : "False")
        << "\n[NiiSplitMerge.exe]\tDetailled Informations:\t"   << (Parameters.bDetails ? "True" : "False") << std::endl;
    
    CNiftiImage* NFIsource = new CNiftiImage(Parameters.sSourceNii);
    try {       //lecture header nifti
        NFIsource->NFIreadHeader();
        std::cout << NFIsource->NFIgetHeaderInfo();
    }
    catch (const CException e) {
        std::cerr << "Erreur : " << e.EXCgetValue() << std::endl;
        return 1;
    }

    CNiftiImageData<uint16_t>* NFIsourceData = new CNiftiImageData<uint16_t>(*NFIsource);
    try {       //lecture données nifti
        unsigned int uiDataType = NFIsource->NFIgetDataType();

        if (uiDataType == 512) {  //NIFTI_TYPE_UINT8, unsigned char

            CNiftiImageData<uint16_t>* NFIextractData = new CNiftiImageData<uint16_t>(*NFIsource);
            NFIextractData->NFDreadData();
            NFIsourceData->NFDconvertDataFrom(*NFIextractData);
        }
        else if (uiDataType == 16) {  //float, unsigned char

            CNiftiImageData<float>* NFIextractData = new CNiftiImageData<float>(*NFIsource);
            NFIextractData->NFDreadData();
            NFIsourceData->NFDconvertDataFrom(*NFIextractData);
        }
        else if (uiDataType == 4) {  //float, unsigned char

            CNiftiImageData<signed short>* NFIextractData = new CNiftiImageData<signed short>(*NFIsource);
            NFIextractData->NFDreadData();
            NFIsourceData->NFDconvertDataFrom(*NFIextractData);
        }
    }
    catch (const CException e) {
        std::cerr << "Erreur : " << e.EXCgetValue() << std::endl;
        return 1;
    }

    try {       //preprocess
        if (Parameters.pPreProMinMax.first == 0 || Parameters.pPreProMinMax.second == 0) {
            NFIsourceData->NFDpreprocess({ 0, (uint16_t)NFIsourceData->NFDgetDataSize() });
            //NFIsourceData->NFDpreprocess({ 0, 10 });
        }
        else {
            NFIsourceData->NFDpreprocess({ Parameters.pPreProMinMax.first, Parameters.pPreProMinMax.second });
        }
        std::cout << NFIsourceData->NFIgetDataInfo();
    } catch (const CException e) {
       std::cerr << "Erreur : " << e.EXCgetValue() << std::endl;
       return 1;
    }

    boost::multi_array<CGrayScale, 3> MAYimageData;
    try {       //to multiArray
        CMultiArrayOperation MAO;
        MAO.MAOcreateFromNifti(MAYimageData, *NFIsourceData);

        if (Parameters.bPreproNii) {
            CNiftiImageData<uint16_t> NFDpreproImage = CNiftiImageData<uint16_t>(NFIsourceData->NFIgetHeader());
            NFDpreproImage.NFDwriteNifti(Parameters.sOutNiiPath + "PrePro" + Parameters.sOutNiiName, MAYimageData);
        }
    }
    catch (const CException e) {
        std::cerr << "Erreur : " << e.EXCgetValue() << std::endl;
        return 1;
    }

    std::vector<CFragment> vFRGresult;
    try {       //split
        std::pair<uint16_t, uint16_t> pMinMax = NFIsourceData->NFDgetMinMax();
        unsigned int uiHomogeneite = static_cast<unsigned int>(pMinMax.first + Parameters.fHomogeneityCrit * (pMinMax.second - pMinMax.first));

        std::cout << "[NiiSplitMerge.exe] Split Strategy parameters :"
            << "\n[NiiSplitMerge.exe]\tSplit strategy:\t\t" << std::to_string(Parameters.uiSplitStrat)
            << "\n[NiiSplitMerge.exe]\tHomogeneity criterion:\t" << std::to_string(uiHomogeneite) << " vxl (" << Parameters.fHomogeneityCrit << "%)"
            << "\n[NiiSplitMerge.exe]\tMinimum chunk dimension:" << std::to_string(Parameters.uiMinSize) << " vxl" << std::endl;

        clock_t cTempsDebut;
        cTempsDebut = clock();

        CMultiArrayOperation MAO;
        vFRGresult = MAO.MAOSplits(MAYimageData, uiHomogeneite, Parameters.uiMinSize, Parameters.uiSplitStrat);

        Times.Split = (double)(clock() - cTempsDebut) / CLOCKS_PER_SEC;

        std::cout << "[NiiSplitMerge.exe] Split results:"
            << "\n[NiiSplitMerge.exe]\tNumber of region:\t" << vFRGresult.size()
            << "\n[NiiSplitMerge.exe]\tExecution time:\t\t" << Times.Split << std::endl;

        if (Parameters.bSplitNii) {
            //write MAYsplitImage split nifti
        }
    } catch (const CException e) {
        std::cerr << "Erreur : " << e.EXCgetValue() << std::endl;
        return 1;
    }

    try {       //merge
        std::pair<uint16_t, uint16_t> pMinMax = NFIsourceData->NFDgetMinMax();
        unsigned int uiHomogeneite = static_cast<unsigned int>(pMinMax.first + Parameters.fHomogeneityCrit * (pMinMax.second - pMinMax.first));

        std::cout << "[NiiSplitMerge.exe] Merge Strategy parameters :"
            << "\n[NiiSplitMerge.exe]\tNeighboring strategy:\t" << std::to_string(Parameters.uiNeighStrat)
            << "\n[NiiSplitMerge.exe]\tMerge strategy:\t\t" << std::to_string(Parameters.uiMergeStrat)
            << "\n[NiiSplitMerge.exe]\tHomogeneity criterion:\t" << std::to_string(uiHomogeneite) << " vxl (" << Parameters.fHomogeneityCrit << "%)"
            << "\n[NiiSplitMerge.exe]\tNumber of region:\t" << vFRGresult.size() << std::endl;

        clock_t cTempsDebut;
        cTempsDebut = clock();

        CGrapheCreator Gs;
        Gs.GCRCreationGraphe(vFRGresult, uiHomogeneite, Parameters.uiMinSize, 0);

        Times.Neighboring = (double)(clock() - cTempsDebut) / CLOCKS_PER_SEC;

        BGLGraphe G = Gs.GCRGetGraphe();
        std::vector<int> component(boost::num_vertices(G));
        std::cout << "[NiiSplitMerge.exe] Split results:"
            << "\n[NiiSplitMerge.exe]\tNumber of region:\t" << boost::connected_components(G, &component[0])
            << "\n[NiiSplitMerge.exe]\tExecution time:\t\t" << Times.Neighboring << std::endl;

        if (Parameters.bMergeNii) {

            typedef boost::multi_array <unsigned int, 3> multi_array_type;
            multi_array_type MAYmergeImage(boost::extents[MAYimageData.shape()[0]][MAYimageData.shape()[1]][MAYimageData.shape()[2]]);

            COperationsSurGraphes OSG;
            MAYmergeImage = OSG.OSGGrapheToMatrice(Gs.GCRGetGraphe());

            CNiftiImageData<uint16_t> NFDmergeImage = CNiftiImageData<uint16_t>(NFIsourceData->NFIgetHeader());
            NFDmergeImage.NFDwriteNiftiUi(Parameters.sOutNiiPath + Parameters.sOutNiiName, MAYmergeImage);
        }
    }
    catch (const CException e) {
        std::cerr << "Erreur : " << e.EXCgetValue() << std::endl;
        return 1;
    }

    try {       //sumary
        //show times

        //si pas detailled, result
    }
    catch (const CException e) {
        std::cerr << "Erreur : " << e.EXCgetValue() << std::endl;
        return 1;
    }


    delete NFIsource;
    delete NFIsourceData;

    return 0;
}