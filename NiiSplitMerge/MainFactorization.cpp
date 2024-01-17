#include <iostream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <limits>
#include <cstring>
#include <vector> 
#include <fstream>
#include <algorithm>

#include "CException.h"

//File purpose to refactor main.cpp


#define errorMessageAdvancedSettingsFile R"(
    Error: Invalid content in the optional settings file.
    The file must adhere to the following syntax:

    Parse the file with a "Key"="Value" format per line.
    Lines starting with //, #, or ; are considered comments and will be ignored.
    The following keys are valid and mandatory with their respective values:
    "prepro": Preprocessing range, two natural numbers separated by a comma, prepro=min,max. If no preprocessing is desired, use prepro=0,0.
    "split": Choice of splitting strategy, either 0, 1, or 2 (refer to the strategy guide). Format: split=N.
    "neighbourg": Choice of neighboring strategy, either 0, 1, or 2 (refer to the strategy guide). Format: neighbourg=N.
    "merge": Choice of merging strategy, either 0, 1, or 2 (refer to the strategy guide). Format: merge=N.
    "preproimg": Production or non-production of the preprocessing image. Format: preproimg=true or preproimg=false.
    "splitimg": Production or non-production of the Split segmentation image. Format: splitimg=true or splitimg=false.
    "mergeimg": Production or non-production of the Split and Merge segmentation image. Format: mergeimg=true or mergeimg=false.
    "details": Activation/deactivation of detailed console display. Format: details=true or details=false.

    // Example configuration file
    prepro=0,10
    split=1
    neighbourg=2
    merge=3
    preproimg=true
    splitimg=true
    mergeimg=true
    details=true
    details=false
    )"


 /***************************************
 ***** Function: hasExtension     *****
 ***************************************
 ***** Description:
 ***** Checks if the given filename has a specified extension.
 *****
 ***** Inputs:
 ***** - filename: The full filename including the extension.
 ***** - extension: The extension to check.
 *****
 ***** Output:
 ***** - Returns true if the filename has the specified extension, false otherwise.
 ***************************************/
inline bool hasExtension(const std::string& filename, const std::string& extension) {
    size_t extLen = extension.length();
    size_t filenameLen = filename.length();

    // Check if the filename is long enough to have an extension
    if (filenameLen < extLen) {
        return false;
    }

    // Compare the end of the string with the expected extension
    return std::strcmp(filename.c_str() + filenameLen - extLen, extension.c_str()) == 0;
}

/***************************************
 ***** Function: seperatePathFile *****
 ***************************************
 ***** Description:
 ***** Separates the path and filename from a given path+filename string.
 *****
 ***** Inputs:
 ***** - sPathFile: The input string containing the path and filename.
 *****
 ***** Outputs:
 ***** - sPathFile: The filename part of the input string.
 ***** - sPath: The path part of the input string.
 ***************************************/
inline void separatePathFile(std::string& sPathFile, std::string& sPath) {
    // Extract the path and filename from arg4
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
        sPath = ""; // No path found
    }
}

/***************************************
 ***** Function: isValidMireFormat *****
 ***************************************
 ***** Description:
 ***** Checks if the given string has a valid "mire" format.
 *****
 ***** Input:
 ***** - input: The string to check.
 *****
 ***** Output:
 ***** - Returns true if the string has a valid "mire" format, false otherwise.
 ***** - Throws a CException with an error code 5 and a specific message if the value after "mire" is out of the valid range [1, 10000].
 ***************************************/
inline bool isValidMireFormat(const std::string& input) {
    // Check if the string starts with "mire"
    if (input.substr(0, 4) == "mire") {
        // Check if there is a value after "mire"
        if (input.length() == 4) {
            throw CException(5, "Mire format requires a value between 1 and 10000.");
        }
        // Check that the rest of the string consists only of digits
        for (size_t i = 4; i < input.length(); ++i) {
            if (!std::isdigit(input[i])) {
                throw CException(5, "Mire format requires a value between 1 and 10000.");
                return false;
            }
        }
        return true;
    }
    return false;
}

/***************************************
 ***** Function: toLower          *****
 ***************************************
 ***** Description:
 ***** Converts a string to lowercase.
 *****
 ***** Input:
 ***** - str: The string to be converted.
 *****
 ***** Output:
 ***** - The input string converted to lowercase.
 ***************************************/
inline void toLower(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

/****************************************
 ***** Function: readConfigFile *****
 ****************************************
 ***** Description:
 ***** Reads and parses a configuration file, extracting values for various parameters.
 *****
 ***** Inputs:
 ***** - filename: The path to the configuration file.
 *****
 ***** Outputs:
 ***** - pPreProMinMax: A pair of unsigned integers representing a range.
 ***** - uiSplitStrat: An unsigned integer representing a splitting strategy.
 ***** - uiNeighStrat: An unsigned integer representing a neighboring strategy.
 ***** - uiMergeStrat: An unsigned integer representing a merging strategy.
 ***** - bPreproNii: A boolean indicating whether a preprocessing operation is required.
 ***** - bSplitNii: A boolean indicating whether a splitting operation is required.
 ***** - bMergeNii: A boolean indicating whether a merging operation is required.
 ***** - bDetails: A boolean indicating whether detailed information is required.
 *****
 ***** Preconditions:
 ***** - The file at 'filename' should exist and be readable.
 ***** - The configuration file should follow a specific format, including key-value pairs.
 ***** - The specified parameters should be provided as references.
 *****
 ***** Postconditions:
 ***** - The provided parameters are updated with values extracted from the configuration file.
 ***** - Exceptions may be thrown for various error conditions, such as file not found or invalid format.
 ****************************************/
inline void readConfigFile(const std::string& filename,
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
        throw CException(0, "Unable to open the configuration file.");
    }

    std::string line;
    while (std::getline(configFile, line)) {
        // Ignore comment lines and empty lines
        if (line.empty() || line.substr(0, 2) == "//" || line[0] == '#' || line[0] == ';') {
            continue;
        }

        // Convert the line to lowercase to be case-insensitive
        toLower(line);

        std::istringstream iss(line);
        std::string key, value;

        // Extract the key and value
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            // Remove spaces around the key and value
            key.erase(std::remove_if(key.begin(), key.end(), ::isspace), key.end());
            value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());

            // Parse the key and value
            if (key == "prepro") {
                std::istringstream valueStream(value);
                char comma;
                if (valueStream >> pPreProMinMax.first >> comma >> pPreProMinMax.second && comma == ',') {
                    bPreproNii = true;
                }
                else {
                    throw CException(1, "Invalid format for the 'prepro' key.");
                }
            }
            else if (key == "split") {
                try {
                    size_t pos;
                    uiSplitStrat = std::stoi(value, &pos);
                    if (pos != value.size()) {
                        throw CException(2, "Value incompatible with the 'split' key, must be an integer.");
                    }
                    bSplitNii = true;
                }
                catch (const std::invalid_argument&) {
                    throw CException(3, "Value incompatible with the 'split' key, must be an integer.");
                }
            }
            else if (key == "neighbourg") {
                try {
                    size_t pos;
                    uiNeighStrat = std::stoi(value, &pos);
                    if (pos != value.size()) {
                        throw CException(4, "Value incompatible with the 'neighbourg' key, must be an integer.");
                    }
                    // ...
                }
                catch (const std::invalid_argument&) {
                    throw CException(5, "Value incompatible with the 'neighbourg' key, must be an integer.");
                }
            }
            else if (key == "merge") {
                try {
                    size_t pos;
                    uiMergeStrat = std::stoi(value, &pos);
                    if (pos != value.size()) {
                        throw CException(6, "Value incompatible with the 'merge' key, must be an integer.");
                    }
                    bMergeNii = true;
                }
                catch (const std::invalid_argument&) {
                    throw CException(7, "Value incompatible with the 'merge' key, must be an integer.");
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
                throw CException(8, ("Unrecognized key '" + key + "'.").c_str());
            }
        }
        else {
            throw CException(9, ("Invalid format for the line '" + line + "'.").c_str());
        }
    }
}

/************************************************************
 * Function to check and process the homogeneity criterion argument
 *
 * Input: const char* arg - Argument to be processed
 * Precondition: None
 * Output: float - Processed value of the homogeneity criterion
 * Postcondition: Throws CException on invalid input, otherwise returns the processed value
 ************************************************************/
inline float processHomogeneityCriterion(const char* arg) {
    float value = std::stof(arg);
    if (value < 0.0f || value > 1.0f) {
        throw CException(1, "Invalid homogeneity criterion value. It should be a float between 0 and 1.");
    }
    return value;
}

/************************************************************
 * Function to check and process the segmentation threshold argument
 *
 * Input: const char* arg - Argument to be processed
 * Precondition: None
 * Output: int - Processed value of the segmentation threshold
 * Postcondition: Throws CException on invalid input, otherwise returns the processed value
 ************************************************************/
inline int processSegmentationThreshold(const char* arg) {
    int value = std::stoi(arg);
    if (value < 1 || value > 1000) {
        throw CException(2, "Invalid segmentation threshold value. It should be an integer between 1 and 1000.");
    }
    return value;
}

/************************************************************
 * Function to check and process the input NIfTI image argument
 *
 * Input: const char* arg - Argument to be processed
 * Precondition: None
 * Output: std::string - Processed value of the input NIfTI image
 * Postcondition: Throws CException on invalid input, otherwise returns the processed value
 ************************************************************/
inline std::string processInputNifti(const char* arg) {
    std::string value(arg);

    if (!hasExtension(value, ".nii") && !isValidMireFormat(arg)) {
        throw CException(3, "Invalid input NIfTI image. It should have the extension '.nii'. or 'mireX' X an integer");
    }
    return value;
}

/************************************************************
 * Function to check and process the optional settings file argument
 *
 * Input: const char* arg - Argument to be processed
 * Precondition: None
 * Output: std::string - Processed value of the optional settings file
 * Postcondition: Throws CException on invalid input, otherwise returns the processed value
 ************************************************************/
inline std::string processOptionalSettingsFile(const char* arg) {
    std::string value(arg);
    if (!hasExtension(value, ".txt")) {
        throw CException(5, "Invalid optional settings file. It should have the extension '.txt'.");
    }
    return value;
}


/**********************************************************************************************
 ***** extractOutputNifti                                                                  *****
 **********************************************************************************************
 ***** Input : const char* arg			                                                  *****
 ***** Precondition: None                                                                 *****
 ***** Output:  std::string                                                               *****
 ***** Postcondition : Extracts the output NIfTI image name from the input path,       *****
 *****                  performs necessary checks, and returns the extracted name.      *****
 **********************************************************************************************/
inline std::string extractOutputNifti(const char* arg) {
    // Check if arg is not null
    if (!arg) {
        throw CException(1, "Argument is null");
    }

    // Convert const char* to std::string
    std::string sPathFile(arg);

    // Check if the conversion is successful
    if (sPathFile.empty()) {
        throw CException(2, "Failed to convert const char* to std::string");
    }

    // Check if the path has a valid format with the .nii extension
    if (!hasExtension(sPathFile, ".nii")) {
        throw CException(4, "Invalid output NIfTI image. It should have the extension '.nii'.");
    }

    //read path part
    size_t lastSlash = sPathFile.find_last_of('/');
    size_t lastBackslash = sPathFile.find_last_of('\\');

    if (lastSlash > 99999999) lastSlash = 0;
    if (lastBackslash > 99999999) lastBackslash = 0;
    size_t lastSeparator = std::max(lastSlash, lastBackslash);

    if (lastSeparator) {
        sPathFile = sPathFile.substr(lastSeparator + 1);
    }
    else {
        sPathFile = ""; // No path found
    }

    return sPathFile;
}

/**********************************************************************************************
 ***** extractOutputPath                                                                   *****
 **********************************************************************************************
 ***** Input : const char* arg                                                             *****
 ***** Precondition: None                                                                  *****
 ***** Output: std::string                                                                *****
 ***** Postcondition : Extracts the path from the given argument, verifies conversion,   *****
 *****                   checks for valid extension (.nii), and returns the path.         *****
 **********************************************************************************************
 ***** Exceptions:                                                                         *****
 *****   1. Throws CException with code 1 if the input argument is null.                 *****
 *****   2. Throws CException with code 2 if the conversion from const char* to           *****
 *****      std::string fails.                                                            *****
 *****   3. Throws CException with code 4 if the output NIfTI image does not have        *****
 *****      the required extension '.nii'.                                               *****
 **********************************************************************************************/
inline std::string extractOutputPath(const char* arg) {
    // Check if arg is not null
    if (!arg) {
        throw CException(1, "Argument is null");
    }

    // Convert const char* to std::string
    std::string sPathFile(arg);

    // Check if the conversion is successful
    if (sPathFile.empty()) {
        throw CException(2, "Failed to convert const char* to std::string");
    }

    // Check if the path has a valid format with the .nii extension
    if (!hasExtension(sPathFile, ".nii")) {
        throw CException(4, "Invalid output NIfTI image. It should have the extension '.nii'.");
    }

    //read path part
    size_t lastSlash = sPathFile.find_last_of('/');
    size_t lastBackslash = sPathFile.find_last_of('\\');

    if (lastSlash > 99999999) lastSlash = 0;
    if (lastBackslash > 99999999) lastBackslash = 0;
    size_t lastSeparator = std::max(lastSlash, lastBackslash);

    std::string sPath;
    if (lastSeparator) {
        sPath = sPathFile.substr(0, lastSeparator + 1);
    } else {
        sPath = ""; // No path found
    }

    return sPath;
}

/**********************************************************************************************
 ***** checkAdvancedParam                                                                 *****
 **********************************************************************************************
 ***** Input : const std::pair<unsigned int, unsigned int>& pPreProMinMax                   *****
 *****         unsigned int uiSplitStrat, uiNeighStrat, uiMergeStrat                         *****
 *****         bool bPreproNii, bSplitNii, bMergeNii, bDetails                               *****
 ***** Precondition: None                                                                 *****
 ***** Output:  None                                                                      *****
 ***** Postcondition : Checks the validity of advanced parameters and throws a CException  *****
 *****                  if any constraint is violated.                                     *****
 **********************************************************************************************/
inline void checkAdvancedParam(const std::pair<unsigned int, unsigned int>& pPreProMinMax,
    unsigned int uiSplitStrat,
    unsigned int uiNeighStrat,
    unsigned int uiMergeStrat) {
    // Check pPreProMinMax
    if (pPreProMinMax.first >= pPreProMinMax.second) {
        throw CException(6, "Invalid range for pre-processing min and max values.");
    }

    // Check uiSplitStrat, uiNeighStrat, uiMergeStrat
    if (uiSplitStrat > 2 || uiNeighStrat > 2 || uiMergeStrat > 2) {
        throw CException(7, "Invalid strategy value. It should be 0, 1, or 2.");
    }
}

/**********************************************************************************************
 ***** extractMireSize                                                                    *****
 **********************************************************************************************
 ***** Input : const std::string& input                                                   *****
 ***** Precondition: None                                                                 *****
 ***** Output:  unsigned int                                                              *****
 ***** Postcondition : Extracts and validates the size from the input string.             *****
 *****                   Throws CException on invalid input or out-of-range value.        *****
**********************************************************************************************/
inline unsigned int extractMireSize(const std::string& input) {
    // Check if the string follows the format "mire" + integer
    if (isValidMireFormat(input)) {
        try {
            // Extract the integer from the substring starting at position 4
            int extractedValue = std::stoi(input.substr(4));

            // Check if the conversion to unsigned int is possible
            if (extractedValue < 1 || extractedValue > 10000) {
                throw CException(1, "Extracted value is out of range. It should be between 1 and 10000.");
            }

            return static_cast<unsigned int>(extractedValue);
        }
        catch (const std::invalid_argument&) {
            throw CException(2, "Invalid mire size format. The substring after 'mire' should be a valid integer.");
        }
        catch (const std::out_of_range&) {
            throw CException(3, "Extracted value is out of range. It should be between 1 and 10000.");
        }
    }
    else {
        throw CException(4, "Invalid mire format. It should start with 'mire' followed by a valid integer.");
    }
}

