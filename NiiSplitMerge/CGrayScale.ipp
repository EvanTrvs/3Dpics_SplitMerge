#pragma once 

#include "CGrayScale.h"

/************************************************************************************************************************************************
***** CGRAYSCALE : Constructeur par d�faut de la classe CGrayScale																			*****
*************************************************************************************************************************************************
***** Entr�e : Aucun Param�tre d'entr�e																										*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : Aucun �l�ment retourn�																										*****
***** Entraine : Initialise uiGSLGray � 0																									*****
************************************************************************************************************************************************/
inline CGrayScale::CGrayScale() {

	//Initialisation de la variable uiGSLGray
	uiGSLGray = 0;
	uiGSLConnexite = -1;
}

/************************************************************************************************************************************************
***** CGRAYSCALE : Constructeur de confort de la classe CGrayScale																			*****
*************************************************************************************************************************************************
***** Entr�e : uiGray : unsigned int																										*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : Aucun �l�ment retourn�																										*****
***** Entraine : Initialise uiGSLGray avec le param�tre pass�																				*****
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
***** Entr�e : GSLGray : const & CGrayScale																									*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : Aucun �l�ment retourn�																										*****
***** Entraine : Initialise uiGSLGray � l'objet pass� en param�tre																			*****
************************************************************************************************************************************************/
inline CGrayScale::CGrayScale(CGrayScale const& GSLGray) {

	//Initialisation de la variable uiGSLGray
	uiGSLGray = GSLGray.uiGSLGray;
	uiGSLConnexite = GSLGray.uiGSLConnexite;
}

/************************************************************************************************************************************************
***** GSLGETGRAY : Accesseur en lecture de l'attribut uiGray																				*****
*************************************************************************************************************************************************
***** Entr�e : Aucun Param�tre d'entr�e																										*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie :uiGSLGray	: unsigned int																										*****
***** Entraine : Retourne la variable uiGSLGray																								*****
************************************************************************************************************************************************/
inline unsigned int CGrayScale::GSLGetGray() const {

	//Return de la variable uiGSLGray
	return uiGSLGray;
}

/************************************************************************************************************************************************
***** GSLSETGRAY : Accesseur en �criture de l'attribut uiGray																				*****
*************************************************************************************************************************************************
***** Entr�e : uiGSLGray : unsigned int																										*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : Aucun �l�ment retourn�																										*****
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
***** GSLUPPERLIMIT : M�thode retournant la valeur max de GrayScale (de 0 � 255)															*****
*************************************************************************************************************************************************
***** Entr�e : uiDifference : unsigned int																									*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : uiGray : unsigned int																										*****
***** Entraine : Retourne la valeur de la diff�rence entre le crit�re d'homog�n�it� et la valeur du Gray									*****
************************************************************************************************************************************************/
inline unsigned int CGrayScale::GSLUpperLimit(unsigned int uiDifference) {

	//Si la variable uiGSLGray est inf�rieur � la diff�rence entre le maximum possible et le crit�re d'homog�n�it�
	if (uiGSLGray < 255 - uiDifference)
		return uiGSLGray + uiDifference;
	else //Sinon return le maximum possible (255)
		return 255;
}

/************************************************************************************************************************************************
***** GSLLOWERLIMIT : M�thode retournant la valeur min de GrayScale (de 0 � 255)															*****
*************************************************************************************************************************************************
***** Entr�e : uiDifference : unsigned int																									*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : uiGray : unsigned int																										*****
***** Entraine : Retourne la valeur de la diff�rence entre le crit�re d'homog�n�it� et la valeur du Gray									*****
************************************************************************************************************************************************/
inline unsigned int CGrayScale::GSLLowerLimit(unsigned int uiDifference) {

	//Si la variable uiGSLGray est sup�rieur � la diff�rence entre le minimum possible et le crit�re d'homog�n�it�
	if (uiGSLGray > uiDifference)
		return uiGSLGray - uiDifference;
	else //Sinon return le minimum (0)
		return 0;
}