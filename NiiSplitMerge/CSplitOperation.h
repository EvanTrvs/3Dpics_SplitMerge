#ifndef CSplit_h
#define CSplit_h

#include <vector>
#include <thread>
#include <mutex>
#include <functional>

#include "CFragment.h"
#include "CMultiArrayOperation.h"

#define SEUIL_MIN 2


class CSplitOperation {
private:

	std::mutex SOTMutex;

	//Friend de la classe CMultiArrayOperation pour une gestion des exceptions condens� 
	friend class CMultiArrayOperation;

private:
	/************************************************************************************************************************************************
	***** SOTSPLITMATRICE : M�thode de Split Classique																							*****
	*************************************************************************************************************************************************
	***** Entr�e : FRGMatrice : CFragment & | CritereHomogeneite, uiSeuilMin : const unsigned int | vFRGVectorFinal : vector<CFragment> &		*****
	***** N�cessite : La taille minimum des cubes ne peux �tre �gale � 0                                                                        *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : M�thode de Split selon les crit�res pass�s en param�tre																	*****
	************************************************************************************************************************************************/
	void SOTSplitMatrice(CFragment & FRGMatrice, const unsigned int CritereHomogeneite, const unsigned int uiSeuilMin, vector<CFragment> & vFRGVectorFinal);

	/********************************************************************************************************************************************************************************************
	***** SOTSPLITMATRICETHREADS : M�thode de Split avec des Threads																														*****
	*********************************************************************************************************************************************************************************************
	***** Entr�e : FRGMatrice : CFragment & | CritereHomogeneite, uiSeuilMin : const unsigned int | vFRGVectorFinal : vector<CFragment> & | OptimizationByThreads : vector<std::thread> &	*****
	***** N�cessite : La taille minimum des cubes ne peux �tre �gale � 0																													*****
	***** Sortie : Aucun �l�ment retourn�																																					*****
	***** Entraine : M�thode de Split avec des Threads selon les crit�res pass�s en param�tre																								*****
	********************************************************************************************************************************************************************************************/
	void SOTSplitMatriceThreads(CFragment FRGMatrice, const unsigned int CritereHomogeneite, const unsigned int uiSeuilMin, vector<CFragment> & vFRGVectorFinal, vector<std::thread> & OptimizationByThreads);
};

#endif
