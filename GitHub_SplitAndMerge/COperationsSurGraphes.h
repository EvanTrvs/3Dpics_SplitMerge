#ifndef COperationsSurGraphes_h
#define COperationsSurGraphes_h

#pragma once

#include "CGrapheColore.h"
#include "CVoxel.h"

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

	/************************************************************************************************************************************************
	***** OSGGRAPHETOMATRICE : Méthode créant une matrice de Voxel ayant des informations de groupe												*****
	*************************************************************************************************************************************************
	***** Entrée : vGPCraphes : vector <CGrapheColore>																							*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : vFRGLeafs : vector <CFragment>                                                                                               *****
	***** Entraine : Création d'une matrice de Voxel ayant des informations de groupe															*****
	************************************************************************************************************************************************/
	boost::multi_array <CVoxel, 3> OSGGrapheToMatrice(vector <CGrapheColore> vGPCGraphes);
};

#endif

