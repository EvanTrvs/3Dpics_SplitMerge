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

	//Friend de la classe CMultiArrayOperation pour une gestion des exceptions condensé 
	friend class CMultiArrayOperation;

private:
	/************************************************************************************************************************************************
	***** SOTSPLITMATRICE : Méthode de Split Classique																							*****
	*************************************************************************************************************************************************
	***** Entrée : FRGMatrice : CFragment & | CritereHomogeneite, uiSeuilMin : const unsigned int | vFRGVectorFinal : vector<CFragment> &		*****
	***** Nécessite : La taille minimum des cubes ne peux être égale à 0                                                                        *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Méthode de Split selon les critères passés en paramètre																	*****
	************************************************************************************************************************************************/
	void SOTSplitMatrice(CFragment & FRGMatrice, const unsigned int CritereHomogeneite, const unsigned int uiSeuilMin, vector<CFragment> & vFRGVectorFinal);

	/********************************************************************************************************************************************************************************************
	***** SOTSPLITMATRICETHREADS : Méthode de Split avec des Threads																														*****
	*********************************************************************************************************************************************************************************************
	***** Entrée : FRGMatrice : CFragment & | CritereHomogeneite, uiSeuilMin : const unsigned int | vFRGVectorFinal : vector<CFragment> & | OptimizationByThreads : vector<std::thread> &	*****
	***** Nécessite : La taille minimum des cubes ne peux être égale à 0																													*****
	***** Sortie : Aucun élément retourné																																					*****
	***** Entraine : Méthode de Split avec des Threads selon les critères passés en paramètre																								*****
	********************************************************************************************************************************************************************************************/
	void SOTSplitMatriceThreads(CFragment FRGMatrice, const unsigned int CritereHomogeneite, const unsigned int uiSeuilMin, vector<CFragment> & vFRGVectorFinal, vector<std::thread> & OptimizationByThreads);
};

#endif
