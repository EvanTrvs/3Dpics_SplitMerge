#pragma once 

#include "CGrayScale.h"

/************************************************************************************************************************************************
***** CGRAYSCALE : Constructeur par défaut de la classe CGrayScale																			*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné																										*****
***** Entraine : Initialise uiGSLGray à 0																									*****
************************************************************************************************************************************************/
inline CGrayScale::CGrayScale() {

	//Initialisation de la variable uiGSLGray
	uiGSLGray = 0;
	uiGSLConnexite = -1;
}

/************************************************************************************************************************************************
***** CGRAYSCALE : Constructeur de confort de la classe CGrayScale																			*****
*************************************************************************************************************************************************
***** Entrée : uiGray : unsigned int																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné																										*****
***** Entraine : Initialise uiGSLGray avec le paramètre passé																				*****
************************************************************************************************************************************************/
inline CGrayScale::CGrayScale(unsigned int uiGray) {
	//Initialisation de la variable uiGSLGray
	uiGSLGray = uiGray;
	uiGSLConnexite = -1;
}

inline CGrayScale::CGrayScale(unsigned int uiGray, int uiConnexite) {

	//Initialisation de la variable uiGSLGray
	uiGSLGray = uiGray;
	uiGSLConnexite = uiConnexite;
}

/************************************************************************************************************************************************
***** CGRAYSCALE : Constructeur de recopie de la classe CGrayScale																			*****
*************************************************************************************************************************************************
***** Entrée : GSLGray : const & CGrayScale																									*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné																										*****
***** Entraine : Initialise uiGSLGray à l'objet passé en paramètre																			*****
************************************************************************************************************************************************/
inline CGrayScale::CGrayScale(CGrayScale const& GSLGray) {

	//Initialisation de la variable uiGSLGray
	uiGSLGray = GSLGray.uiGSLGray;
	uiGSLConnexite = GSLGray.uiGSLConnexite;
}

/************************************************************************************************************************************************
***** GSLGETGRAY : Accesseur en lecture de l'attribut uiGray																				*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie :uiGSLGray	: unsigned int																										*****
***** Entraine : Retourne la variable uiGSLGray																								*****
************************************************************************************************************************************************/
inline unsigned int CGrayScale::GSLGetGray() const {

	//Return de la variable uiGSLGray
	return uiGSLGray;
}

/************************************************************************************************************************************************
***** GSLSETGRAY : Accesseur en écriture de l'attribut uiGray																				*****
*************************************************************************************************************************************************
***** Entrée : uiGSLGray : unsigned int																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné																										*****
***** Entraine : Modifie la variable uiGSLGray																								*****
************************************************************************************************************************************************/
inline void CGrayScale::GSLSetGray(unsigned int uiGray) {

	//Modification de la variable uiGSLGray
	uiGSLGray = uiGray;
}

inline int CGrayScale::GSLGetConnexite() {
	return uiGSLConnexite;
}

inline void CGrayScale::GSLSetConnexite(int uiNewConnexite) {
	uiGSLConnexite = uiNewConnexite;
}

/************************************************************************************************************************************************
***** GSLUPPERLIMIT : Méthode retournant la valeur max de GrayScale (de 0 à 255)															*****
*************************************************************************************************************************************************
***** Entrée : uiDifference : unsigned int																									*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : uiGray : unsigned int																										*****
***** Entraine : Retourne la valeur de la différence entre le critère d'homogénéité et la valeur du Gray									*****
************************************************************************************************************************************************/
inline unsigned int CGrayScale::GSLUpperLimit(unsigned int uiDifference) {

	//Si la variable uiGSLGray est inférieur à la différence entre le maximum possible et le critère d'homogénéité
	if (uiGSLGray < 255 - uiDifference)
		return uiGSLGray + uiDifference;
	else //Sinon return le maximum possible (255)
		return 255;
}

/************************************************************************************************************************************************
***** GSLLOWERLIMIT : Méthode retournant la valeur min de GrayScale (de 0 à 255)															*****
*************************************************************************************************************************************************
***** Entrée : uiDifference : unsigned int																									*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : uiGray : unsigned int																										*****
***** Entraine : Retourne la valeur de la différence entre le critère d'homogénéité et la valeur du Gray									*****
************************************************************************************************************************************************/
inline unsigned int CGrayScale::GSLLowerLimit(unsigned int uiDifference) {

	//Si la variable uiGSLGray est supérieur à la différence entre le minimum possible et le critère d'homogénéité
	if (uiGSLGray > uiDifference)
		return uiGSLGray - uiDifference;
	else //Sinon return le minimum (0)
		return 0;
}