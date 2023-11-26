#ifndef CSplit_h
#define CSplit_h

#include <vector>
#include <thread>
#include <mutex>
#include <functional>

#include "CFragment.h"


class CSplitOperation {

	std::mutex SOTMutex;

public:
	/************************************************************************************************************************************************************************************************************************
	***** SOTSPLITMATRICE : M�thode Divisant une matrice en fonction d'un crit�re d'homog�n�it�																													  	    *****
	*************************************************************************************************************************************************************************************************************************
	***** Entr�e : FRGMatriceComplete : CFragment | uiCritereHomogeneite : unsigned int | uiTailleMinCube : unsigned int | vFRGVectorFinal : vector <CFragment>	* | OptimizationByThreads : vector<std::thread> *		*****
	***** N�cessite : Ne n�cessite rien																																												    *****
	***** Sortie : Aucun El�ments Retourn�s																																												*****
	***** Entraine : Divise une matrice en fonction d'un crit�re d'homog�n�it�																																		    *****
	************************************************************************************************************************************************************************************************************************/
	void SOTSplitMatrice(CFragment FRGMatrice, unsigned int uiCritereHomogeneite, unsigned int uiTailleMinCube, vector <CFragment> *vFRGVectorFinal, vector<std::thread> * OptimizationByThreads);
	void SOTSplitMatriceV2(CFragment & FRGMatrice, const unsigned int CritereHomogeneite, const unsigned int SeuilMin, vector<CFragment> & vFRGVectorFinal, vector<std::thread> & OptimizationByThreads);
	void SOTSplitMatriceV3(CFragment & FRGMatrice, const unsigned int CritereHomogeneite, const unsigned int SeuilMin, vector<CFragment> & vFRGVectorFinal);

private:
	void SOTThreadedSplit(CFragment FRGMatrice, unsigned int uiCritereHomogeneite, unsigned int uiTailleMinCube, std::vector<CFragment>* vFRGVectorFinal, vector<std::thread> * OptimizationByThreads);
};

#endif
