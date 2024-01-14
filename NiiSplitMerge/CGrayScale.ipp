#pragma once 

#include "CGrayScale.h"

/************************************************************************************************************************************************
***** Default Class Constructor																												*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Initialize uiGSLGray to 0 and uiGSLConnexite to -1                                                                          *****
************************************************************************************************************************************************/
inline CGrayScale::CGrayScale() {

	// Initialize the variable uiGSLGray
	uiGSLGray = 0;
	uiGSLConnexite = -1;
}

/************************************************************************************************************************************************
***** Class Constructor																														*****
*************************************************************************************************************************************************
***** Input : uiGray : unsigned int																											*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Initialize uiGSLGray with the provided parameter and uiGSLConnexite to -1                                                   *****
************************************************************************************************************************************************/
inline CGrayScale::CGrayScale(unsigned int uiGray) {

	//Variables Initialization
	uiGSLGray = uiGray;
	uiGSLConnexite = -1;
}

/************************************************************************************************************************************************
***** Class Constructor																														*****
*************************************************************************************************************************************************
***** Input : uiGray, uiConnexite : unsigned int																							*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Initialize uiGSLGray and uiGSLConnexite with the provided parameter				 											*****
************************************************************************************************************************************************/
inline CGrayScale::CGrayScale(unsigned int uiGray, int uiConnexite) {

	//Variables Initialization
	uiGSLGray = uiGray;
	uiGSLConnexite = uiConnexite;
}

/************************************************************************************************************************************************
***** Class Copie Constructor																												*****
*************************************************************************************************************************************************
***** Input : GSLGray : const & CGrayScale																									*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Initialize uiGSLGray and uiGSLConnexite with the parameter object															*****
************************************************************************************************************************************************/
inline CGrayScale::CGrayScale(CGrayScale const& GSLGray) {

	//Variables Initialization
	uiGSLGray = GSLGray.uiGSLGray;
	uiGSLConnexite = GSLGray.uiGSLConnexite;
}

/************************************************************************************************************************************************
***** GSLGetGray : Reading Accessors																										*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : uiGSLGray : unsigned int																										*****
***** Effects : Return Variable uiGSLGray																									*****
************************************************************************************************************************************************/
inline unsigned int CGrayScale::GSLGetGray() const {

	//Return Variable uiGSLGray
	return uiGSLGray;
}

/************************************************************************************************************************************************
***** GSLSetGray : Writting Accessors																										*****
*************************************************************************************************************************************************
***** Input : uiGray : unsigned int 																										*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Modification of variable uiGSLGray																							*****
************************************************************************************************************************************************/
inline void CGrayScale::GSLSetGray(unsigned int uiGray) {

	//Modification of variable uiGSLGray
	uiGSLGray = uiGray;
}

/************************************************************************************************************************************************
***** GSLGetConexite : Reading Accessors																									*****
*************************************************************************************************************************************************
***** Input : None 																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : uiGSLConnexite : unsigned int																								*****
***** Effects : Return variable uiGSLConnexite																								*****
************************************************************************************************************************************************/
inline int CGrayScale::GSLGetConnexite() const {

	//Return Variable uiGSLConnexite
	return uiGSLConnexite;
}

/************************************************************************************************************************************************
***** GSLSetConnexite : Wrtting Accessors																									*****
*************************************************************************************************************************************************
***** Input : uiNewConnexite : int 																											*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Modification of variable uiGSLConnexite																						*****
************************************************************************************************************************************************/
inline void CGrayScale::GSLSetConnexite(int uiNewConnexite) {

	//Modification of variable uiGSLConnexite
	uiGSLConnexite = uiNewConnexite;
}