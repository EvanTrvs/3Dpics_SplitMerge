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

	//Friend of the CMultiArrayOperation class for condensed exception handling 
	friend class CMultiArrayOperation;

private:
	/************************************************************************************************************************************************
	***** SOTSplitMatrice : Method for Split A Fragment																							*****
	*************************************************************************************************************************************************
	***** Input : FRGMatrice : CFragment & | CritereHomogeneite, uiSeuilMin : const unsigned int | vFRGVectorFinal : vector<CFragment> &		*****
	***** Precondition : uiSeuilMin need to not be null                                                                                         *****
	***** Output : None																															*****
	***** Effects : Split Method according to parameter requirements																			*****
	************************************************************************************************************************************************/
	void SOTSplitMatrice(CFragment & FRGMatrice, const unsigned int CritereHomogeneite, const unsigned int uiSeuilMin, vector<CFragment> & vFRGVectorFinal);

	/********************************************************************************************************************************************************************************************
	***** SOTSplitMatriceThreads : Method for Split A Fragment																																*****
	*********************************************************************************************************************************************************************************************
	***** Input : FRGMatrice : CFragment & | CritereHomogeneite, uiSeuilMin : const unsigned int | vFRGVectorFinal : vector<CFragment> & | OptimizationByThreads : vector<std::thread> &	*****
	***** Precondition : uiSeuilMin need to not be null																																		*****
	***** Output : None																																										*****
	***** Effects : Split Method according to parameter requirements with threads																											*****
	********************************************************************************************************************************************************************************************/
	void SOTSplitMatriceThreads(CFragment FRGMatrice, const unsigned int CritereHomogeneite, const unsigned int uiSeuilMin, vector<CFragment> & vFRGVectorFinal, vector<std::thread> & OptimizationByThreads);

	/************************************************************************************************************************************************
	***** SOTSplitMatriceSwitch : Method for Split A Fragment																					*****
	*************************************************************************************************************************************************
	***** Input : FRGMatrice : CFragment & | CritereHomogeneite, uiSeuilMin : const unsigned int | vFRGVectorFinal : vector<CFragment> &		*****
	***** Precondition : uiSeuilMin need to not be null                                                                                         *****
	***** Output : None																															*****
	***** Effects : Split Method according to parameter requirements, same a initial but with switch conditions verifications					*****
	************************************************************************************************************************************************/
	void SOTSplitMatriceSwitch(CFragment & FRGMatrice, const unsigned int CritereHomogeneite, const unsigned int uiSeuilMin, vector<CFragment>& vFRGVectorFinal);
};

#endif
