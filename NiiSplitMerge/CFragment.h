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
	***** CFRAGMENT : Constructeur par d�faut de la classe CFragment																						 			   *****
	****************************************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e 																															   *****
	***** N�cessite : Ne n�cessite rien																														 			   *****
	***** Sortie : Aucun �l�ment retourn�																																   *****
	***** Entraine : Initialise les variables � null ou 0																												   *****
	***************************************************************************************************************************************************************************/
	CFragment();

	/***************************************************************************************************************************************************************************
	***** CFRAGMENT : Constructeur de confort de la classe CFragment																						 			   *****
	****************************************************************************************************************************************************************************
	***** Entr�e : pmaCLRMultiArray : * boost::multi_array <CGrayScale, 3>, vuiFRGConer et vuiFRGDimension : vector <unsigned int>										   *****
	***** N�cessite : Ne n�cessite rien																														 			   *****
	***** Sortie : Aucun �l�ment retourn�																																   *****
	***** Entraine : Initialise les variables avec les variables pass�es en param�tre																					   *****
	***************************************************************************************************************************************************************************/
	CFragment(boost::multi_array <CGrayScale, 3> * pmaGSLMultiArray, vector <unsigned int> vuiConer, vector <unsigned int> vuiDimension);


	/***************************************************************************************************************************************************************************
	***** CFRAGMENT : Constructeur de confort de la classe CFragment																						 			   *****
	****************************************************************************************************************************************************************************
	***** Entr�e : pmaCLRMultiArray : * boost::multi_array <CGrayScale, 3>, vuiFRGConer et vuiFRGDimension : vector <unsigned int> | uiFRGNum : unsigned int 			   *****
	***** N�cessite : Ne n�cessite rien																														 			   *****
	***** Sortie : Aucun �l�ment retourn�																																   *****
	***** Entraine : Initialise les variables avec les variables pass�es en param�tre																					   *****
	***************************************************************************************************************************************************************************/
	CFragment(boost::multi_array <CGrayScale, 3> * pmaGSLMultiArray, vector <unsigned int> vuiConer, vector <unsigned int> vuiDimension, unsigned int uiNum);

	/************************************************************************************************************************************************************************************************************
	***** CFRAGMENT : Constructeur de confort de la classe CFragment																						 												*****
	*************************************************************************************************************************************************************************************************************
	***** Entr�e : pmaCLRMultiArray : * boost::multi_array <CGrayScale, 3>, vuiFRGConer et vuiFRGDimension : vector <unsigned int> | uiFRGNum : unsigned int | puiMinMax : pair<unsigned int, unsigned int>	*****
	***** N�cessite : Ne n�cessite rien																														 												*****
	***** Sortie : Aucun �l�ment retourn�																																									*****
	***** Entraine : Initialise les variables avec les variables pass�es en param�tre																														*****
	*************************************************************************************************************************************************************************************************************/	
	CFragment(boost::multi_array <CGrayScale, 3> * pmaCLRMultiArray, vector <unsigned int> vuiConer, vector <unsigned int> vuiDimension, unsigned int uiNum, std::pair<unsigned int, unsigned int> puiMinMax);

	/************************************************************************************************************************************************
	***** OPERATOR= : Surcharge de l'op�rateur= de la classe CFragment																			*****
	*************************************************************************************************************************************************
	***** Entr�e : FRGFragment : const & CFragment																								*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : L'objet lui-m�me			                                                                                                    *****
	***** Entraine : Initialise les variables respectivement � celles de FRGFragment															*****
	************************************************************************************************************************************************/
	CFragment & operator= (CFragment const& FRGFragment);

	/************************************************************************************************************************************************
	***** CFRAGMENT : Constructeur par d�faut de la classe CFragment																			*****
	*************************************************************************************************************************************************
	***** Entr�e : FRGFragment : const & CFragment																								*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�                                                                                                       *****
	***** Entraine : Initialise les variables respectivement � celles de FRGFragment															*****
	************************************************************************************************************************************************/
	CFragment(CFragment const& FRGFragment);

	/************************************************************************************************************************************************
	***** FRGGETMATRICE : Accesseur en lecture de l'attribut pmaGSLFRGMultiArray																*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : * boost::multi_array<CGrayScale, 3> : pmaGSLFRGMultiArray																	*****
	***** Entraine : Retourne le vector des dimensions de pmaGSLFRGMultiArray																	*****
	************************************************************************************************************************************************/
	boost::multi_array<CGrayScale, 3> * FRGGetMatrice();

	/************************************************************************************************************************************************
	***** FRGGETDIMENSIONMATRICE : Accesseur en lecture de l'attribut pmaGSLFRGMultiArray														*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : vuiDimensionMatrice : vector <unsigned int>																					*****
	***** Entraine : Retourne le vector des dimensions de pmaGSLFRGMultiArray																	*****
	************************************************************************************************************************************************/
	vector <unsigned int> FRGGetDimensionMatrice();

	/************************************************************************************************************************************************
	***** FRGGETELEMENT : Accesseur en lecture de l'attribut pmaGSLFRGMultiArray																*****
	*************************************************************************************************************************************************
	***** Entr�e : uiX, uiY, uiZ : unsigned int																									*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : CGrayScale : GSLElement																										*****
	***** Entraine : Retourne l'�l�ment CGrayScale pour des coordonn�es donn�es																	*****
	************************************************************************************************************************************************/
	CGrayScale FRGGetElement(unsigned int uiX, unsigned int uiY, unsigned int uiZ);

	/************************************************************************************************************************************************
	***** FRGGETCOOS : Accesseur en lecture de l'attribut vuiFRGConer																			*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : vuiFRGConer : vector <unsigned int>																							*****
	***** Entraine : Retourne les coordon�es du coin du Multi Array																				*****
	************************************************************************************************************************************************/
	vector <unsigned int> FRGGetCoos();

	/************************************************************************************************************************************************
	***** FRGGETDIMENSIONS : Accesseur en lecture de l'attribut vuiFRGDimension																	*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : vuiFRGDimension : vector <unsigned int>																						*****
	***** Entraine : Retourne les dimensions du Multi Array																						*****
	************************************************************************************************************************************************/
	vector <unsigned int> FRGGetDimensions();

	/************************************************************************************************************************************************
	***** FRGGETMINMAX : Accesseur en lecture de l'attribut puiFRGMinMax																		*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : puiFRGMinMax : pair<unsigned int, unsigned int>																				*****
	***** Entraine : Retourne les valeurs du couple Min / Max																					*****
	************************************************************************************************************************************************/
	std::pair<unsigned int, unsigned int> FRGGetMinMax();

	/************************************************************************************************************************************************
	***** FRGGETMIN : Accesseur en lecture de l'attribut puiFRGMinMax																			*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : puiFRGMinMax.first : unsigned int																							*****
	***** Entraine : Retourne la valeur Min du couple Min / Max																					*****
	************************************************************************************************************************************************/
	unsigned int FRGGetMin();

	/************************************************************************************************************************************************
	***** FRGGETMAX : Accesseur en lecture de l'attribut puiFRGMinMax																			*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : puiFRGMinMax.second : unsigned int																							*****
	***** Entraine : Retourne la valeur Max du couple Min / Max																					*****
	************************************************************************************************************************************************/
	unsigned int FRGGetMax();

	/************************************************************************************************************************************************
	***** FRGSETMINMAX : Accesseur en �criture de l'attribut puiFRGMinMax																		*****
	*************************************************************************************************************************************************
	***** Entr�e : puiMinMax : pair<unsigned int, unsigned int>																					*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Modifie la valeur du couple Min / Max																						*****
	************************************************************************************************************************************************/
	void FRGSetMinMax(std::pair<unsigned int, unsigned int> puiMinMax);

	/************************************************************************************************************************************************
	***** FRGSETMINMAX : Accesseur en �criture de l'attribut puiFRGMinMax																		*****
	*************************************************************************************************************************************************
	***** Entr�e : uiMin : unsigned int | uiMax : unsigned int																					*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Modifie la valeur du couple Min / Max																						*****
	************************************************************************************************************************************************/
	void FRGSetMinMax(unsigned int uiMin, unsigned int uiMax);

	/************************************************************************************************************************************************
	***** FRGSETMIN : Accesseur en �criture de l'attribut puiFRGMinMax																			*****
	*************************************************************************************************************************************************
	***** Entr�e : uiMin : unsigned int																											*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Modifie la valeur Min du couple Min / Max																					*****
	************************************************************************************************************************************************/
	void FRGSetMin(unsigned int uiMin);

	/************************************************************************************************************************************************
	***** FRGSETMAX : Accesseur en �criture de l'attribut puiFRGMinMax																			*****
	*************************************************************************************************************************************************
	***** Entr�e : uiMax : unsigned int																											*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Modifie la valeur Max du couple Min / Max																					*****
	************************************************************************************************************************************************/
	void FRGSetMax(unsigned int uiMax);

	/************************************************************************************************************************************************
	***** FRGGETCONNEXITE : Accesseur en lecture de uiFRGConnexite																				*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien																											*****
	***** Sortie : uiFRGConnexite : unsigned int																								*****
	***** Entraine : Retourne la valeur de la variable uiFRGConnexite																			*****
	************************************************************************************************************************************************/
	unsigned int FRGGetConnexite();

	/************************************************************************************************************************************************
	***** FRGSETCONNEXITE : Accesseur en �criture de uiFRGConnexite																				*****
	*************************************************************************************************************************************************
	***** Entr�e : uiNewConnexite : unsigned int																								*****
	***** N�cessite : Ne n�cessite rien																											*****
	***** Sortie : Aucun �lement retourn�																										*****
	***** Entraine : Modifie la valeur de la variable uiFRGConnexite																			*****
	************************************************************************************************************************************************/
	void FRGSetConnexite(unsigned int uiNewNConnexite);

	/************************************************************************************************************************************************
	***** FRGHOMOGENEITY : M�thode de v�rification de l'homog�n�it� de pmaGSLFRGMultiArray														*****
	*************************************************************************************************************************************************
	***** Entr�e : uiHomogeneite : unsigned int																									*****
	***** N�cessite : Doit �tre comprise entre 0 et 255                                                                                         *****
	***** Sortie : boolean																														*****
	***** Entraine : Retourne True/False comme r�ponse d'homog�n�it� du Multi-Array																*****
	************************************************************************************************************************************************/
	bool FRGHomogeneity(const unsigned int uiHomogeneite);

	/************************************************************************************************************************************************
	***** FRGHOMOGENEITYV2 : M�thode de v�rification de l'homog�n�it� de pmaGSLFRGMultiArray													*****
	*************************************************************************************************************************************************
	***** Entr�e : uiHomogeneite : const unsigned int																							*****
	***** N�cessite : Ne n�cessite rien					                                                                                        *****
	***** Sortie : puiMinMax : pair <unsigned int, unsigned int>																				*****
	***** Entraine : Retourne le Min / Max comme r�ponse d'homog�n�it� du Multi-Array, nullptr si pas homog�ne									*****
	************************************************************************************************************************************************/
	std::pair<unsigned int, unsigned int> * FRGHomogeneityV2(const unsigned int uiHomogeneite);

	/************************************************************************************************************************************************
	***** FRGFINDMINMAX : M�thode retournant le Min/Max																							*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : std::pair <unsigned int, unsigned int> : puiMinMax																			*****
	***** Entraine : Retourne une pair de Min / Max du CFragment																				*****
	************************************************************************************************************************************************/
	std::pair<unsigned int, unsigned int> FRGFindMinMax();

	/************************************************************************************************************************************************
	***** FRGDOMINANTCOLOR : M�thode retournant la couleur dominante de pmaGSLFRGMultiArray														*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : GSLDominantGray : CGrayScale																									*****
	***** Entraine : Retourne la couleur dominante du Multi-Array																				*****
	************************************************************************************************************************************************/
	CGrayScale FRGDominantColor();

	/************************************************************************************************************************************************
	***** FRGISSPLITABLE : M�thode retournant le Min/Max																						*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : std::vector<bool> : vbDimSplitable																							*****
	***** Entraine : Retourne une pair de Min / Max du CFragment																				*****
	************************************************************************************************************************************************/
	std::vector<bool> FRGIsSplitable(const unsigned int uiSeuilMin);

	/************************************************************************************************************************************************
	***** FRGGETNEWSPOTS : M�thode retournant les nouveaux Fragments																			*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : std::vector<bool> : vbDimSplitable																							*****
	***** Entraine : Retourne une pair de Min / Max du CFragment																				*****
	************************************************************************************************************************************************/
	void FRGGetNewSpots(const std::vector<bool> vbSplitDim, std::vector< std::pair< std::vector<unsigned int>, std::vector<unsigned int>>> & vpvuiNewSpots);

};

#include "CFragment.ipp"

#endif