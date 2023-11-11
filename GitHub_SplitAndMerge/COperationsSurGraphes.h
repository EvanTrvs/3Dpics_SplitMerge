#ifndef COperationsSurGraphes_h
#define COperationsSurGraphes_h

#pragma once

#include "CGrapheColore.h"
#include "CVoxel.h"

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

	/************************************************************************************************************************************************
	***** OSGGRAPHETOMATRICE : M�thode cr�ant une matrice de Voxel ayant des informations de groupe												*****
	*************************************************************************************************************************************************
	***** Entr�e : vGPCraphes : vector <CGrapheColore>																							*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : vFRGLeafs : vector <CFragment>                                                                                               *****
	***** Entraine : Cr�ation d'une matrice de Voxel ayant des informations de groupe															*****
	************************************************************************************************************************************************/
	boost::multi_array <CVoxel, 3> OSGGrapheToMatrice(vector <CGrapheColore> vGPCGraphes);
};

#endif

