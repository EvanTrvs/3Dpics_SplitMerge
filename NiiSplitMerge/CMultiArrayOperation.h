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
	***** MAOSPLITS : Méthode d'appel des méthodes de Splits																					*****
	*************************************************************************************************************************************************
	***** Entrée : maData : boost::multi_array<CGrayScale, 3> & | uiHomogeneite, uiMinSize, uiVersion : unsigned int							*****
	***** Nécessite : La taille minimum des cubes ne peux être égale à 0                                                                        *****
	***** Sortie : vFRGLeafs : vector <CFragment>																								*****
	***** Entraine : Appel les méthodes de Split en gérant les cas d'exception																	*****
	************************************************************************************************************************************************/
	vector<CFragment> MAOSplits(boost::multi_array<CGrayScale, 3> & maData, unsigned int uiHomogeneite, unsigned int uiMinSize, unsigned int uiVersion);

	void MAOsetMireData(unsigned int uiDimZ, boost::multi_array<CGrayScale, 3>& MultiArrayMire);

	void MAOcreateFromNifti(boost::multi_array<CGrayScale, 3>& MultiArrayParam, const CNiftiImageData<uint16_t> & NFDparam);

	friend std::ostream& operator<<(std::ostream& os, const boost::multi_array<CGrayScale, 3> & MultiArrayParam);
};

#endif