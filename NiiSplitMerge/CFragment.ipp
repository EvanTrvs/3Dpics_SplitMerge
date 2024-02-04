#pragma once
 
#include <iostream> 

using namespace std;

#include "CFragment.h"

/************************************************************************************************************************************************
***** Default Class Constructor																												*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Initialize variables to null / O					                                                                        *****
************************************************************************************************************************************************/
inline CFragment::CFragment() {

	//Variables Initialization
	pmaGSLFRGMultiArray = nullptr;

	vuiFRGConer = {};
	vuiFRGDimension = {};

	puiFRGMinMax.first = 0;
	puiFRGMinMax.second = 0;

	uiFRGConnexite = 0;
}

/************************************************************************************************************************************************
***** Class Constructor																														*****
*************************************************************************************************************************************************
***** Input : pmaCLRMultiArray : * boost::multi_array <CGrayScale, 3>, vuiFRGConer et vuiFRGDimension : vector <unsigned int>				*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Initialize variables with the provided parameter					                                                        *****
************************************************************************************************************************************************/
inline CFragment::CFragment(boost::multi_array <CGrayScale, 3> * pmaGSLMultiArray, vector <unsigned int> vuiConer, vector <unsigned int> vuiDimension) {

	//Variables Initialization
	pmaGSLFRGMultiArray = pmaGSLMultiArray;

	//Verification if coos + dimensions are within the dimensions of the MultiArray
	if (vuiConer[0] + vuiDimension[0] > pmaGSLMultiArray->shape()[0] ||
		vuiConer[1] + vuiDimension[1] > pmaGSLMultiArray->shape()[1] ||
		vuiConer[2] + vuiDimension[2] > pmaGSLMultiArray->shape()[2]) {

		CException EXCErreur;
		EXCErreur.EXCModifierValeur(TAILLE_DIM);
		throw (EXCErreur);
	}

	vuiFRGConer = vuiConer;
	vuiFRGDimension = vuiDimension;

	//Initialization of other variables to 0
	uiFRGConnexite = 0;
	puiFRGMinMax.first = 0;
	puiFRGMinMax.second = 0;
}

/****************************************************************************************************************************************************************************************
***** Class Constructor																																								*****
*****************************************************************************************************************************************************************************************
***** Input : pmaCLRMultiArray : * boost::multi_array <CGrayScale, 3>, vuiFRGConer et vuiFRGDimension : vector <unsigned int> | puiMinMax : pair<unsigned int, unsigned int>		*****
***** Precondition : Nothing																																						*****
***** Output : None																																									*****
***** Effects : Initialize variables with the provided parameter																													*****
****************************************************************************************************************************************************************************************/
inline CFragment::CFragment(boost::multi_array <CGrayScale, 3> * pmaCLRMultiArray, vector <unsigned int> vuiConer, vector <unsigned int> vuiDimension, unsigned int uiConnexite, std::pair<unsigned int, unsigned int> puiMinMax) {

	//Variables Initialization
	pmaGSLFRGMultiArray = pmaCLRMultiArray;

	//Verification if coos + dimensions are within the dimensions of the MultiArray
	if (vuiConer[0] + vuiDimension[0] > pmaCLRMultiArray->shape()[0] ||
		vuiConer[1] + vuiDimension[1] > pmaCLRMultiArray->shape()[1] ||
		vuiConer[2] + vuiDimension[2] > pmaCLRMultiArray->shape()[2]) {

		CException EXCErreur;
		EXCErreur.EXCModifierValeur(TAILLE_DIM);
		throw (EXCErreur);
	}

	vuiFRGConer = vuiConer;
	vuiFRGDimension = vuiDimension;

	uiFRGConnexite = uiConnexite;
	puiFRGMinMax = puiMinMax;
}

/************************************************************************************************************************************************
***** Operator=																																*****
*************************************************************************************************************************************************
***** Input : FRGFragment : const & CFragment																								*****
***** Precondition : Nothing                                                                                                                *****
***** Output : the object itself																											*****
***** Effects : Initialize variables respectively with FRGFragment's variables 					                                            *****
************************************************************************************************************************************************/
inline CFragment& CFragment::operator= (CFragment const& FRGFragment) {

	//Variables Initialization
	pmaGSLFRGMultiArray = FRGFragment.pmaGSLFRGMultiArray; //Pointer on the same object

	//Verification if coos + dimensions are within the dimensions of the MultiArray
	if (FRGFragment.vuiFRGConer[0] + FRGFragment.vuiFRGDimension[0] > FRGFragment.pmaGSLFRGMultiArray->shape()[0] ||
		FRGFragment.vuiFRGConer[1] + FRGFragment.vuiFRGDimension[1] > FRGFragment.pmaGSLFRGMultiArray->shape()[1] ||
		FRGFragment.vuiFRGConer[2] + FRGFragment.vuiFRGDimension[2] > FRGFragment.pmaGSLFRGMultiArray->shape()[2]) {

		CException EXCErreur;
		EXCErreur.EXCModifierValeur(TAILLE_DIM);
		throw (EXCErreur);
	}

	vuiFRGConer = FRGFragment.vuiFRGConer;
	vuiFRGDimension = FRGFragment.vuiFRGDimension;

	puiFRGMinMax = FRGFragment.puiFRGMinMax;
	uiFRGConnexite = FRGFragment.uiFRGConnexite;

	//Return Itself
	return *this;
}

/************************************************************************************************************************************************
***** Class Copie Constructor																												*****
*************************************************************************************************************************************************
***** Input : FRGFragment : const & CFragment																								*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Initialize variables respectively with FRGFragment's variables 					                                            *****
************************************************************************************************************************************************/
inline CFragment::CFragment(CFragment const& FRGFragment) {

	//Variables Initialization
	pmaGSLFRGMultiArray = FRGFragment.pmaGSLFRGMultiArray; //Pointer on the same object

	//Verification if coos + dimensions are within the dimensions of the MultiArray
	if (FRGFragment.vuiFRGConer[0] + FRGFragment.vuiFRGDimension[0] > FRGFragment.pmaGSLFRGMultiArray->shape()[0] ||
		FRGFragment.vuiFRGConer[1] + FRGFragment.vuiFRGDimension[1] > FRGFragment.pmaGSLFRGMultiArray->shape()[1] ||
		FRGFragment.vuiFRGConer[2] + FRGFragment.vuiFRGDimension[2] > FRGFragment.pmaGSLFRGMultiArray->shape()[2]) {

		CException EXCErreur;
		EXCErreur.EXCModifierValeur(TAILLE_DIM);
		throw (EXCErreur);
	}

	vuiFRGConer = FRGFragment.vuiFRGConer;
	vuiFRGDimension = FRGFragment.vuiFRGDimension;

	puiFRGMinMax = FRGFragment.puiFRGMinMax;
	uiFRGConnexite = FRGFragment.uiFRGConnexite;
}

/************************************************************************************************************************************************
***** FRGGetMatrice : Reading Accessor																										*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : pmaGSLFRGMultiArray : boost::multi_array<CGrayScale, 3> *																	*****
***** Effects : Return variable pmaGSLFRGMultiArray 																						*****
************************************************************************************************************************************************/
inline boost::multi_array<CGrayScale, 3> * CFragment::FRGGetMatrice() {

	return pmaGSLFRGMultiArray;
}

/************************************************************************************************************************************************
***** FRGGetDimensionMatrice : Reading Accessor																								*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : vuiDimMatrice : vector <unsigned int>																						*****
***** Effects : Return the dimensions of the variable pmaGSLFRGMultiArray 																	*****
************************************************************************************************************************************************/
inline vector <unsigned int> CFragment::FRGGetDimensionMatrice() const {

	return { (unsigned int)pmaGSLFRGMultiArray->shape()[0], (unsigned int)pmaGSLFRGMultiArray->shape()[1], (unsigned int)pmaGSLFRGMultiArray->shape()[2] };
}

/************************************************************************************************************************************************
***** FRGGetElement : Reading Accessor																										*****
*************************************************************************************************************************************************
***** Input : uiX, uiY, uiZ : unsigned int																									*****
***** Precondition : Nothing                                                                                                                *****
***** Output : uiElement : unsigned int																										*****
***** Effects : Return an element of the variable pmaGSLFRGMultiArray 																		*****
************************************************************************************************************************************************/
inline CGrayScale CFragment::FRGGetElement(unsigned int uiX, unsigned int uiY, unsigned int uiZ) const {

	//Verification if coos are within the dimensions of the MultiArray
	if (uiX > pmaGSLFRGMultiArray->shape()[0] ||
		uiY > pmaGSLFRGMultiArray->shape()[1] ||
		uiZ > pmaGSLFRGMultiArray->shape()[2]) {

		CException EXCErreur;
		EXCErreur.EXCModifierValeur(TAILLE_DIM);
		throw (EXCErreur);
	}

	return (*pmaGSLFRGMultiArray)[uiX][uiY][uiZ];
}

/************************************************************************************************************************************************
***** FRGGetCoos : Reading Accessor																											*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : vuiFRGConer : vector <unsigned int>																							*****
***** Effects : Return variable vuiFRGConer																									*****
************************************************************************************************************************************************/
inline vector <unsigned int> CFragment::FRGGetCoos() const {

	return vuiFRGConer;
}

/************************************************************************************************************************************************
***** FRGGetDimensions : Reading Accessor																									*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : vuiFRGDimension : vector <unsigned int>																						*****
***** Effects : Return variable vuiFRGDimension																								*****
************************************************************************************************************************************************/
inline vector <unsigned int> CFragment::FRGGetDimensions() const {

	return vuiFRGDimension;
}

/************************************************************************************************************************************************
***** FRGGetMinMax : Reading Accessor																										*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : puiFRGMinMax : std::pair<unsigned int, unsigned int>																			*****
***** Effects : Return variable puiFRGMinMax																								*****
************************************************************************************************************************************************/
inline std::pair<unsigned int, unsigned int> CFragment::FRGGetMinMax() const {

	return puiFRGMinMax;
}

/************************************************************************************************************************************************
***** FRGGetMax : Reading Accessor																											*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : uiMax : unsigned int																											*****
***** Effects : Return variable puiFRGMinMax's second element 																				*****
************************************************************************************************************************************************/
inline unsigned int CFragment::FRGGetMax() const {

	return puiFRGMinMax.second;
}

/************************************************************************************************************************************************
***** FRGGetMin : Reading Accessor																											*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : uiMin : unsigned int																											*****
***** Effects : Return variable puiFRGMinMax's first element 																				*****
************************************************************************************************************************************************/
inline unsigned int CFragment::FRGGetMin() const {

	return puiFRGMinMax.first;
}

/************************************************************************************************************************************************
***** FRGSetMinMax : Writting Accessor																										*****
*************************************************************************************************************************************************
***** Input : puiMinMax : std::pair<unsigned int, unsigned int>																				*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Modification of the variable puiFRGMinMax 																					*****
************************************************************************************************************************************************/
inline void CFragment::FRGSetMinMax(std::pair<unsigned int, unsigned int> puiMinMax) {

	puiFRGMinMax = puiMinMax;
}

/************************************************************************************************************************************************
***** FRGSetMinMax : Writting Accessor																										*****
*************************************************************************************************************************************************
***** Input : uiMin, uiMax : unsigned int																									*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Modification of the variable puiFRGMinMax 																					*****
************************************************************************************************************************************************/
inline void CFragment::FRGSetMinMax(unsigned int uiMin, unsigned int uiMax) {

	//Creation of the pair
	puiFRGMinMax = std::pair<unsigned int, unsigned int>(uiMin, uiMax);
}

/************************************************************************************************************************************************
***** FRGSetMin : Writting Accessor																											*****
*************************************************************************************************************************************************
***** Input : uiMin : unsigned int																											*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Modification of the puiFRGMinMax's first element																			*****
************************************************************************************************************************************************/
inline void CFragment::FRGSetMin(unsigned int uiMin) {

	puiFRGMinMax.first = uiMin;
}

/************************************************************************************************************************************************
***** FRGSetMax : Writting Accessor																											*****
*************************************************************************************************************************************************
***** Input : uiMax : unsigned int																											*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Modification of the puiFRGMinMax's second element 																			*****
************************************************************************************************************************************************/
inline void CFragment::FRGSetMax(unsigned int uiMax) {

	puiFRGMinMax.second = uiMax;
}

/************************************************************************************************************************************************
***** FRGGetConnexite : Reading Accessor																									*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : uiFRGConnexite : unsigned int																								*****
***** Effects : Return variable uiFRGConnexite					 																			*****
************************************************************************************************************************************************/
inline unsigned int CFragment::FRGGetConnexite() const {

	return uiFRGConnexite;
}

/************************************************************************************************************************************************
***** FRGGetConnexite : Reading Accessor																									*****
*************************************************************************************************************************************************
***** Input : uiNewConnexite : unsigned int																									*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Modification of the variable uiFRGConnexite					 																*****
************************************************************************************************************************************************/
inline void CFragment::FRGSetConnexite(unsigned int uiNewConnexite) {

	uiFRGConnexite = uiNewConnexite;
}

/************************************************************************************************************************************************
***** FRGHomogeneity : Method for analyze homogeneity																						*****
*************************************************************************************************************************************************
***** Input : uiHomogeneite : const unsigned int																							*****
***** Precondition : Nothing                                                                                                                *****
***** Output : bHomogeneity : boolean																										*****
***** Effects : Return True/False if the Fragment are uniform or not					 													*****
************************************************************************************************************************************************/
inline bool CFragment::FRGHomogeneity(const unsigned int uiHomogeneite) const {

	//Min and Max Set
	CGrayScale GSLMini = (*pmaGSLFRGMultiArray)[vuiFRGConer[0]][vuiFRGConer[1]][vuiFRGConer[2]];
	CGrayScale GSLMax = GSLMini;

	//For each Voxel, analyze Min / Max
	for (unsigned int uiBoucle = 0; uiBoucle < vuiFRGDimension[0]; uiBoucle++) {
		for (unsigned int uiBoucle2 = 0; uiBoucle2 < vuiFRGDimension[1]; uiBoucle2++) {
			for (unsigned int uiBoucle3 = 0; uiBoucle3 < vuiFRGDimension[2]; uiBoucle3++) {

				//Save 
				CGrayScale GSLRef = (*pmaGSLFRGMultiArray)[vuiFRGConer[0] + uiBoucle][vuiFRGConer[1] + uiBoucle2][vuiFRGConer[2] + uiBoucle3];

				//Max Comparaison
				if (GSLMax.GSLGetGray() < GSLRef.GSLGetGray()) {
					GSLMax = GSLRef;
				}

				//Min Comparaison
				else if (GSLMini.GSLGetGray() > GSLRef.GSLGetGray()) {
					GSLMini = GSLRef;
				}

				//Verification if the difference between Min / Max are superior the uiHomogeneite (Not Homogene) or not (Homogene)
				if (GSLMax.GSLGetGray() - GSLMini.GSLGetGray() > uiHomogeneite) {
					return false;
				}
			}
		}
	}

	//Else => Homogene Fragment
	return true;
}

/************************************************************************************************************************************************
***** FRGHomogeneityV2 : Method for analyze homogeneity																						*****
*************************************************************************************************************************************************
***** Input : uiHomogeneite : const unsigned int																							*****
***** Precondition : Nothing                                                                                                                *****
***** Output : puiMinMax : std::pair<unsigned int, unsigned int> *																			*****
***** Effects : Return Min/Max if the Fragment are uniform, nullptr else				 													*****
************************************************************************************************************************************************/
inline std::pair<unsigned int, unsigned int> * CFragment::FRGHomogeneityV2(const unsigned int uiHomogeneite) const {

	//Min and Max Set
	CGrayScale GSLMini = (*pmaGSLFRGMultiArray)[vuiFRGConer[0]][vuiFRGConer[1]][vuiFRGConer[2]];
	CGrayScale GSLMax = GSLMini;

	//For each Voxel, analyze Min / Max
	for (unsigned int uiBoucle = 0; uiBoucle < vuiFRGDimension[0]; uiBoucle++) {
		for (unsigned int uiBoucle2 = 0; uiBoucle2 < vuiFRGDimension[1]; uiBoucle2++) {
			for (unsigned int uiBoucle3 = 0; uiBoucle3 < vuiFRGDimension[2]; uiBoucle3++) {

				CGrayScale GSLRef = (*pmaGSLFRGMultiArray)[vuiFRGConer[0] + uiBoucle][vuiFRGConer[1] + uiBoucle2][vuiFRGConer[2] + uiBoucle3];

				//Max Comparaison
				if (GSLMax.GSLGetGray() < GSLRef.GSLGetGray()) {
					GSLMax = GSLRef;

					//Verification if the difference between Min / Max are superior the uiHomogeneite (Not uniform) or not (uniform)
					if (GSLMax.GSLGetGray() - GSLMini.GSLGetGray() > uiHomogeneite) {
						return nullptr;
					}
				}
				//Min Comparaison
				else if (GSLMini.GSLGetGray() > GSLRef.GSLGetGray()) {
					GSLMini = GSLRef;

					//Verification if the difference between Min / Max are superior the uiHomogeneite (Not uniform) or not (uniform)
					if (GSLMax.GSLGetGray() - GSLMini.GSLGetGray() > uiHomogeneite) {
						return nullptr;
					}
				}
			}
		}
	}

	//Else => uniform Fragment and return the pair of Min / Max
	return new std::pair<unsigned int, unsigned int>(GSLMini.GSLGetGray(), GSLMax.GSLGetGray());
}

/************************************************************************************************************************************************
***** FRGFindMinMax : Method for return Min/Max																								*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : puiMinMax : std::pair <unsigned int, unsigned int>																			*****
***** Effects : Return the Min/Max of the Fragment										 													*****
************************************************************************************************************************************************/
inline std::pair<unsigned int, unsigned int> CFragment::FRGFindMinMax() const {

	//Min and Max Set
	CGrayScale GSLMin = (*pmaGSLFRGMultiArray)[vuiFRGConer[0]][vuiFRGConer[1]][vuiFRGConer[2]];
	CGrayScale GSLMax = GSLMin;

	//For each Voxel, analyze Min / Max
	for (unsigned int uiBoucle = 0; uiBoucle < vuiFRGDimension[0]; uiBoucle++) {
		for (unsigned int uiBoucle2 = 0; uiBoucle2 < vuiFRGDimension[1]; uiBoucle2++) {
			for (unsigned int uiBoucle3 = 0; uiBoucle3 < vuiFRGDimension[2]; uiBoucle3++) {

				CGrayScale GSLCurrent = (*pmaGSLFRGMultiArray)[vuiFRGConer[0] + uiBoucle][vuiFRGConer[1] + uiBoucle2][vuiFRGConer[2] + uiBoucle3];

				//Max Comparaison
				if (GSLMax.GSLGetGray() < GSLCurrent.GSLGetGray()) {
					GSLMax = GSLCurrent;
				}
				//Min Comparaison
				else if (GSLMin.GSLGetGray() > GSLCurrent.GSLGetGray()) {
					GSLMin = GSLCurrent;
				}
			}
		}
	}

	//Return Min / Max Pair
	return std::pair<unsigned int, unsigned int>(GSLMin.GSLGetGray(), GSLMax.GSLGetGray());
}

/************************************************************************************************************************************************
***** FRGIsSplitable : Method for return Direction Possibility of Split																		*****
*************************************************************************************************************************************************
***** Input : uiSeuilMin : const unsigned int																								*****
***** Precondition : Nothing                                                                                                                *****
***** Output : vbDimSplitable : std::vector<bool>																							*****
***** Effects : Return boolean for each direction (true if is splitable, false else)										 				*****
************************************************************************************************************************************************/
inline std::vector<bool> CFragment::FRGIsSplitable(const unsigned int uiSeuilMin) const {

	//Exception Management if uiSeuilMin = 0
	if (uiSeuilMin == 0) {
		CException EXCErreur;
		EXCErreur.EXCModifierValeur(SEUIL_MIN);
		throw (EXCErreur);
	}

	return { vuiFRGDimension[0] >= (uiSeuilMin * 2), vuiFRGDimension[1] >= (uiSeuilMin * 2), vuiFRGDimension[2] >= (uiSeuilMin * 2) };
}

/************************************************************************************************************************************************************
***** FRGGetNewSpots : Method for return New Fragment (Coos and Dimensions)																				*****
*************************************************************************************************************************************************************
***** Input : vbSplitDim : const std::vector<bool> | vpvuiNewSpots : std::vector< std::pair< std::vector<unsigned int>, std::vector<unsigned int>>> &	*****
***** Precondition : Nothing																															*****
***** Output : None																																		*****
***** Effects : Return boolean for each direction (true if is splitable, false else)										 							*****
************************************************************************************************************************************************************/
inline void CFragment::FRGGetNewSpots(const std::vector<bool> vbSplitDim, std::vector< std::pair< std::vector<unsigned int>, std::vector<unsigned int>>> & vpvuiNewSpots) {

	std::vector<unsigned int> vuiHalfDims; //Half Dimension vector

	//For each dimension
	for (unsigned int cLoop = 0; cLoop < 3; ++cLoop) { 

		//Calcul of half-dimension if this one is splitable
		vuiHalfDims.push_back(vbSplitDim[cLoop] ? (vuiFRGDimension[cLoop] >> 1) + (vuiFRGDimension[cLoop] & 1) : vuiFRGDimension[cLoop]);
	}

	int i = 0;
	
	//Triple loop for analyze each case possible
	for (unsigned int cLoop1 = 0; cLoop1 <= static_cast <unsigned int>(vbSplitDim[0]); ++cLoop1) {
		for (unsigned int cLoop2 = 0; cLoop2 <= static_cast <unsigned int>(vbSplitDim[1]); ++cLoop2) {
			for (unsigned int cLoop3 = 0; cLoop3 <= static_cast <unsigned int>(vbSplitDim[2]); ++cLoop3) {
				std::vector<unsigned int> vuiSpotCoos = { vuiFRGConer[0] + cLoop1 * vuiHalfDims[0], vuiFRGConer[1] + cLoop2 * vuiHalfDims[1], vuiFRGConer[2] + cLoop3 * vuiHalfDims[2] };
				std::vector<unsigned int> vuiSpotDims = { cLoop1 == 0 ? vuiHalfDims[0] : vuiFRGDimension[0] - vuiHalfDims[0],
														cLoop2 == 0 ? vuiHalfDims[1] : vuiFRGDimension[1] - vuiHalfDims[1],
														cLoop3 == 0 ? vuiHalfDims[2] : vuiFRGDimension[2] - vuiHalfDims[2] };

				//Add new Pair to futur fragment
				vpvuiNewSpots.push_back(std::pair< std::vector<unsigned int>, std::vector<unsigned int> >(vuiSpotCoos, vuiSpotDims));
			}
		}
	}
}