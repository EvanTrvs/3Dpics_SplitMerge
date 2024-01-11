#ifndef C_NIFTIIMAGE_H
#define C_NIFTIIMAGE_H

#include "CException.h"
#include <string>
#include "nifti1.h"
#include <map>

#define NIFTI_HEADER_ERROR 10
#define NIFTI_HEADER_NOT_SUPPORT 11

#define MIN_HEADER_SIZE 348
#define NII_HEADER_SIZE 352

const std::map<int, std::string> NiftiTypeDictionary = {
	{2, "NIFTI_TYPE_UINT8"}, {4, "NIFTI_TYPE_INT16"}, {8, "NIFTI_TYPE_INT32"},
	{16, "NIFTI_TYPE_FLOAT32"}, {32, "NIFTI_TYPE_COMPLEX64"}, {64, "NIFTI_TYPE_FLOAT64"},
	{128, "NIFTI_TYPE_RGB24"}, {256, "NIFTI_TYPE_INT8"}, {512, "NIFTI_TYPE_UINT16"},
	{768, "NIFTI_TYPE_UINT32"}, {1024, "NIFTI_TYPE_INT64"}, {1280, "NIFTI_TYPE_UINT64"},
	{1536, "NIFTI_TYPE_FLOAT128"}, {1792, "NIFTI_TYPE_COMPLEX128"}, {2048, "NIFTI_TYPE_COMPLEX256"},
	{2304, "NIFTI_TYPE_RGBA32"}
};

class CNiftiImage {
	//Atributes
protected:

	char * sNFIfilePath;				//Nifti file path

	nifti_1_header hdrNFIheader;			//struct header for Nifti (nifti1.h)

	//Constructors & Destructor
public:

	/**************************************************************************
	 ***** Default class Constructor | CNiftiImage                        *****
	 **************************************************************************
	 ***** Input : None                                                   *****
	 ***** precondtion : None                                             *****
	 ***** Output : None                                                  *****
	 ***** Postcondition : Attribut of this are initialized               *****
	 **************************************************************************/
	CNiftiImage();

	CNiftiImage(const std::string pcFilepath);

	CNiftiImage(const std::string pcFilepath, nifti_1_header hdrParam);

	CNiftiImage(const CNiftiImage & NIIParam);
	//Methods
public:
	
	int NFIreadHeader();

	//plein de getter / setter

	const nifti_1_header NFIgetHeader() const;

	std::string NFIgetHeaderInfo() const;

	const char* NFIgetfilePath() const;

	unsigned int NFIgetDataType() const;
};

#endif	//C_NIFTIIMAGE_H