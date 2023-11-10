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
	***** CFRAGMENT : Constructeur par d�faut de la classe CFragment																			*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																									    *****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�                                                                                                       *****
	***** Entraine : Initialise les variables � "null"																							*****
	************************************************************************************************************************************************/
	CFragment();

	/************************************************************************************************************************************************
	***** CFRAGMENT : Constructeur de confort de la classe CFragment																			*****
	*************************************************************************************************************************************************
	***** Entr�e : pmaGSLMultiArray : * boost::multi_array <CGrayScale, 3>, vuiFRGConer et vuiFRGDimension : vector <unsigned int>				*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�                                                                                                       *****
	***** Entraine : Initialise les variables avec les variables pass�es en param�tre															*****
	************************************************************************************************************************************************/
	CFragment(boost::multi_array <CGrayScale, 3> * pmaGSLMultiArray, vector <unsigned int> vuiConer, vector <unsigned int> vuiDimension);

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
	***** OPERATOR== : Surcharge de l'op�rateur== de la classe CFragment																		*****
	*************************************************************************************************************************************************
	***** Entr�e : FRGFragment : const & CFragment																								*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : bSame : boolean			                                                                                                    *****
	***** Entraine : Retourne un boolean sur la correspondance des 2 objets																		*****
	************************************************************************************************************************************************/
	bool operator==(CFragment const& FRGFragment);

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
	***** FRGHOMOGENEITY : M�thode de v�rification de l'homog�n�it� de pmaGSLFRGMultiArray														*****
	*************************************************************************************************************************************************
	***** Entr�e : uiDifference : unsigned int																									*****
	***** N�cessite : Doit �tre comprise entre 0 et 255                                                                                         *****
	***** Sortie : boolean																														*****
	***** Entraine : Retourne True/False comme r�ponse d'homog�n�it� du Multi-Array																*****
	************************************************************************************************************************************************/
	bool FRGHomogeneity(unsigned int uiDifference);

	/************************************************************************************************************************************************
	***** FRGDOMINANTCOLOR : M�thode retournant la couleur dominante de pmaGSLFRGMultiArray														*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : GSLDominantGray : CGrayScale																									*****
	***** Entraine : Retourne la couleur dominante du Multi-Array																				*****
	************************************************************************************************************************************************/
	CGrayScale FRGDominantColor();

};

#include "CFragment.ipp"

#endif