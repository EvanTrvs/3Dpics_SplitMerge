#pragma once
 
#include <iostream> 

using namespace std;

#include "CFragment.h"

/************************************************************************************************************************************************
***** CGROUPE : Constructeur par défaut de la classe CGroupe																				*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																									    *****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné                                                                                                       *****
***** Entraine : Initialise les variables à "null"																							*****
************************************************************************************************************************************************/
inline CFragment::CFragment() {

	//Initialisation des variables
	pmaGSLFRGMultiArray = nullptr;
	vuiFRGConer = {};
	vuiFRGDimension = {};
}

/************************************************************************************************************************************************
***** CFRAGMENT : Constructeur de confort de la classe CFragment																			*****
*************************************************************************************************************************************************
***** Entrée : pmaCLRMultiArray : * boost::multi_array <CGrayScale, 3>, vuiFRGConer et vuiFRGDimension : vector <unsigned int>				*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné                                                                                                       *****
***** Entraine : Initialise les variables avec les variables passées en paramètre															*****
************************************************************************************************************************************************/
inline CFragment::CFragment(boost::multi_array <CGrayScale, 3> * pmaCLRMultiArray, vector <unsigned int> vuiConer, vector <unsigned int> vuiDimension) {

	//Initialisation des variables
	pmaGSLFRGMultiArray = pmaCLRMultiArray;

	//Vérification si les coordonnées et les dimensions sont situé dans le MultiArray
	if (vuiConer[0] + vuiDimension[0] > pmaCLRMultiArray->shape()[0] || 
		vuiConer[1] + vuiDimension[1] > pmaCLRMultiArray->shape()[1] || 
		vuiConer[2] + vuiDimension[2] > pmaCLRMultiArray->shape()[2]) {

		CException EXCErreur;
		EXCErreur.EXCModifierValeur(TAILLE);
		throw (EXCErreur);
	}


	vuiFRGConer = vuiConer;
	vuiFRGDimension = vuiDimension;
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
		EXCErreur.EXCModifierValeur(TAILLE);
		throw (EXCErreur);
	}

	vuiFRGConer = FRGFragment.vuiFRGConer;
	vuiFRGDimension = FRGFragment.vuiFRGDimension;

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
		EXCErreur.EXCModifierValeur(TAILLE);
		throw (EXCErreur);
	}

	vuiFRGConer = FRGFragment.vuiFRGConer;
	vuiFRGDimension = FRGFragment.vuiFRGDimension;
}

/************************************************************************************************************************************************
***** OPERATOR== : Surcharge de l'opérateur== de la classe CFragment																		*****
*************************************************************************************************************************************************
***** Entrée : FRGFragment : const & CFragment																								*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : bSame : boolean			                                                                                                    *****
***** Entraine : Retourne un boolean sur la correspondance des 2 objets																		*****
************************************************************************************************************************************************/
inline bool CFragment::operator==(CFragment const& FRGFragment) {

	if (vuiFRGConer == FRGFragment.vuiFRGConer) {
		return true;
	}

	return false;
}

/************************************************************************************************************************************************
***** FRGGETMATRICE : Accesseur en lecture de l'attribut pmaGSLFRGMultiArray																*****
*************************************************************************************************************************************************
***** Entrée : Aucun paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : * boost::multi_array<CGrayScale, 3> : pmaGSLFRGMultiArray																	*****
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

	return { pmaGSLFRGMultiArray->shape()[0], pmaGSLFRGMultiArray->shape()[1], pmaGSLFRGMultiArray->shape()[2] };
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
		EXCErreur.EXCModifierValeur(TAILLE);
		throw (EXCErreur);
	}

	return pmaGSLFRGMultiArray[0][uiX][uiY][uiZ];
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
***** FRGHOMOGENEITY : Méthode de vérification de l'homogénéité de pmaGSLFRGMultiArray														*****
*************************************************************************************************************************************************
***** Entrée : uiDifference : unsigned int																									*****
***** Nécessite : Doit être comprise entre 0 et 255                                                                                         *****
***** Sortie : boolean																														*****
***** Entraine : Retourne True/False comme réponse d'homogénéité du Multi-Array																*****
************************************************************************************************************************************************/
inline bool CFragment::FRGHomogeneity(unsigned int uiDifference) {

	CGrayScale CLRRef = pmaGSLFRGMultiArray[0][vuiFRGConer[0]][vuiFRGConer[1]][vuiFRGConer[2]];

	for (unsigned int uiBoucle = 0; uiBoucle < vuiFRGDimension[0]; uiBoucle++) {
		for (unsigned int uiBoucle2 = 0; uiBoucle2 < vuiFRGDimension[1]; uiBoucle2++) {
			for (unsigned int uiBoucle3 = 0; uiBoucle3 < vuiFRGDimension[2]; uiBoucle3++) {

				if (pmaGSLFRGMultiArray[0][vuiFRGConer[0] + uiBoucle][vuiFRGConer[1] + uiBoucle2][vuiFRGConer[2] + uiBoucle3].GSLLowerLimit(uiDifference) > CLRRef.GSLGetGray() ||
					pmaGSLFRGMultiArray[0][vuiFRGConer[0] + uiBoucle][vuiFRGConer[1] + uiBoucle2][vuiFRGConer[2] + uiBoucle3].GSLUpperLimit(uiDifference) < CLRRef.GSLGetGray()) {
					return false;
				}
			}
		}
	}

	return true;
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
				uiMoyenneGray += pmaGSLFRGMultiArray[0][vuiFRGConer[0] + uiBoucle][vuiFRGConer[1] + uiBoucle2][vuiFRGConer[2] + uiBoucle3].GSLGetGray();
			}
		}
	}

	return CGrayScale (static_cast<unsigned int> (round (uiMoyenneGray / (vuiFRGDimension[0]*vuiFRGDimension[1]*vuiFRGDimension[2]))));
}