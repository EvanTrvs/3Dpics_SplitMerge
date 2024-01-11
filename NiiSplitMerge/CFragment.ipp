#pragma once
 
#include <iostream> 

using namespace std;

#include "CFragment.h"

/***************************************************************************************************************************************************************************
***** CFRAGMENT : Constructeur par défaut de la classe CFragment																						 			   *****
****************************************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée 																															   *****
***** Nécessite : Ne nécessite rien																														 			   *****
***** Sortie : Aucun élément retourné																																   *****
***** Entraine : Initialise les variables à null ou 0																												   *****
***************************************************************************************************************************************************************************/
inline CFragment::CFragment() {

	//Initialisation des variables
	pmaGSLFRGMultiArray = nullptr;

	vuiFRGConer = {};
	vuiFRGDimension = {};

	puiFRGMinMax.first = 0;
	puiFRGMinMax.second = 0;

	uiFRGConnexite = 0;
}

/***************************************************************************************************************************************************************************
***** CFRAGMENT : Constructeur de confort de la classe CFragment																						 			   *****
****************************************************************************************************************************************************************************
***** Entrée : pmaCLRMultiArray : * boost::multi_array <CGrayScale, 3>, vuiFRGConer et vuiFRGDimension : vector <unsigned int>										   *****
***** Nécessite : Ne nécessite rien																														 			   *****
***** Sortie : Aucun élément retourné																																   *****
***** Entraine : Initialise les variables avec les variables passées en paramètre																					   *****
***************************************************************************************************************************************************************************/
inline CFragment::CFragment(boost::multi_array <CGrayScale, 3> * pmaGSLMultiArray, vector <unsigned int> vuiConer, vector <unsigned int> vuiDimension) {

	//Initialisation des variables
	pmaGSLFRGMultiArray = pmaGSLMultiArray;

	//Vérification si les coordonnées et les dimensions sont situé dans le MultiArray
	if (vuiConer[0] + vuiDimension[0] > pmaGSLMultiArray->shape()[0] ||
		vuiConer[1] + vuiDimension[1] > pmaGSLMultiArray->shape()[1] ||
		vuiConer[2] + vuiDimension[2] > pmaGSLMultiArray->shape()[2]) {

		CException EXCErreur;
		EXCErreur.EXCModifierValeur(TAILLE_DIM);
		throw (EXCErreur);
	}


	vuiFRGConer = vuiConer;
	vuiFRGDimension = vuiDimension;
	uiFRGConnexite = 0;

	puiFRGMinMax.first = 0;
	puiFRGMinMax.second = 0;
}

/***************************************************************************************************************************************************************************
***** CFRAGMENT : Constructeur de confort de la classe CFragment																						 			   *****
****************************************************************************************************************************************************************************
***** Entrée : pmaCLRMultiArray : * boost::multi_array <CGrayScale, 3>, vuiFRGConer et vuiFRGDimension : vector <unsigned int> | uiConnexite : unsigned int 		   *****
***** Nécessite : Ne nécessite rien																														 			   *****
***** Sortie : Aucun élément retourné																																   *****
***** Entraine : Initialise les variables avec les variables passées en paramètre																					   *****
***************************************************************************************************************************************************************************/
inline CFragment::CFragment(boost::multi_array <CGrayScale, 3> * pmaGSLMultiArray, vector <unsigned int> vuiConer, vector <unsigned int> vuiDimension, unsigned int uiConnexite) {

	//Initialisation des variables
	pmaGSLFRGMultiArray = pmaGSLMultiArray;

	//Vérification si les coordonnées et les dimensions sont situé dans le MultiArray
	if (vuiConer[0] + vuiDimension[0] > pmaGSLMultiArray->shape()[0] ||
		vuiConer[1] + vuiDimension[1] > pmaGSLMultiArray->shape()[1] ||
		vuiConer[2] + vuiDimension[2] > pmaGSLMultiArray->shape()[2]) {

		CException EXCErreur;
		EXCErreur.EXCModifierValeur(TAILLE_DIM);
		throw (EXCErreur);
	}


	vuiFRGConer = vuiConer;
	vuiFRGDimension = vuiDimension;
	uiFRGConnexite = uiConnexite;

	puiFRGMinMax.first = 0;
	puiFRGMinMax.second = 0;
}

/****************************************************************************************************************************************************************************************************************
***** CFRAGMENT : Constructeur de confort de la classe CFragment																						 												    *****
*****************************************************************************************************************************************************************************************************************
***** Entrée : pmaCLRMultiArray : * boost::multi_array <CGrayScale, 3>, vuiFRGConer et vuiFRGDimension : vector <unsigned int> | uiConnexite : unsigned int | puiMinMax : pair<unsigned int, unsigned int>	*****
***** Nécessite : Ne nécessite rien																														 												    *****
***** Sortie : Aucun élément retourné																																									    *****
***** Entraine : Initialise les variables avec les variables passées en paramètre																														    *****
****************************************************************************************************************************************************************************************************************/
inline CFragment::CFragment(boost::multi_array <CGrayScale, 3> * pmaCLRMultiArray, vector <unsigned int> vuiConer, vector <unsigned int> vuiDimension, unsigned int uiConnexite, std::pair<unsigned int, unsigned int> puiMinMax) {

	//Initialisation des variables
	pmaGSLFRGMultiArray = pmaCLRMultiArray;

	//Vérification si les coordonnées et les dimensions sont situé dans le MultiArray
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
***** OPERATOR= : Surcharge de l'opérateur= de la classe CFragment																			*****
*************************************************************************************************************************************************
***** Entrée : FRGFragment : const & CFragment																								*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : L'objet lui-même			                                                                                                    *****
***** Entraine : Initialise les variables respectivement à celles de FRGFragment															*****
************************************************************************************************************************************************/
inline CFragment& CFragment::operator= (CFragment const& FRGFragment) {

	//Initialisation des variables
	pmaGSLFRGMultiArray = FRGFragment.pmaGSLFRGMultiArray; //Pointeur sur le même bjet pour éviter de la redondance en mémoire

	//Vérification si les coordonnées et les dimensions sont situé dans le MultiArray
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

	return *this;
}

/************************************************************************************************************************************************
***** CGROUPE : Constructeur par défaut de la classe CVoxel																					*****
*************************************************************************************************************************************************
***** Entrée : GRPGroupe : const & CGroupe																								    *****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné                                                                                                       *****
***** Entraine : Initialise les variables respectivement à celles de FRGFragment															*****
************************************************************************************************************************************************/
inline CFragment::CFragment(CFragment const& FRGFragment) {

	//Initialisation des variables
	pmaGSLFRGMultiArray = FRGFragment.pmaGSLFRGMultiArray; //Pointeur sur le même bjet pour éviter de la redondance en mémoire

	//Vérification si les coordonnées et les dimensions sont situé dans le MultiArray
	if (FRGFragment.vuiFRGConer[0] + FRGFragment.vuiFRGDimension[0] > FRGFragment.pmaGSLFRGMultiArray->shape()[0] ||
		FRGFragment.vuiFRGConer[1] + FRGFragment.vuiFRGDimension[1] > FRGFragment.pmaGSLFRGMultiArray->shape()[1] ||
		FRGFragment.vuiFRGConer[2] + FRGFragment.vuiFRGDimension[2] > FRGFragment.pmaGSLFRGMultiArray->shape()[2]) {

		CException EXCErreur;
		EXCErreur.EXCModifierValeur(TAILLE_DIM);
		throw (EXCErreur);
	}

	vuiFRGConer = FRGFragment.vuiFRGConer;
	vuiFRGDimension = FRGFragment.vuiFRGDimension;

	uiFRGConnexite = FRGFragment.uiFRGConnexite;
	puiFRGMinMax = FRGFragment.puiFRGMinMax;
}

/************************************************************************************************************************************************
***** FRGGETMATRICE : Accesseur en lecture de l'attribut pmaGSLFRGMultiArray																*****
*************************************************************************************************************************************************
***** Entrée : Aucun paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : boost::multi_array<CGrayScale, 3> * : pmaGSLFRGMultiArray																	*****
***** Entraine : Retourne le vector des dimensions de pmaGSLFRGMultiArray																	*****
************************************************************************************************************************************************/
inline boost::multi_array<CGrayScale, 3> * CFragment::FRGGetMatrice() {
	return pmaGSLFRGMultiArray;
}

/************************************************************************************************************************************************
***** FRGGETDIMENSIONMATRICE : Accesseur en lecture de l'attribut pmaGSLFRGMultiArray														*****
*************************************************************************************************************************************************
***** Entrée : Aucun paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : vuiDimensionMatrice : vector <unsigned int>																					*****
***** Entraine : Retourne le vector des dimensions de pmaGSLFRGMultiArray																	*****
************************************************************************************************************************************************/
inline vector <unsigned int> CFragment::FRGGetDimensionMatrice() {

	return { (unsigned int)pmaGSLFRGMultiArray->shape()[0], (unsigned int)pmaGSLFRGMultiArray->shape()[1], (unsigned int)pmaGSLFRGMultiArray->shape()[2] };
}

/************************************************************************************************************************************************
***** FRGGETELEMENT : Accesseur en lecture de l'attribut pmaGSLFRGMultiArray																*****
*************************************************************************************************************************************************
***** Entrée : uiX, uiY, uiZ : unsigned int																									*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : CGrayScale : CLRElement																										*****
***** Entraine : Retourne l'élément CGrayScale pour des coordonnées données																	*****
************************************************************************************************************************************************/
inline CGrayScale CFragment::FRGGetElement(unsigned int uiX, unsigned int uiY, unsigned int uiZ) {

	//Vérification si les coordonnées sont situé dans le MultiArray
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
***** FRGGETCOOS : Accesseur en lecture de l'attribut vuiFRGConer																			*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : vuiFRGConer : vector <unsigned int>																							*****
***** Entraine : Retourne les coordonées du coin du Multi Array																				*****
************************************************************************************************************************************************/
inline vector <unsigned int> CFragment::FRGGetCoos() {
	return vuiFRGConer;
}

/************************************************************************************************************************************************
***** FRGGETDIMENSIONS : Accesseur en lecture de l'attribut vuiFRGDimension																	*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : vuiFRGDimension : vector <unsigned int>																						*****
***** Entraine : Retourne les dimensions du Multi Array																						*****
************************************************************************************************************************************************/
inline vector <unsigned int> CFragment::FRGGetDimensions() {
	return vuiFRGDimension;
}

/************************************************************************************************************************************************
***** FRGGETMINMAX : Accesseur en lecture de l'attribut puiFRGMinMax																		*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : puiFRGMinMax : pair<unsigned int, unsigned int>																				*****
***** Entraine : Retourne les valeurs du couple Min / Max																					*****
************************************************************************************************************************************************/
inline std::pair<unsigned int, unsigned int> CFragment::FRGGetMinMax() {
	return puiFRGMinMax;
}

/************************************************************************************************************************************************
***** FRGGETMAX : Accesseur en lecture de l'attribut puiFRGMinMax																			*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : puiFRGMinMax.second : unsigned int																							*****
***** Entraine : Retourne la valeur Max du couple Min / Max																					*****
************************************************************************************************************************************************/
inline unsigned int CFragment::FRGGetMax() {
	return puiFRGMinMax.second;
}

/************************************************************************************************************************************************
***** FRGGETMIN : Accesseur en lecture de l'attribut puiFRGMinMax																			*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : puiFRGMinMax.first : unsigned int																							*****
***** Entraine : Retourne la valeur Min du couple Min / Max																					*****
************************************************************************************************************************************************/
inline unsigned int CFragment::FRGGetMin() {
	return puiFRGMinMax.first;
}

/************************************************************************************************************************************************
***** FRGSETMINMAX : Accesseur en écriture de l'attribut puiFRGMinMax																		*****
*************************************************************************************************************************************************
***** Entrée : puiMinMax : pair<unsigned int, unsigned int>																					*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné																										*****
***** Entraine : Modifie la valeur du couple Min / Max																						*****
************************************************************************************************************************************************/
inline void CFragment::FRGSetMinMax(std::pair<unsigned int, unsigned int> puiMinMax) {
	puiFRGMinMax = puiMinMax;
}

/************************************************************************************************************************************************
***** FRGSETMINMAX : Accesseur en écriture de l'attribut puiFRGMinMax																		*****
*************************************************************************************************************************************************
***** Entrée : uiMin : unsigned int | uiMax : unsigned int																					*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné																										*****
***** Entraine : Modifie la valeur du couple Min / Max																						*****
************************************************************************************************************************************************/
inline void CFragment::FRGSetMinMax(unsigned int uiMin, unsigned int uiMax) {
	puiFRGMinMax = std::pair<unsigned int, unsigned int>(uiMin, uiMax);
}

/************************************************************************************************************************************************
***** FRGSETMIN : Accesseur en écriture de l'attribut puiFRGMinMax																			*****
*************************************************************************************************************************************************
***** Entrée : uiMin : unsigned int																											*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné																										*****
***** Entraine : Modifie la valeur Min du couple Min / Max																					*****
************************************************************************************************************************************************/
inline void CFragment::FRGSetMin(unsigned int uiMin) {
	puiFRGMinMax.first = uiMin;
}

/************************************************************************************************************************************************
***** FRGSETMAX : Accesseur en écriture de l'attribut puiFRGMinMax																			*****
*************************************************************************************************************************************************
***** Entrée : uiMax : unsigned int																											*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné																										*****
***** Entraine : Modifie la valeur Max du couple Min / Max																					*****
************************************************************************************************************************************************/
inline void CFragment::FRGSetMax(unsigned int uiMax) {
	puiFRGMinMax.second = uiMax;
}

/************************************************************************************************************************************************
***** FRGGETCONNEXITE : Accesseur en lecture de uiFRGConnexite																				*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien																											*****
***** Sortie : uiFRGConnexite : unsigned int																								*****
***** Entraine : Retourne la valeur de la variable uiFRGConnexite																			*****
************************************************************************************************************************************************/
inline unsigned int CFragment::FRGGetConnexite() {
	return uiFRGConnexite;
}

/************************************************************************************************************************************************
***** FRGSETCONNEXITE : Accesseur en écriture de uiFRGConnexite																				*****
*************************************************************************************************************************************************
***** Entrée : uiNewConnexite : unsigned int																								*****
***** Nécessite : Ne nécessite rien																											*****
***** Sortie : Aucun élement retourné																										*****
***** Entraine : Modifie la valeur de la variable uiFRGConnexite																			*****
************************************************************************************************************************************************/
inline void CFragment::FRGSetConnexite(unsigned int uiNewConnexite) {
	uiFRGConnexite = uiNewConnexite;
}

/************************************************************************************************************************************************
***** FRGHOMOGENEITY : Méthode de vérification de l'homogénéité de pmaGSLFRGMultiArray														*****
*************************************************************************************************************************************************
***** Entrée : uiDifference : const unsigned int																							*****
***** Nécessite : Ne nécessite rien																											*****
***** Sortie : boolean																														*****
***** Entraine : Retourne True/False comme réponse d'homogénéité du Multi-Array																*****
************************************************************************************************************************************************/
inline bool CFragment::FRGHomogeneity(const unsigned int uiHomogeneite) {

	//set du min et du max
	CGrayScale GSLMini = (*pmaGSLFRGMultiArray)[vuiFRGConer[0]][vuiFRGConer[1]][vuiFRGConer[2]];
	CGrayScale GSLMax = GSLMini;

	//Pour chaque Voxel du Fragment, détermine le min et le max
	for (unsigned int uiBoucle = 0; uiBoucle < vuiFRGDimension[0]; uiBoucle++) {
		for (unsigned int uiBoucle2 = 0; uiBoucle2 < vuiFRGDimension[1]; uiBoucle2++) {
			for (unsigned int uiBoucle3 = 0; uiBoucle3 < vuiFRGDimension[2]; uiBoucle3++) {

				//Sauvegarde 
				CGrayScale GSLRef = (*pmaGSLFRGMultiArray)[vuiFRGConer[0] + uiBoucle][vuiFRGConer[1] + uiBoucle2][vuiFRGConer[2] + uiBoucle3];

				//Compare le max
				if (GSLMax.GSLGetGray() < GSLRef.GSLGetGray()) {
					GSLMax = GSLRef;
				}

				//Compare le Min
				else if (GSLMini.GSLGetGray() > GSLRef.GSLGetGray()) {
					GSLMini = GSLRef;
				}

				//Vérifie si la différence entre le min et le max est supérieur à l'homogénéité => non homogène
				if (GSLMax.GSLGetGray() - GSLMini.GSLGetGray() > uiHomogeneite) {
					return false;
				}
			}
		}
	}

	//Sinon => Fragment Homogène
	return true;
}

/************************************************************************************************************************************************
***** FRGHOMOGENEITYV2 : Méthode de vérification de l'homogénéité de pmaGSLFRGMultiArray													*****
*************************************************************************************************************************************************
***** Entrée : uiHomogeneite : const unsigned int																							*****
***** Nécessite : Ne nécessite rien					                                                                                        *****
***** Sortie : puiMinMax : pair <unsigned int, unsigned int>																				*****
***** Entraine : Retourne le Min / Max comme réponse d'homogénéité du Multi-Array, nullptr si pas homogène									*****
************************************************************************************************************************************************/
inline std::pair<unsigned int, unsigned int> * CFragment::FRGHomogeneityV2(const unsigned int uiHomogeneite) {

	//set du min et du max
	CGrayScale GSLMini = (*pmaGSLFRGMultiArray)[vuiFRGConer[0]][vuiFRGConer[1]][vuiFRGConer[2]];
	CGrayScale GSLMax = GSLMini;

	//Pour chaque Voxel du Fragment, détermine le min et le max
	for (unsigned int uiBoucle = 0; uiBoucle < vuiFRGDimension[0]; uiBoucle++) {
		for (unsigned int uiBoucle2 = 0; uiBoucle2 < vuiFRGDimension[1]; uiBoucle2++) {
			for (unsigned int uiBoucle3 = 0; uiBoucle3 < vuiFRGDimension[2]; uiBoucle3++) {

				CGrayScale GSLRef = (*pmaGSLFRGMultiArray)[vuiFRGConer[0] + uiBoucle][vuiFRGConer[1] + uiBoucle2][vuiFRGConer[2] + uiBoucle3];

				//Compare le Max
				if (GSLMax.GSLGetGray() < GSLRef.GSLGetGray()) {
					GSLMax = GSLRef;

					//Vérifie si la différence entre le min et le max est supérieur à l'homogénéité => non homogène
					if (GSLMax.GSLGetGray() - GSLMini.GSLGetGray() > uiHomogeneite) {
						return nullptr;
					}
				}
				//Compare le Min
				else if (GSLMini.GSLGetGray() > GSLRef.GSLGetGray()) {
					GSLMini = GSLRef;

					//Vérifie si la différence entre le min et le max est supérieur à l'homogénéité => non homogène
					if (GSLMax.GSLGetGray() - GSLMini.GSLGetGray() > uiHomogeneite) {
						return nullptr;
					}
				}
			}
		}
	}

	//Return la pair Min/Max
	return new std::pair<unsigned int, unsigned int>(GSLMini.GSLGetGray(), GSLMax.GSLGetGray());
}

/************************************************************************************************************************************************
***** FRGFINDMINMAX : Méthode retournant le Min/Max																							*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : std::pair <unsigned int, unsigned int> : puiMinMax																			*****
***** Entraine : Retourne une pair de Min / Max du CFragment																				*****
************************************************************************************************************************************************/
inline std::pair<unsigned int, unsigned int> CFragment::FRGFindMinMax() {	//même algo que HomogeneityV2 mais pas de critere d'homogeinite, calcul min,max du fragment

	CGrayScale GSLMin = (*pmaGSLFRGMultiArray)[vuiFRGConer[0]][vuiFRGConer[1]][vuiFRGConer[2]];
	CGrayScale GSLMax = GSLMin;

	//Pour chaque Voxel du Fragment, détermine le min et le max
	for (unsigned int uiBoucle = 0; uiBoucle < vuiFRGDimension[0]; uiBoucle++) {
		for (unsigned int uiBoucle2 = 0; uiBoucle2 < vuiFRGDimension[1]; uiBoucle2++) {
			for (unsigned int uiBoucle3 = 0; uiBoucle3 < vuiFRGDimension[2]; uiBoucle3++) {

				CGrayScale GSLCurrent = (*pmaGSLFRGMultiArray)[vuiFRGConer[0] + uiBoucle][vuiFRGConer[1] + uiBoucle2][vuiFRGConer[2] + uiBoucle3];

				//Compare le Max
				if (GSLMax.GSLGetGray() < GSLCurrent.GSLGetGray()) {
					GSLMax = GSLCurrent;
				}
				//Compare le Min
				else if (GSLMin.GSLGetGray() > GSLCurrent.GSLGetGray()) {
					GSLMin = GSLCurrent;
				}
			}
		}
	}
	//Return la pair Min/Max
	return std::pair<unsigned int, unsigned int>(GSLMin.GSLGetGray(), GSLMax.GSLGetGray());
}

/************************************************************************************************************************************************
***** FRGDOMINANTCOLOR : Méthode retournant la couleur dominante de pmaGSLFRGMultiArray														*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : GSLDominantGray : CGrayScale																									*****
***** Entraine : Retourne la couleur dominante du Multi-Array																				*****
************************************************************************************************************************************************/
inline CGrayScale CFragment::FRGDominantColor() {

	unsigned int uiMoyenneGray = 0;

	for (unsigned int uiBoucle = 0; uiBoucle < vuiFRGDimension[0]; uiBoucle++) {
		for (unsigned int uiBoucle2 = 0; uiBoucle2 < vuiFRGDimension[1]; uiBoucle2++) {
			for (unsigned int uiBoucle3 = 0; uiBoucle3 < vuiFRGDimension[2]; uiBoucle3++) {
				uiMoyenneGray += (*pmaGSLFRGMultiArray)[vuiFRGConer[0] + uiBoucle][vuiFRGConer[1] + uiBoucle2][vuiFRGConer[2] + uiBoucle3].GSLGetGray();
			}
		}
	}

	return CGrayScale (static_cast<unsigned int> (round (uiMoyenneGray / (vuiFRGDimension[0]*vuiFRGDimension[1]*vuiFRGDimension[2]))));
}

/************************************************************************************************************************************************
***** FRGISSPLITABLE : Méthode retournant le Min/Max																						*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : std::vector<bool> : vbDimSplitable																							*****
***** Entraine : Retourne une pair de Min / Max du CFragment																				*****
************************************************************************************************************************************************/
inline std::vector<bool> CFragment::FRGIsSplitable(const unsigned int uiSeuilMin) {

	//Gestion de l'exception : Taille minimum = 0
	if (uiSeuilMin == 0) {
		CException EXCErreur;
		EXCErreur.EXCModifierValeur(SEUIL_MIN);
		throw (EXCErreur);
	}

	return { vuiFRGDimension[0] >= (uiSeuilMin * 2), vuiFRGDimension[1] >= (uiSeuilMin * 2), vuiFRGDimension[2] >= (uiSeuilMin * 2) };
}

/************************************************************************************************************************************************
***** FRGGETNEWSPOTS : Méthode retournant les nouveaux Fragments																			*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : std::vector<bool> : vbDimSplitable																							*****
***** Entraine : Retourne une pair de Min / Max du CFragment																				*****
************************************************************************************************************************************************/
inline void CFragment::FRGGetNewSpots(const std::vector<bool> vbSplitDim, std::vector< std::pair< std::vector<unsigned int>, std::vector<unsigned int>>> & vpvuiNewSpots) {

	std::vector<unsigned int> vuiHalfDims; //conteneur des demi dimensions

	//Pour chaque dimension
	for (unsigned int cLoop = 0; cLoop < 3; ++cLoop) {      
		//calcule de la demi-dimension, seulement si celle-ci est "Splitable"
		vuiHalfDims.push_back(vbSplitDim[cLoop] ? (vuiFRGDimension[cLoop] >> 1) + (vuiFRGDimension[cLoop] & 1) : vuiFRGDimension[cLoop]);
	}

	int i = 0;
	//Triple boucle permet de lire tous les cas possibles
	for (unsigned int cLoop1 = 0; cLoop1 <= static_cast <unsigned int>(vbSplitDim[0]); ++cLoop1) {
		for (unsigned int cLoop2 = 0; cLoop2 <= static_cast <unsigned int>(vbSplitDim[1]); ++cLoop2) {
			for (unsigned int cLoop3 = 0; cLoop3 <= static_cast <unsigned int>(vbSplitDim[2]); ++cLoop3) {
				std::vector<unsigned int> vuiSpotCoos = { vuiFRGConer[0] + cLoop1 * vuiHalfDims[0], vuiFRGConer[1] + cLoop2 * vuiHalfDims[1], vuiFRGConer[2] + cLoop3 * vuiHalfDims[2] };
				std::vector<unsigned int> vuiSpotDims = { cLoop1 == 0 ? vuiHalfDims[0] : vuiFRGDimension[0] - vuiHalfDims[0],
														cLoop2 == 0 ? vuiHalfDims[1] : vuiFRGDimension[1] - vuiHalfDims[1],
														cLoop3 == 0 ? vuiHalfDims[2] : vuiFRGDimension[2] - vuiHalfDims[2] };

				//Ajoute la nouvelle pair à la liste des nouveaux futurs splits
				vpvuiNewSpots.push_back(std::pair< std::vector<unsigned int>, std::vector<unsigned int> >(vuiSpotCoos, vuiSpotDims));
			}
		}
	}
}