#ifndef COperationsSurGraphes_h
#define COperationsSurGraphes_h

#pragma once

#include "CGrapheColore.h"

class COperationsSurGraphes {
public:
	/************************************************************************************************************************************************
	***** OSGMERGEGRAPHE : Méthode fusionnant les graphes avec des correspondances																*****
	*************************************************************************************************************************************************
	***** Entrée : vGPCGraphes : vector <CGrapheColore>	& uiHomogeneite : unsigned int															*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : vGPCGraphes : vector <CGrapheColore>																							*****
	***** Entraine : Fusionne les graphes avec des correspondances																				*****
	************************************************************************************************************************************************/
	vector <CGrapheColore> OSGMergeGraphe(vector <CGrapheColore> vGPCGraphes, unsigned int uiHomogeneite);
};

#endif

