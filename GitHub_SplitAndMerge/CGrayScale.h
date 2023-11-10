#ifndef CGrayScale_h
#define CGrayScale_h

#pragma once

#include <iostream> 

using namespace std;

class CGrayScale {
private:
	unsigned int uiGSLGray;

public:
	/************************************************************************************************************************************************
	***** CGRAYSCALE : Constructeur par défaut de la classe CGrayScale																			*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Initialise uiGSLGray à 0																									*****
	************************************************************************************************************************************************/
	CGrayScale();

	/************************************************************************************************************************************************
	***** CGRAYSCALE : Constructeur de confort de la classe CGrayScale																			*****
	*************************************************************************************************************************************************
	***** Entrée : uiGray : unsigned int																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Initialise uiGSLGray avec le paramètre passé																				*****
	************************************************************************************************************************************************/
	CGrayScale(unsigned int uiGray);

	/************************************************************************************************************************************************
	***** CGRAYSCALE : Constructeur de recopie de la classe CGrayScale																			*****
	*************************************************************************************************************************************************
	***** Entrée : GSLGray : const & CGrayScale																									*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Initialise uiGSLGray à l'objet passé en paramètre																			*****
	************************************************************************************************************************************************/
	CGrayScale(CGrayScale const& GSLGray);

	/************************************************************************************************************************************************
	***** GSLGETGRAY : Accesseur en lecture de l'attribut uiGray																				*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie :uiGSLGray	: unsigned int																										*****
	***** Entraine : Retourne la variable uiGSLGray																								*****
	************************************************************************************************************************************************/
	unsigned int GSLGetGray();

	/************************************************************************************************************************************************
	***** GSLSETGRAY : Accesseur en écriture de l'attribut uiGray																				*****
	*************************************************************************************************************************************************
	***** Entrée : uiGSLGray : unsigned int																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Modifie la variable uiGSLGray																								*****
	************************************************************************************************************************************************/
	void GSLSetGray(unsigned int uiGray);

	/************************************************************************************************************************************************
	***** GSLUPPERLIMIT : Méthode retournant la valeur max de GrayScale (de 0 à 255)															*****
	*************************************************************************************************************************************************
	***** Entrée : uiDifference : unsigned int																									*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : uiGray : unsigned int																										*****
	***** Entraine : Retourne la valeur de la différence entre le critère d'homogénéité et la valeur du Gray									*****
	************************************************************************************************************************************************/
	unsigned int GSLUpperLimit(unsigned int uiDifference);

	/************************************************************************************************************************************************
	***** GSLLOWERLIMIT : Méthode retournant la valeur min de GrayScale (de 0 à 255)															*****
	*************************************************************************************************************************************************
	***** Entrée : uiDifference : unsigned int																									*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : uiGray : unsigned int																										*****
	***** Entraine : Retourne la valeur de la différence entre le critère d'homogénéité et la valeur du Gray									*****
	************************************************************************************************************************************************/
	unsigned int GSLLowerLimit(unsigned int uiDifference);


};

#include "CGrayScale.ipp"

#endif

