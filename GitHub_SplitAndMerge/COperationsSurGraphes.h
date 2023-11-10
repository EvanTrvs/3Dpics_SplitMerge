#ifndef COperationsSurGraphes_h
#define COperationsSurGraphes_h

#pragma once

#include "CGrapheColore.h"

class COperationsSurGraphes {
public:
	/************************************************************************************************************************************************
	***** OSGMERGEGRAPHE : M�thode fusionnant les graphes avec des correspondances																*****
	*************************************************************************************************************************************************
	***** Entr�e : vGPCGraphes : vector <CGrapheColore>	& uiHomogeneite : unsigned int															*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : vGPCGraphes : vector <CGrapheColore>																							*****
	***** Entraine : Fusionne les graphes avec des correspondances																				*****
	************************************************************************************************************************************************/
	vector <CGrapheColore> OSGMergeGraphe(vector <CGrapheColore> vGPCGraphes, unsigned int uiHomogeneite);
};

#endif

