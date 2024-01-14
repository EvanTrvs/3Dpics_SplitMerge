#ifndef C_MULTIARRAYOPERATION_h
#define C_MULTIARRAYOPERATION_h

#include <boost/multi_array.hpp>
#include <vector>
#include "CNiftiImageData.h"
#include "CSplitOperation.h"
#include "CFragment.h"
#include "CGrayScale.h"

#define SEUIL_MIN 2
#define DIMENSION_ERROR 3
#define UNDIFIED_VERSION 4


//template TypeT
class CMultiArrayOperation {

public: 
	/************************************************************************************************************************************************
	***** MAOSplits : Method for call each version of split																						*****
	*************************************************************************************************************************************************
	***** Input : maData : boost::multi_array<CGrayScale, 3> & | uiHomogeneite, uiMinSize, uiVersion : const unsigned int						*****
	***** Precondition : Minimum cube size cannot be equal to 0                                                                                 *****
	***** Output : vFRGLeafs : vector <CFragment>																								*****
	***** Effects : Call version of split managing exceptional cases																			*****
	************************************************************************************************************************************************/
	vector<CFragment> MAOSplits(boost::multi_array<CGrayScale, 3> & maData, unsigned int uiHomogeneite, unsigned int uiMinSize, unsigned int uiVersion);

	/************************************************************************************************************************************************
	***** MAOsetMireData : Method for create Mire																								*****
	*************************************************************************************************************************************************
	***** Input : MultiArrayMire : boost::multi_array<CGrayScale, 3> & | uiDimZ : const unsigned int							 				*****
	***** Precondition : Nothing								                                                                                *****
	***** Output : None																															*****
	***** Effects : Initialize multi_array if the mire.nii is called																			*****
	************************************************************************************************************************************************/
	void MAOsetMireData(unsigned int uiDimZ, boost::multi_array<CGrayScale, 3>& MultiArrayMire);

	/************************************************************************************************************************************************
	***** MAOcreateFromNifti : Method for multi_array from nifti image																			*****
	*************************************************************************************************************************************************
	***** Input : MultiArrayMire : boost::multi_array<CGrayScale, 3> & | NFDparam : const CNiftiImageData<uint16_t> &							*****
	***** Precondition : Nothing								                                                                                *****
	***** Output : None																															*****
	***** Effects : Initialize multi_array from nifti image																						*****
	************************************************************************************************************************************************/
	void MAOcreateFromNifti(boost::multi_array<CGrayScale, 3>& MultiArrayParam, const CNiftiImageData<uint16_t> & NFDparam);

	/************************************************************************************************************************************************
	***** Operator<<																															*****
	*************************************************************************************************************************************************
	***** Input : os : std::ostream & | MultiArrayParam	: const boost::multi_array<CGrayScale, 3> &												*****
	***** Precondition : Nothing								                                                                                *****
	***** Output : std::ostream &																												*****
	***** Effects : OverLoad for print the multi_array																							*****
	************************************************************************************************************************************************/
	friend std::ostream& operator<<(std::ostream& os, const boost::multi_array<CGrayScale, 3> & MultiArrayParam);
};

#endif