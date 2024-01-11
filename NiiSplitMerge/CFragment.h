#ifndef CFragment_h
#define CFragment_h 

#pragma once

#include <math.h>
#include <vector>
#include <boost/multi_array.hpp>

using namespace std;

#include "CGrayScale.h"
#include "CException.h"

#define TAILLE_DIM 1
#define SEUIL_MIN 2

class CFragment {

private:
	boost::multi_array <CGrayScale, 3> * pmaGSLFRGMultiArray;
	vector <unsigned int> vuiFRGConer;
	vector <unsigned int> vuiFRGDimension;

	std::pair <unsigned int, unsigned int> puiFRGMinMax;
	unsigned int uiFRGConnexite;

public:

	/***************************************************************************************************************************************************************************
	***** CFRAGMENT : Constructeur par défaut de la classe CFragment																						 			   *****
	****************************************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée 																															   *****
	***** Nécessite : Ne nécessite rien																														 			   *****
	***** Sortie : Aucun élément retourné																																   *****
	***** Entraine : Initialise les variables à null ou 0																												   *****
	***************************************************************************************************************************************************************************/
	CFragment();

	/***************************************************************************************************************************************************************************
	***** CFRAGMENT : Constructeur de confort de la classe CFragment																						 			   *****
	****************************************************************************************************************************************************************************
	***** Entrée : pmaCLRMultiArray : * boost::multi_array <CGrayScale, 3>, vuiFRGConer et vuiFRGDimension : vector <unsigned int>										   *****
	***** Nécessite : Ne nécessite rien																														 			   *****
	***** Sortie : Aucun élément retourné																																   *****
	***** Entraine : Initialise les variables avec les variables passées en paramètre																					   *****
	***************************************************************************************************************************************************************************/
	CFragment(boost::multi_array <CGrayScale, 3> * pmaGSLMultiArray, vector <unsigned int> vuiConer, vector <unsigned int> vuiDimension);


	/***************************************************************************************************************************************************************************
	***** CFRAGMENT : Constructeur de confort de la classe CFragment																						 			   *****
	****************************************************************************************************************************************************************************
	***** Entrée : pmaCLRMultiArray : * boost::multi_array <CGrayScale, 3>, vuiFRGConer et vuiFRGDimension : vector <unsigned int> | uiFRGNum : unsigned int 			   *****
	***** Nécessite : Ne nécessite rien																														 			   *****
	***** Sortie : Aucun élément retourné																																   *****
	***** Entraine : Initialise les variables avec les variables passées en paramètre																					   *****
	***************************************************************************************************************************************************************************/
	CFragment(boost::multi_array <CGrayScale, 3> * pmaGSLMultiArray, vector <unsigned int> vuiConer, vector <unsigned int> vuiDimension, unsigned int uiNum);

	/************************************************************************************************************************************************************************************************************
	***** CFRAGMENT : Constructeur de confort de la classe CFragment																						 												*****
	*************************************************************************************************************************************************************************************************************
	***** Entrée : pmaCLRMultiArray : * boost::multi_array <CGrayScale, 3>, vuiFRGConer et vuiFRGDimension : vector <unsigned int> | uiFRGNum : unsigned int | puiMinMax : pair<unsigned int, unsigned int>	*****
	***** Nécessite : Ne nécessite rien																														 												*****
	***** Sortie : Aucun élément retourné																																									*****
	***** Entraine : Initialise les variables avec les variables passées en paramètre																														*****
	*************************************************************************************************************************************************************************************************************/	
	CFragment(boost::multi_array <CGrayScale, 3> * pmaCLRMultiArray, vector <unsigned int> vuiConer, vector <unsigned int> vuiDimension, unsigned int uiNum, std::pair<unsigned int, unsigned int> puiMinMax);

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
	***** FRGGETMINMAX : Accesseur en lecture de l'attribut puiFRGMinMax																		*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : puiFRGMinMax : pair<unsigned int, unsigned int>																				*****
	***** Entraine : Retourne les valeurs du couple Min / Max																					*****
	************************************************************************************************************************************************/
	std::pair<unsigned int, unsigned int> FRGGetMinMax();

	/************************************************************************************************************************************************
	***** FRGGETMIN : Accesseur en lecture de l'attribut puiFRGMinMax																			*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : puiFRGMinMax.first : unsigned int																							*****
	***** Entraine : Retourne la valeur Min du couple Min / Max																					*****
	************************************************************************************************************************************************/
	unsigned int FRGGetMin();

	/************************************************************************************************************************************************
	***** FRGGETMAX : Accesseur en lecture de l'attribut puiFRGMinMax																			*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : puiFRGMinMax.second : unsigned int																							*****
	***** Entraine : Retourne la valeur Max du couple Min / Max																					*****
	************************************************************************************************************************************************/
	unsigned int FRGGetMax();

	/************************************************************************************************************************************************
	***** FRGSETMINMAX : Accesseur en écriture de l'attribut puiFRGMinMax																		*****
	*************************************************************************************************************************************************
	***** Entrée : puiMinMax : pair<unsigned int, unsigned int>																					*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Modifie la valeur du couple Min / Max																						*****
	************************************************************************************************************************************************/
	void FRGSetMinMax(std::pair<unsigned int, unsigned int> puiMinMax);

	/************************************************************************************************************************************************
	***** FRGSETMINMAX : Accesseur en écriture de l'attribut puiFRGMinMax																		*****
	*************************************************************************************************************************************************
	***** Entrée : uiMin : unsigned int | uiMax : unsigned int																					*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Modifie la valeur du couple Min / Max																						*****
	************************************************************************************************************************************************/
	void FRGSetMinMax(unsigned int uiMin, unsigned int uiMax);

	/************************************************************************************************************************************************
	***** FRGSETMIN : Accesseur en écriture de l'attribut puiFRGMinMax																			*****
	*************************************************************************************************************************************************
	***** Entrée : uiMin : unsigned int																											*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Modifie la valeur Min du couple Min / Max																					*****
	************************************************************************************************************************************************/
	void FRGSetMin(unsigned int uiMin);

	/************************************************************************************************************************************************
	***** FRGSETMAX : Accesseur en écriture de l'attribut puiFRGMinMax																			*****
	*************************************************************************************************************************************************
	***** Entrée : uiMax : unsigned int																											*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Modifie la valeur Max du couple Min / Max																					*****
	************************************************************************************************************************************************/
	void FRGSetMax(unsigned int uiMax);

	/************************************************************************************************************************************************
	***** FRGGETCONNEXITE : Accesseur en lecture de uiFRGConnexite																				*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien																											*****
	***** Sortie : uiFRGConnexite : unsigned int																								*****
	***** Entraine : Retourne la valeur de la variable uiFRGConnexite																			*****
	************************************************************************************************************************************************/
	unsigned int FRGGetConnexite();

	/************************************************************************************************************************************************
	***** FRGSETCONNEXITE : Accesseur en écriture de uiFRGConnexite																				*****
	*************************************************************************************************************************************************
	***** Entrée : uiNewConnexite : unsigned int																								*****
	***** Nécessite : Ne nécessite rien																											*****
	***** Sortie : Aucun élement retourné																										*****
	***** Entraine : Modifie la valeur de la variable uiFRGConnexite																			*****
	************************************************************************************************************************************************/
	void FRGSetConnexite(unsigned int uiNewNConnexite);

	/************************************************************************************************************************************************
	***** FRGHOMOGENEITY : Méthode de vérification de l'homogénéité de pmaGSLFRGMultiArray														*****
	*************************************************************************************************************************************************
	***** Entrée : uiHomogeneite : unsigned int																									*****
	***** Nécessite : Doit être comprise entre 0 et 255                                                                                         *****
	***** Sortie : boolean																														*****
	***** Entraine : Retourne True/False comme réponse d'homogénéité du Multi-Array																*****
	************************************************************************************************************************************************/
	bool FRGHomogeneity(const unsigned int uiHomogeneite);

	/************************************************************************************************************************************************
	***** FRGHOMOGENEITYV2 : Méthode de vérification de l'homogénéité de pmaGSLFRGMultiArray													*****
	*************************************************************************************************************************************************
	***** Entrée : uiHomogeneite : const unsigned int																							*****
	***** Nécessite : Ne nécessite rien					                                                                                        *****
	***** Sortie : puiMinMax : pair <unsigned int, unsigned int>																				*****
	***** Entraine : Retourne le Min / Max comme réponse d'homogénéité du Multi-Array, nullptr si pas homogène									*****
	************************************************************************************************************************************************/
	std::pair<unsigned int, unsigned int> * FRGHomogeneityV2(const unsigned int uiHomogeneite);

	/************************************************************************************************************************************************
	***** FRGFINDMINMAX : Méthode retournant le Min/Max																							*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : std::pair <unsigned int, unsigned int> : puiMinMax																			*****
	***** Entraine : Retourne une pair de Min / Max du CFragment																				*****
	************************************************************************************************************************************************/
	std::pair<unsigned int, unsigned int> FRGFindMinMax();

	/************************************************************************************************************************************************
	***** FRGDOMINANTCOLOR : Méthode retournant la couleur dominante de pmaGSLFRGMultiArray														*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : GSLDominantGray : CGrayScale																									*****
	***** Entraine : Retourne la couleur dominante du Multi-Array																				*****
	************************************************************************************************************************************************/
	CGrayScale FRGDominantColor();

	/************************************************************************************************************************************************
	***** FRGISSPLITABLE : Méthode retournant le Min/Max																						*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : std::vector<bool> : vbDimSplitable																							*****
	***** Entraine : Retourne une pair de Min / Max du CFragment																				*****
	************************************************************************************************************************************************/
	std::vector<bool> FRGIsSplitable(const unsigned int uiSeuilMin);

	/************************************************************************************************************************************************
	***** FRGGETNEWSPOTS : Méthode retournant les nouveaux Fragments																			*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : std::vector<bool> : vbDimSplitable																							*****
	***** Entraine : Retourne une pair de Min / Max du CFragment																				*****
	************************************************************************************************************************************************/
	void FRGGetNewSpots(const std::vector<bool> vbSplitDim, std::vector< std::pair< std::vector<unsigned int>, std::vector<unsigned int>>> & vpvuiNewSpots);

};

#include "CFragment.ipp"

#endif