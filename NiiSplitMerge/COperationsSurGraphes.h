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

#define GRAPHE_VIDE 3

typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS, CFragment> BGLGrapheAffichage;

class COperationsSurGraphes {
public:

	/************************************************************************************************************************************************
	***** OSGGrapheToMatrice : Function convert graphe to multi_array																			*****
	*************************************************************************************************************************************************
	***** Input : alGraphe : BGLGrapheAffichage																									*****
	***** Precondition : Nothing                                                                                                                *****
	***** Output : maMatriceGroupe : boost::multi_array <unsigned int, 3>																		*****
	***** Effects : Convert graphe to multi_array with connexity for each elements			                                                    *****
	************************************************************************************************************************************************/
	boost::multi_array <unsigned int, 3> OSGGrapheToMatrice(BGLGrapheAffichage alGraphe);
};

#endif

