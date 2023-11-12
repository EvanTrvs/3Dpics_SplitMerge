#ifndef CSplit_h
#define CSplit_h

#include "CFragment.h"


class CSplitOperation {
public:
	/*****************************************************************************************************************************************************************
	***** SOTSPLITMATRICE : Méthode Divisant une matrice en fonction d'un critère d'homogénéité													                 *****
	******************************************************************************************************************************************************************
	***** Entrée : FRGMatriceComplete : CFragment | uiCritereHomogeneite : unsigned int | uiTailleMinCube : unsigned int | vFRGVectorFinal : vector <CFragment>	 *****
	***** Nécessite : Ne nécessite rien																															 *****
	***** Sortie : vFRGLeafs : vector <CFragment>																											     *****
	***** Entraine : Divise une matrice en fonction d'un critère d'homogénéité																					 *****
	*****************************************************************************************************************************************************************/
	vector <CFragment> SOTSplitMatrice(CFragment FRGMatriceComplete, unsigned int CritereHomogeneite, unsigned int uiTailleMinCube, vector <CFragment> vFRGVectorFinal);
};

#endif
