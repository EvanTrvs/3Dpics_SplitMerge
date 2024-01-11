#include "CNiftiImage.h"

/**************************************************************************
	 ***** Default class Constructor | CNiftiImage                        *****
	 **************************************************************************
	 ***** Input : None                                                   *****
	 ***** precondtion : None                                             *****
	 ***** Output : None                                                  *****
	 ***** Postcondition : Attribut of this are initialized               *****
	 **************************************************************************/
CNiftiImage::CNiftiImage() {
}

CNiftiImage::CNiftiImage(const std::string pcFilepath) {

	sNFIfilePath = new char[pcFilepath.length() + 1];

	// Copier le contenu de la chaîne de caractères dans le tableau alloué
	strcpy_s(sNFIfilePath, pcFilepath.length() + 1, pcFilepath.c_str());
}

CNiftiImage::CNiftiImage(const std::string pcFilepath, nifti_1_header hdrParam) {

	sNFIfilePath = new char[pcFilepath.length() + 1];

	// Copier le contenu de la chaîne de caractères dans le tableau alloué
	strcpy_s(sNFIfilePath, pcFilepath.length() + 1, pcFilepath.c_str());
	hdrNFIheader = hdrParam;
}

CNiftiImage::CNiftiImage(const CNiftiImage& NFIParam) {
	sNFIfilePath = NFIParam.sNFIfilePath;
	hdrNFIheader = NFIParam.hdrNFIheader;
}

int CNiftiImage::NFIreadHeader() {

	FILE* fp;
	int ret;

	//open header
	fopen_s(&fp, sNFIfilePath, "r");
	if (fp == NULL) {
		throw CException(5);	//error openning file
		return 1;
	}

	//read header
	ret = (int)fread(&hdrNFIheader, MIN_HEADER_SIZE, 1, fp);
	if (ret != 1) {
		throw CException(5); //error reading
		return 1;
	}
	fclose(fp);

	return 0;
}

const nifti_1_header CNiftiImage::NFIgetHeader() const {
	return hdrNFIheader;
}

std::string CNiftiImage::NFIgetHeaderInfo() const {
	std::string sOutMessage;

	sOutMessage.append("[NiiSplitMerge.exe] Image HEADER content :\n");
	sOutMessage.append("[NiiSplitMerge.exe] \tDimensions:\t\t" + std::to_string(hdrNFIheader.dim[0]) + "\n");
	sOutMessage.append("[NiiSplitMerge.exe] \tDimensionX:\t\t" + std::to_string(hdrNFIheader.dim[1]) + " vxl\n");
	sOutMessage.append("[NiiSplitMerge.exe] \tDimensionY:\t\t" + std::to_string(hdrNFIheader.dim[2]) + " vxl\n");
	sOutMessage.append("[NiiSplitMerge.exe] \tDimensionZ:\t\t" + std::to_string(hdrNFIheader.dim[3]) + " vxl\n");
	sOutMessage.append("[NiiSplitMerge.exe] \tDimensionT:\t\t" + std::to_string(hdrNFIheader.dim[4]) + " vxl\n");
	sOutMessage.append("[NiiSplitMerge.exe] \tNumber of Voxels:\t" + std::to_string(hdrNFIheader.dim[1] * hdrNFIheader.dim[2] * hdrNFIheader.dim[3] * hdrNFIheader.dim[4]) + " vxl\n");
	sOutMessage.append("[NiiSplitMerge.exe] \tData Type:\t\t" + NiftiTypeDictionary.find(hdrNFIheader.datatype)->second + "(" + std::to_string(hdrNFIheader.datatype) + ")\n");
	sOutMessage.append("[NiiSplitMerge.exe] \tData size:\t\t" + std::to_string(hdrNFIheader.bitpix) + " bits\n");
	sOutMessage.append("[NiiSplitMerge.exe] \tImage volume:\t\t" + std::to_string((hdrNFIheader.dim[1] * hdrNFIheader.dim[2] * hdrNFIheader.dim[3] * hdrNFIheader.dim[4] * hdrNFIheader.bitpix)/8 ) + " octets\n");

	return sOutMessage;
}

const char* CNiftiImage::NFIgetfilePath() const {
	return sNFIfilePath;
}

unsigned int CNiftiImage::NFIgetDataType() const {
	return hdrNFIheader.datatype;
}