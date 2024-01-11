#ifndef C_NIFTIIMAGEDATA_H
#define C_NIFTIIMAGEDATA_H

#include "CException.h"
#include "CNiftiImage.h"
#include "nifti1.h"
#include "CGrayScale.h"
#include <vector>
#include <algorithm>

#define NIFTI_DATA_ERROR 15
#define NIFTI_DATA_NOT_SUPPORT 16


template <typename TypeT>
class CNiftiImageData : public CNiftiImage {
	//Atributes
private:

	std::vector<TypeT> vTypeTNFDdata;	//struct data for Nifti

	//Constructors & Destructor
public:

	/**************************************************************************
	 ***** Default class Constructor | CNiftiImageData                    *****
	 **************************************************************************
	 ***** Input : None                                                   *****
	 ***** precondtion : None                                             *****
	 ***** Output : None                                                  *****
	 ***** Postcondition : Attribut of this are initialized               *****
	 **************************************************************************/
	CNiftiImageData();

	CNiftiImageData(const CNiftiImage& NFDparam);

	CNiftiImageData(const nifti_1_header & hdrParam);

	template <typename Type>
	CNiftiImageData(const CNiftiImageData<Type>& NFDparam);

	//Methods
public:

	int NFDreadData();

	int NFDwriteNifti(std::string sPathFile, boost::multi_array<CGrayScale, 3>& MultiArrayParam);

	int NFDwriteNiftiUi(std::string sPathFile, boost::multi_array<unsigned int, 3>& MultiArrayParam);

	template <typename OtherTypeT>
	int NFDconvertDataFrom(const CNiftiImageData<OtherTypeT>& NFDparam);

	std::vector<TypeT> NFDgetData() const;

	rsize_t NFDgetDataSize() const;

	std::pair<TypeT, TypeT> NFDgetMinMax() const;

	int NFDpreprocess(std::pair < uint16_t, uint16_t> pMinMax);

	std::string NFIgetDataInfo() const;

};

#include "CNiftiImageData.ipp"

#endif	//C_NIFTIIMAGEDATA_H
