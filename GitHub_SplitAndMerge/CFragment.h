#ifndef CFragment_h
#define CFragment_h 

#pragma once

#include <math.h>
#include <vector>
#include <boost/multi_array.hpp>

using namespace std;

#include "CGrayScale.h"
#include "CException.h"

#define TAILLE 1

class CFragment {

private:
	boost::multi_array <CGrayScale, 3> * pmaGSLFRGMultiArray;
	vector <unsigned int> vuiFRGConer;
	vector <unsigned int> vuiFRGDimension;

public:

	/************************************************************************************************************************************************
	***** CFRAGMENT : Constructeur par défaut de la classe CFragment																			*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																									    *****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné                                                                                                       *****
	***** Entraine : Initialise les variables à "null"																							*****
	************************************************************************************************************************************************/
	CFragment();

	/************************************************************************************************************************************************
	***** CFRAGMENT : Constructeur de confort de la classe CFragment																			*****
	*************************************************************************************************************************************************
	***** Entrée : pmaGSLMultiArray : * boost::multi_array <CGrayScale, 3>, vuiFRGConer et vuiFRGDimension : vector <unsigned int>				*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné                                                                                                       *****
	***** Entraine : Initialise les variables avec les variables passées en paramètre															*****
	************************************************************************************************************************************************/
	CFragment(boost::multi_array <CGrayScale, 3> * pmaGSLMultiArray, vector <unsigned int> vuiConer, vector <unsigned int> vuiDimension);

	/************************************************************************************************************************************************
	***** OPERATOR= : Surcharge de l'opérateur= de la classe CFragment																			*****
	*************************************************************************************************************************************************
	***** Entrée : FRGFragment : const & CFragment																								*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : L'objet lui-même			                                                                                                    *****
	***** Entraine : Initialise les variables respectivement à celles de FRGFragment															*****
	************************************************************************************************************************************************/
	CFragment & operator= (CFragment const& FRGFragment);

	/************************************************************************************************************************************************
	***** CFRAGMENT : Constructeur par défaut de la classe CFragment																			*****
	*************************************************************************************************************************************************
	***** Entrée : FRGFragment : const & CFragment																								*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné                                                                                                       *****
	***** Entraine : Initialise les variables respectivement à celles de FRGFragment															*****
	************************************************************************************************************************************************/
	CFragment(CFragment const& FRGFragment);

	/************************************************************************************************************************************************
	***** OPERATOR== : Surcharge de l'opérateur== de la classe CFragment																		*****
	*************************************************************************************************************************************************
	***** Entrée : FRGFragment : const & CFragment																								*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : bSame : boolean			                                                                                                    *****
	***** Entraine : Retourne un boolean sur la correspondance des 2 objets																		*****
	************************************************************************************************************************************************/
	bool operator==(CFragment const& FRGFragment);

	/************************************************************************************************************************************************
	***** FRGGETMATRICE : Accesseur en lecture de l'attribut pmaGSLFRGMultiArray																*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : * boost::multi_array<CGrayScale, 3> : pmaGSLFRGMultiArray																	*****
	***** Entraine : Retourne le vector des dimensions de pmaGSLFRGMultiArray																	*****
	************************************************************************************************************************************************/
	boost::multi_array<CGrayScale, 3> * FRGGetMatrice();

	/************************************************************************************************************************************************
	***** FRGGETDIMENSIONMATRICE : Accesseur en lecture de l'attribut pmaGSLFRGMultiArray														*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : vuiDimensionMatrice : vector <unsigned int>																					*****
	***** Entraine : Retourne le vector des dimensions de pmaGSLFRGMultiArray																	*****
	************************************************************************************************************************************************/
	vector <unsigned int> FRGGetDimensionMatrice();

	/************************************************************************************************************************************************
	***** FRGGETELEMENT : Accesseur en lecture de l'attribut pmaGSLFRGMultiArray																*****
	*************************************************************************************************************************************************
	***** Entrée : uiX, uiY, uiZ : unsigned int																									*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : CGrayScale : GSLElement																										*****
	***** Entraine : Retourne l'élément CGrayScale pour des coordonnées données																	*****
	************************************************************************************************************************************************/
	CGrayScale FRGGetElement(unsigned int uiX, unsigned int uiY, unsigned int uiZ);

	/************************************************************************************************************************************************
	***** FRGGETCOOS : Accesseur en lecture de l'attribut vuiFRGConer																			*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : vuiFRGConer : vector <unsigned int>																							*****
	***** Entraine : Retourne les coordonées du coin du Multi Array																				*****
	************************************************************************************************************************************************/
	vector <unsigned int> FRGGetCoos();

	/************************************************************************************************************************************************
	***** FRGGETDIMENSIONS : Accesseur en lecture de l'attribut vuiFRGDimension																	*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : vuiFRGDimension : vector <unsigned int>																						*****
	***** Entraine : Retourne les dimensions du Multi Array																						*****
	************************************************************************************************************************************************/
	vector <unsigned int> FRGGetDimensions();

	/************************************************************************************************************************************************
	***** FRGHOMOGENEITY : Méthode de vérification de l'homogénéité de pmaGSLFRGMultiArray														*****
	*************************************************************************************************************************************************
	***** Entrée : uiDifference : unsigned int																									*****
	***** Nécessite : Doit être comprise entre 0 et 255                                                                                         *****
	***** Sortie : boolean																														*****
	***** Entraine : Retourne True/False comme réponse d'homogénéité du Multi-Array																*****
	************************************************************************************************************************************************/
	bool FRGHomogeneity(unsigned int uiDifference);

	/************************************************************************************************************************************************
	***** FRGDOMINANTCOLOR : Méthode retournant la couleur dominante de pmaGSLFRGMultiArray														*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : GSLDominantGray : CGrayScale																									*****
	***** Entraine : Retourne la couleur dominante du Multi-Array																				*****
	************************************************************************************************************************************************/
	CGrayScale FRGDominantColor();

};

#include "CFragment.ipp"

#endif