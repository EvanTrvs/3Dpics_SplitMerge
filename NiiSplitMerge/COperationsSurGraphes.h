#ifndef COperationsSurGraphes_h
#define COperationsSurGraphes_h

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

#include "CFragment.h"
#include "CVoxel.h"

#define GRAPHE_VIDE 3

typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS, CFragment> BGLGrapheAffichage;

class COperationsSurGraphes {
public:

	/************************************************************************************************************************************************
	***** OSGGRAPHETOMATRICE : M�thode transformant un graphe de fragment en matrice															*****
	*************************************************************************************************************************************************
	***** Entr�e : alGraphe : BGLGrapheAffichage																								*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : maMatriceGroupe : boost::multi_array <unsigned int, 3>													                    *****
	***** Entraine : Transforme un graphe en matrice avec comme �l�ment les groupes de chaque voxels											*****
	************************************************************************************************************************************************/
	boost::multi_array <unsigned int, 3> OSGGrapheToMatrice(BGLGrapheAffichage alGraphe);
};

#endif

