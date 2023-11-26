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
	***** CGRAYSCALE : Constructeur par d�faut de la classe CGrayScale																			*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Initialise uiGSLGray � 0																									*****
	************************************************************************************************************************************************/
	CGrayScale();

	/************************************************************************************************************************************************
	***** CGRAYSCALE : Constructeur de confort de la classe CGrayScale																			*****
	*************************************************************************************************************************************************
	***** Entr�e : uiGray : unsigned int																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Initialise uiGSLGray avec le param�tre pass�																				*****
	************************************************************************************************************************************************/
	CGrayScale(unsigned int uiGray);

	/************************************************************************************************************************************************
	***** CGRAYSCALE : Constructeur de recopie de la classe CGrayScale																			*****
	*************************************************************************************************************************************************
	***** Entr�e : GSLGray : const & CGrayScale																									*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Initialise uiGSLGray � l'objet pass� en param�tre																			*****
	************************************************************************************************************************************************/
	CGrayScale(CGrayScale const& GSLGray);

	/************************************************************************************************************************************************
	***** GSLGETGRAY : Accesseur en lecture de l'attribut uiGray																				*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie :uiGSLGray	: unsigned int																										*****
	***** Entraine : Retourne la variable uiGSLGray																								*****
	************************************************************************************************************************************************/
	unsigned int GSLGetGray();

	/************************************************************************************************************************************************
	***** GSLSETGRAY : Accesseur en �criture de l'attribut uiGray																				*****
	*************************************************************************************************************************************************
	***** Entr�e : uiGSLGray : unsigned int																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Modifie la variable uiGSLGray																								*****
	************************************************************************************************************************************************/
	void GSLSetGray(unsigned int uiGray);

	/************************************************************************************************************************************************
	***** GSLUPPERLIMIT : M�thode retournant la valeur max de GrayScale (de 0 � 255)															*****
	*************************************************************************************************************************************************
	***** Entr�e : uiDifference : unsigned int																									*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : uiGray : unsigned int																										*****
	***** Entraine : Retourne la valeur de la diff�rence entre le crit�re d'homog�n�it� et la valeur du Gray									*****
	************************************************************************************************************************************************/
	unsigned int GSLUpperLimit(unsigned int uiDifference);

	/************************************************************************************************************************************************
	***** GSLLOWERLIMIT : M�thode retournant la valeur min de GrayScale (de 0 � 255)															*****
	*************************************************************************************************************************************************
	***** Entr�e : uiDifference : unsigned int																									*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : uiGray : unsigned int																										*****
	***** Entraine : Retourne la valeur de la diff�rence entre le crit�re d'homog�n�it� et la valeur du Gray									*****
	************************************************************************************************************************************************/
	unsigned int GSLLowerLimit(unsigned int uiDifference);


};

#include "CGrayScale.ipp"

#endif

