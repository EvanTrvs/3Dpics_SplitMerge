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
#include "CException.h"
#include "MainFactorization.cpp"


/*****************************************************
 ***** Project Information: Image Segmentation 3D *****
 *****************************************************
 ***** Authors:
 ***** - Evan TORTEVOIS
 ***** - Thibaud SCRIBE
 *****
 ***** Project Framework:
 ***** This project is part of the 4th-year Programming and Software Engineering curriculum at École Polytech Tours.
 *****
 ***** Project Purpose:
 ***** The primary goal of this programming project is to implement and optimize the "Split and Merge" image segmentation algorithm for three-dimensional (3D) medical images. The project falls within the scope of the Programming and Software Engineering project in the computer engineering curriculum at École Polytech Tours.
 *****
 ***** Image Segmentation:
 ***** Image segmentation is a crucial process that involves grouping pixels based on certain criteria, forming distinct regions. This automation allows for more precise analysis of medical images, aiding in the detection of tumors and anomalies.
 *****
 ***** Split and Merge Algorithm:
 ***** The "Split and Merge" algorithm is an image processing technique used to segment an image into homogeneous regions. The main idea is to successively divide the image into quadrants based on homogeneity criteria and a granularity threshold. Subsequently, similar regions are merged to create the segmented result.
 *****
 ***** 3D Digital NIfTI Image:
 ***** The processed image format is NIfTI (Neuroimaging Informatics Technology Initiative), commonly used for storing medical imaging data. It supports multidimensional images and is represented by extensions such as .nii or .nii.gz. Applications like ITK-SNAP enable the reading of this format.
 *****************************************************/



//This structure encapsulates the parameters used in the image segmentation program. It includes both user inputs and process-related variables.
typedef struct Parameters {
    // User inputs
    float           fHomogeneityCrit = 0.0f;    // User-defined homogeneity criterion, a float between 0.0 and 1.0.
    unsigned int    uiMinSize = 1;        // Minimum size for segmentation, an unsigned integer.
    std::string     sSourceNii = "mire1"; // Source NIfTI image path or "mireN" for a pre-registered NIfTI of dimension 32x25xN.
    std::string     sOutNiiName = "";       // Name of the output NIfTI image.
    std::string     sOutNiiPath = "mire1_seg"; // Path for storing the segmented output NIfTI image.
    std::string     sSettingFile = "";       // Path to the optional advanced configuration file.

    // Process variables
    std::pair <unsigned int, unsigned int> pPreProMinMax; // Pair of unsigned integers representing pre-processing min and max values.
    unsigned int    uiSplitStrat = 0;        // Splitting strategy during segmentation.
    unsigned int    uiNeighStrat = 0;        // Neighboring strategy during segmentation.
    unsigned int    uiMergeStrat = 0;        // Merging strategy during segmentation.

    // Outputs
    bool            bPreproNii = false;    // Flag indicating whether pre-processing of the NIfTI image is enabled.
    bool            bSplitNii = false;    // Flag indicating whether splitting during segmentation is enabled.
    bool            bMergeNii = true;     // Flag indicating whether merging during segmentation is enabled.
    bool            bDetails = true;     // Flag indicating whether detailed segmentation information is enabled.
} Parameters;


/********************************************************************
 ***** Main Function: Segmentation Program NiiSplitMerge ************
 ********************************************************************
 ***** Description:
 ***** This program performs image segmentation based on specified criteria and settings. It expects certain input parameters, including a homogeneity criterion, a segmentation threshold, source and output NIfTI images, and an optional advanced configuration file. The program validates input conditions and executes the segmentation process.
 *****
 ***** Execution:
 ***** - Homogeneity criterion (H): A float between 0 and 1, representing the proportion of homogeneity respected by the segmentation.
 ***** - Segmentation threshold (S): An integer between 1 and 1000, serving as the threshold for segmentation.
 ***** - Source NIfTI image: An existing file path with the .nii extension, or "mireN" for a pre-registered NIfTI of dimension 32x25xN.
 ***** - Output NIfTI image: A file path with the .nii extension, specifying the name of the output image.
 ***** - Advanced configuration file (optional): An existing file path with the .txt extension, providing additional settings for segmentation.
 *****
 ***** Preconditions:
 ***** - The homogeneity criterion (H) must be a float between 0 and 1.
 ***** - The segmentation threshold (S) must be an integer between 1 and 1000.
 ***** - The source NIfTI image path must be valid, and the associated image must be intact.
 ***** - The output NIfTI image path must be valid, and the specified file will be replaced if it already exists.
 ***** - The optional advanced configuration file, if provided, must be a valid .txt file with appropriate syntax.
 *****
 ***** Usage:
 ***** Execute the program with the specified command-line arguments:
 *****   ./segmentation_program [H] [S] [Source NIfTI] [Output NIfTI] [Optional Settings.txt]
 *****
 ***** Example:
 *****   ./segmentation_program 0.5 500 input_image.nii output_segmented.nii settings.txt
 *****************************************************/
int main(int argc, char* argv[]) {

    // Record the current time for later execution time calculation
    clock_t cExecutionTime = clock();

    // Check the number of command line arguments
    if (argc < 5 || argc > 6) {
        // Display usage information and exit with an error code if the number of arguments is incorrect
        std::cerr << "Usage: " << "./executable.exe" << "[homogeneity criterion : float between 0 and 1] [segmentation threshold : integer between 1 and 1000] [Input NIfTI image.nii] [Output NIfTI image.nii] [optional settings.txt]" << std::endl;
        return 1;
    }

    unsigned int uiMireSize = 0;
    Parameters Parameters; // Structure that encapsulates parameters used in the image segmentation program. It includes both user inputs and process-related variables.

    try {
        // Process and retrieve the values of each command line argument
        Parameters.fHomogeneityCrit = processHomogeneityCriterion(argv[1]);
        Parameters.uiMinSize = processSegmentationThreshold(argv[2]);
        Parameters.sSourceNii = processInputNifti(argv[3]);
        Parameters.sOutNiiName = extractOutputNifti(argv[4]);
        Parameters.sOutNiiPath = extractOutputPath(argv[4]);

        // If the input follows the "mire" format, extract and validate the size
        if (isValidMireFormat(argv[3])) {
            uiMireSize = extractMireSize(Parameters.sSourceNii);
        }
    }
    catch (const CException& EXCparam) {
        // Handle exceptions by displaying an error message and usage information, then exit with an error code
        std::cerr << "Error: " << EXCparam << std::endl;
        std::cerr << "\nUsage: " << "./executable.exe" << " [homogeneity criterion: float between 0 and 1] [segmentation threshold: integer between 1 and 1000] [Input NIfTI image.nii] [Output NIfTI image.nii] [optional settings.txt]" << std::endl;
        return EXCparam.EXCgetValue();
    }

    // If an optional settings file is provided
    if (argc == 6) {
        try {
            // Process and retrieve the path to the optional settings file
            Parameters.sSettingFile = processOptionalSettingsFile(argv[5]);

            // Declare variables for advanced parameters
            std::pair<unsigned int, unsigned int> pPreProMinMax;
            unsigned int uiSplitStrat = 0, uiNeighStrat = 0, uiMergeStrat = 0;
            bool bPreproNii = false, bSplitNii = false, bMergeNii = false, bDetails = false;

            // Read and parse the configuration file, extracting values for various advanced parameters
            readConfigFile(Parameters.sSettingFile, pPreProMinMax, uiSplitStrat, uiNeighStrat, uiMergeStrat, bPreproNii, bSplitNii, bMergeNii, bDetails);

            // Check the validity of advanced parameters
            checkAdvancedParam(pPreProMinMax, uiSplitStrat, uiNeighStrat, uiMergeStrat);

            // Assign the advanced parameters to the Parameters structure
            Parameters.pPreProMinMax = pPreProMinMax;
            Parameters.uiSplitStrat = uiSplitStrat;
            Parameters.uiNeighStrat = uiNeighStrat;
            Parameters.uiMergeStrat = uiMergeStrat;
            Parameters.bPreproNii = bPreproNii;
            Parameters.bSplitNii = bSplitNii;
            Parameters.bMergeNii = bMergeNii;
            Parameters.bDetails = bDetails;
        }
        catch (const CException EXCparam) {
            // Handle exceptions related to advanced settings with appropriate error messages and usage information, then exit with an error code
            std::cerr << "Error: " << EXCparam << std::endl;
            std::cerr << "\nUsage: " << "./executable.exe" << errorMessageAdvancedSettingsFile << std::endl;
            return EXCparam.EXCgetValue();
        }
    }


    std::cout << "[NiiSplitMerge.exe] Program parameters configuration:"
        << "\n[NiiSplitMerge.exe] Inputs:"
        << "\n[NiiSplitMerge.exe]\tHomogeneity criterion:\t"    << Parameters.fHomogeneityCrit << " (" << Parameters.fHomogeneityCrit*100 << "%)"
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
        if (uiMireSize == 0) {
            NFIsource->NFIreadHeader();
        }
        else {
            NFIsource->NFImireHeader(uiMireSize);
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

        if (uiMireSize != 0) {
            CNiftiImageData<uint16_t>* NFImireData = new CNiftiImageData<uint16_t>(*NFIsource);
            NFImireData->NFDgetMireData(uiMireSize);
            NFIsourceData->NFDconvertDataFrom(*NFImireData);
            delete NFImireData;
        }
        else if (uiDataType == 512) {  //NIFTI_TYPE_UINT8, unsigned char
            CNiftiImageData<uint16_t>* NFIextractData = new CNiftiImageData<uint16_t>(*NFIsource);
            NFIextractData->NFDreadData();
            NFIsourceData->NFDconvertDataFrom(*NFIextractData);
            delete NFIextractData;
        }
          else if (uiDataType == 16) {  //float, unsigned char
            CNiftiImageData<float>* NFIextractData = new CNiftiImageData<float>(*NFIsource);
            NFIextractData->NFDreadData();
            NFIsourceData->NFDconvertDataFrom(*NFIextractData);
            delete NFIextractData;
        }
        else if (uiDataType == 4) {  //float, unsigned char
            CNiftiImageData<signed short>* NFIextractData = new CNiftiImageData<signed short>(*NFIsource);
            NFIextractData->NFDreadData();
            NFIsourceData->NFDconvertDataFrom(*NFIextractData);
            delete NFIextractData;
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

            std::cout << "[NiiSplitMerge.exe] Successful Preprocess image writing: " + Parameters.sOutNiiPath + "prepro_" + Parameters.sOutNiiName << std::endl;
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
            << "\n[NiiSplitMerge.exe]\tHomogeneity criterion:\t" << std::to_string(uiHomogeneite) << " (" << Parameters.fHomogeneityCrit*100 << "%)"
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

            std::cout << "[NiiSplitMerge.exe] Successful Split image writing: " + Parameters.sOutNiiPath + "split_" + Parameters.sOutNiiName << std::endl;
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
            << "\n[NiiSplitMerge.exe]\tHomogeneity criterion:\t" << std::to_string(uiHomogeneite) << " (" << Parameters.fHomogeneityCrit * 100 << "%)"
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