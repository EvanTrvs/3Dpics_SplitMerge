#ifndef CSplit_h
#define CSplit_h

#include "CFragment.h"


class CSplitOperation {
public:
	/*****************************************************************************************************************************************************************
	***** SOTSPLITMATRICE : M�thode Divisant une matrice en fonction d'un crit�re d'homog�n�it�													                 *****
	******************************************************************************************************************************************************************
	***** Entr�e : FRGMatriceComplete : CFragment | uiCritereHomogeneite : unsigned int | uiTailleMinCube : unsigned int | vFRGVectorFinal : vector <CFragment>	 *****
	***** N�cessite : Ne n�cessite rien																															 *****
	***** Sortie : vFRGLeafs : vector <CFragment>																											     *****
	***** Entraine : Divise une matrice en fonction d'un crit�re d'homog�n�it�																					 *****
	*****************************************************************************************************************************************************************/
	vector <CFragment> SOTSplitMatrice(CFragment FRGMatriceComplete, unsigned int CritereHomogeneite, unsigned int uiTailleMinCube, vector <CFragment> vFRGVectorFinal);
};

#endif
