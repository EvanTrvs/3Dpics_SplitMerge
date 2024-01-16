#include <iostream>
#include <cstdlib>
#include <sstream>
#include <limits>
#include <cstring>
#include <vector> 
#include <fstream>
#include <algorithm>
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
    unsigned int    uiMinSize       =1;
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
    bool            bPreproNii  =true;
    bool            bSplitNii   =false;
    bool            bMergeNii   =true;
    bool            bDetails    =true;
} Parameters;

//MainFactorization.cpp
bool hasExtension(const std::string& filename, const std::string& extension);

void seperatePathFile(std::string& sPathFile, std::string& sPath);

bool isValidMireFormat(const std::string& input);

void toLower(std::string& str);

// Fonction pour lire et analyser le fichier de configuration
bool readConfigFile(const std::string& filename, std::pair<unsigned int, unsigned int>& pPreProMinMax,
    unsigned int& uiSplitStrat, unsigned int& uiNeighStrat, unsigned int& uiMergeStrat,
    bool& bPreproNii, bool& bSplitNii, bool& bMergeNii, bool& bDetails);


int main(int argc, char* argv[]) {

    clock_t cExecutionTime;
    cExecutionTime = clock();

    // Check number of arguments
    if (argc < 5 || argc > 6) {
        std::cerr << "Usage: " << argv[0] << " [float entre 0 et 1] [entier entre 1 et 1000] [Input Nifti image.nii] [Output Nifti image.nii] [optionel settings.txt]" << std::endl;
        return 1;
    }

    // Convertir les arguments et vérifier les conditions
    float arg1;
    int arg2;
    std::string arg3, arg4, arg5, sOutPath;
    unsigned int mireValue = 0;

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

        // Vérifier si arg3 suit le format "mire" + entier
        if (isValidMireFormat(arg3)) {
            // Extraire l'entier à partir de la chaîne
            mireValue = std::stoi(arg3.substr(4));
            // Utilisez mireValue comme nécessaire
        }
        // Vérifier que les fichiers .nii existent et ont la bonne extension
        else if (!hasExtension(arg3, ".nii") || !hasExtension(arg4, ".nii")) {
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
    } catch (const std::exception& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    Parameters Parameters;
    Parameters.fHomogeneityCrit = arg1;
    Parameters.uiMinSize = arg2;
    Parameters.sSourceNii = arg3;
    Parameters.sOutNiiName = arg4;
    Parameters.sOutNiiPath = sOutPath;
    Parameters.sSettingFile = arg5;

    if (argc == 6) {
        
        std::pair<unsigned int, unsigned int> pPreProMinMax;
        unsigned int uiSplitStrat = 0, uiNeighStrat = 0, uiMergeStrat = 0;
        bool bPreproNii = false, bSplitNii = false, bMergeNii = false, bDetails = false;

        if (readConfigFile("exemple.txt", pPreProMinMax, uiSplitStrat, uiNeighStrat, uiMergeStrat, bPreproNii, bSplitNii, bMergeNii, bDetails)) {
            // Utiliser les valeurs lues
            Parameters.pPreProMinMax = pPreProMinMax;
            Parameters.uiSplitStrat = uiSplitStrat;
            Parameters.uiNeighStrat = uiNeighStrat;
            Parameters.uiMergeStrat = uiMergeStrat;
            Parameters.bPreproNii = bPreproNii;
            Parameters.bSplitNii = bSplitNii;
            Parameters.bMergeNii = bMergeNii;
            Parameters.bDetails = bDetails;
        }
    }

    std::cout << "[NiiSplitMerge.exe] Program parameters configuration:"
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
        if (mireValue == 0) {
            NFIsource->NFIreadHeader();
        }
        else {
            NFIsource->NFImireHeader(mireValue);
        }
        std::cout << std::endl;
        std::cout << NFIsource->NFIgetHeaderInfo();
    }
    catch (const CException e) {
        std::cerr << "Erreur : " << e.EXCgetValue() << std::endl;
        return 1;
    }

    CNiftiImageData<uint16_t>* NFIsourceData = new CNiftiImageData<uint16_t>(*NFIsource);
    try {       //lecture données nifti
        unsigned int uiDataType = NFIsource->NFIgetDataType();

        if (mireValue != 0) {
            CNiftiImageData<uint16_t>* NFImireData = new CNiftiImageData<uint16_t>(*NFIsource);
            NFImireData->NFDgetMireData(mireValue);
            NFIsourceData->NFDconvertDataFrom(*NFImireData);
        }
        else if (uiDataType == 512) {  //NIFTI_TYPE_UINT8, unsigned char
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
        else {
            throw CException(5);
        }
    }
    catch (const CException e) {
        std::cerr << "Erreur : " << e.EXCgetValue() << std::endl;
        return 1;
    }

    try {       //preprocess
        if (Parameters.pPreProMinMax.first == 0 && Parameters.pPreProMinMax.second == 0) {
            NFIsourceData->NFDpreprocess({ 0, (uint16_t)NFIsourceData->NFDgetDataSize() });
            //NFIsourceData->NFDpreprocess({ 0, 10 });
        }
        else {
            std::cout << NFIsourceData->NFIgetDataInfo();
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
            NFDpreproImage.NFDwriteNifti(Parameters.sOutNiiPath + "prepro" + Parameters.sOutNiiName, MAYimageData);

            std::cout << "[NiiSplitMerge.exe] Successful Preprocess image writing: " + Parameters.sOutNiiPath + "prepro" + Parameters.sOutNiiName << std::endl;
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
        std::cout << std::endl;
        std::cout << "[NiiSplitMerge.exe] Split Strategy parameters :"
            << "\n[NiiSplitMerge.exe]\tSplit strategy:\t\t" << std::to_string(Parameters.uiSplitStrat)
            << "\n[NiiSplitMerge.exe]\tHomogeneity criterion:\t" << std::to_string(uiHomogeneite) << " (" << Parameters.fHomogeneityCrit << "%)"
            << "\n[NiiSplitMerge.exe]\tMinimum chunk dimension:" << std::to_string(Parameters.uiMinSize) << " vxl" << std::endl;

        clock_t cTempsDebut;
        cTempsDebut = clock();

        CMultiArrayOperation MAO;
        vFRGresult = MAO.MAOSplits(MAYimageData, uiHomogeneite, Parameters.uiMinSize, Parameters.uiSplitStrat);

        double elapsed = (double)(clock() - cTempsDebut) / CLOCKS_PER_SEC;

        std::cout << "[NiiSplitMerge.exe] Split results:"
            << "\n[NiiSplitMerge.exe]\tNumber of region:\t" << vFRGresult.size()
            << "\n[NiiSplitMerge.exe]\tExecution time:\t\t" << elapsed << std::endl;

        if (Parameters.bSplitNii) {
            typedef boost::multi_array <CGrayScale, 3> multi_array_type;
            multi_array_type MAYsplitImage(boost::extents[MAYimageData.shape()[0]][MAYimageData.shape()[1]][MAYimageData.shape()[2]]);

            MAO.MultiArrayFromFragments(MAYsplitImage, vFRGresult);

            CNiftiImageData<uint16_t> NFDsplitImage = CNiftiImageData<uint16_t>(NFIsourceData->NFIgetHeader());
            NFDsplitImage.NFDwriteNifti(Parameters.sOutNiiPath + "split" + Parameters.sOutNiiName, MAYsplitImage);

            std::cout << "[NiiSplitMerge.exe] Successful Split image writing: " + Parameters.sOutNiiPath + "split" + Parameters.sOutNiiName << std::endl;
        }
    } catch (const CException e) {
        std::cerr << "Erreur : " << e.EXCgetValue() << std::endl;
        return 1;
    }

    int iNumberROI;
    try {       //merge
        std::pair<uint16_t, uint16_t> pMinMax = NFIsourceData->NFDgetMinMax();
        unsigned int uiHomogeneite = static_cast<unsigned int>(pMinMax.first + Parameters.fHomogeneityCrit * (pMinMax.second - pMinMax.first));
        std::cout << std::endl;
        std::cout << "[NiiSplitMerge.exe] Merge Strategy parameters :"
            << "\n[NiiSplitMerge.exe]\tNeighboring strategy:\t" << std::to_string(Parameters.uiNeighStrat)
            << "\n[NiiSplitMerge.exe]\tMerge strategy:\t\t" << std::to_string(Parameters.uiMergeStrat)
            << "\n[NiiSplitMerge.exe]\tHomogeneity criterion:\t" << std::to_string(uiHomogeneite) << " (" << Parameters.fHomogeneityCrit << "%)"
            << "\n[NiiSplitMerge.exe]\tNumber of region:\t" << vFRGresult.size() << std::endl;

        CGrapheCreator Gs;
        Gs.GCRCreationGraphe(vFRGresult, uiHomogeneite, Parameters.uiMinSize, Parameters.uiNeighStrat, Parameters.uiMergeStrat);

        BGLGraphe G = Gs.GCRGetGraphe();
        std::vector<int> component(boost::num_vertices(G));
        iNumberROI = boost::connected_components(G, &component[0]);

        if (Parameters.bMergeNii) {

            typedef boost::multi_array <unsigned int, 3> multi_array_type;
            multi_array_type MAYmergeImage(boost::extents[MAYimageData.shape()[0]][MAYimageData.shape()[1]][MAYimageData.shape()[2]]);

            COperationsSurGraphes OSG;
            MAYmergeImage = OSG.OSGGrapheToMatrice(Gs.GCRGetGraphe());

            CNiftiImageData<uint16_t> NFDmergeImage = CNiftiImageData<uint16_t>(NFIsourceData->NFIgetHeader());
            NFDmergeImage.NFDwriteNiftiUi(Parameters.sOutNiiPath + Parameters.sOutNiiName, MAYmergeImage);

            std::cout << "[NiiSplitMerge.exe] Successful Merge image writing: " + Parameters.sOutNiiPath + Parameters.sOutNiiName << std::endl;
        }
    }
    catch (const CException e) {
        std::cerr << "Erreur : " << e.EXCgetValue() << std::endl;
        return 1;
    }

    try {       //sumary
        std::cout << std::endl;
        double elapsed = (double)(clock() - cExecutionTime) / CLOCKS_PER_SEC;

        std::cout << "[NiiSplitMerge.exe] Program results :"
            << "\n[NiiSplitMerge.exe]\tSource Image:\t\t" << MAYimageData.shape()[0] << "x" << MAYimageData.shape()[1] << "x" << MAYimageData.shape()[2]
            << ", " << MAYimageData.shape()[0] * MAYimageData.shape()[1] * MAYimageData.shape()[2] << "vxl (" << Parameters.sSourceNii << ")"
            << "\n[NiiSplitMerge.exe]\tHomogeneity criterion:\t" << Parameters.fHomogeneityCrit
            << "\n[NiiSplitMerge.exe]\tMinimum chunk dimension:" << Parameters.uiMinSize
            << "\n[NiiSplitMerge.exe]\tNumber of ROI:\t\t" << iNumberROI
            << "\n[NiiSplitMerge.exe]\tTotal execution time:\t" << elapsed << "sec" << std::endl;
    }
    catch (const CException e) {
        std::cerr << "Erreur : " << e.EXCgetValue() << std::endl;
        return 1;
    }


    delete NFIsource;
    delete NFIsourceData;

    return 0;
}