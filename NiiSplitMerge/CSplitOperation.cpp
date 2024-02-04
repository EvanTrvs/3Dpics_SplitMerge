#pragma once 

#include "CThreadInformation.h"
#include "CSplitOperation.h"

/************************************************************************************************************************************************
***** SOTSplitMatrice : Method for Split A Fragment																							*****
*************************************************************************************************************************************************
***** Input : FRGMatrice : CFragment & | CritereHomogeneite, uiSeuilMin : const unsigned int | vFRGVectorFinal : vector<CFragment> &		*****
***** Precondition : uiSeuilMin need to not be null                                                                                         *****
***** Output : None																															*****
***** Effects : Split Method according to parameter requirements																			*****
************************************************************************************************************************************************/
void CSplitOperation::SOTSplitMatrice(CFragment & FRGMatrice, const unsigned int CritereHomogeneite, const unsigned int uiSeuilMin, vector<CFragment> & vFRGVectorFinal) {

	//Build a Pair with Min / Max or nullptr if this Fragemnt isn't uniform
	std::pair<unsigned int, unsigned int> * puiHomoMinMax = FRGMatrice.FRGHomogeneityV2(CritereHomogeneite);

	//if not null => uniform
	if (puiHomoMinMax) {
		FRGMatrice.FRGSetMinMax(*puiHomoMinMax); //Set Min / Max of "leaf" fragment
		delete puiHomoMinMax; 

		vFRGVectorFinal.push_back(FRGMatrice); //Add the new fragment to the list
	}
	else {	
		//Calculating if the fragment (not uniform) are splittable
		std::vector<bool> vbSplitDim = FRGMatrice.FRGIsSplitable(uiSeuilMin);	//Vector of 3 boolean, true if the fragment can be split (for the dimension)

		//If at least can be splittable
		if (vbSplitDim[0] || vbSplitDim[1] || vbSplitDim[2]) {

			//return a vector of each new fragment (with coos and dimensions for each)
			std::vector< std::pair< std::vector<unsigned int>, std::vector<unsigned int>>> vpvuiNewSpots;
			FRGMatrice.FRGGetNewSpots(vbSplitDim, vpvuiNewSpots);

			//For each new fragments
			for (std::pair<std::vector<unsigned int>, std::vector<unsigned int>> pvuiNewSpot : vpvuiNewSpots) {

				//Recursivity for all new fragments
				CFragment FRGNewFragment(FRGMatrice.FRGGetMatrice(), pvuiNewSpot.first, pvuiNewSpot.second);
				SOTSplitMatrice(FRGNewFragment, CritereHomogeneite, uiSeuilMin, vFRGVectorFinal);
			}
		}
		else { //If no dimensions can be splittable => "leaf" fragement 
			FRGMatrice.FRGSetMinMax(FRGMatrice.FRGFindMinMax()); //Set Min / Max of "leaf" fragment

			vFRGVectorFinal.push_back(FRGMatrice); //Add the new fragment to the list
		}
	}
}

/********************************************************************************************************************************************************************************************
***** SOTSplitMatriceThreads : Method for Split A Fragment																																*****
*********************************************************************************************************************************************************************************************
***** Input : FRGMatrice : CFragment & | CritereHomogeneite, uiSeuilMin : const unsigned int | vFRGVectorFinal : vector<CFragment> & | OptimizationByThreads : vector<std::thread> &	*****
***** Precondition : uiSeuilMin need to not be null																																		*****
***** Output : None																																										*****
***** Effects : Split Method according to parameter requirements with threads																											*****
********************************************************************************************************************************************************************************************/
void CSplitOperation::SOTSplitMatriceThreads(CFragment FRGMatrice, const unsigned int CritereHomogeneite, const unsigned int uiSeuilMin, vector<CFragment> & vFRGVectorFinal, vector<std::thread> & OptimizationByThreads) {

	//Build a Pair with Min / Max or nullptr if this Fragemnt isn't uniform
	std::pair<unsigned int, unsigned int> * puiHomoMinMax = FRGMatrice.FRGHomogeneityV2(CritereHomogeneite);	//construit un pair contenant : min,max si homogene; null sinon

	//if not null => uniform
	if (puiHomoMinMax) {

		FRGMatrice.FRGSetMinMax(*puiHomoMinMax); //Set Min / Max of "leaf" fragment
		delete puiHomoMinMax;

		//Mutex for writting in the vector
		SOTMutex.lock();
		vFRGVectorFinal.push_back(FRGMatrice); //Add the new fragment to the list
		SOTMutex.unlock();
	}
	else {	
		//Calculating if the fragment (not uniform) are splittable
		std::vector<bool> vbSplitDim = FRGMatrice.FRGIsSplitable(uiSeuilMin);	//vector de 3 booleen, pour chaque dimension, true si peut split

		//If at least can be splittable
		if (vbSplitDim[0] || vbSplitDim[1] || vbSplitDim[2]) {

			//return a vector of each new fragment (with coos and dimensions for each)
			std::vector< std::pair< std::vector<unsigned int>, std::vector<unsigned int>>> vpvuiNewSpots;
			FRGMatrice.FRGGetNewSpots(vbSplitDim, vpvuiNewSpots);
			
			//Increment 1 to make a single subdivision
			CThreadInformation::TDIIncrementCurrentThreadCount();
			unsigned int uiValeurActuel = CThreadInformation::TDIGetCurrentThreadCount(); //local storage

			//For each new fragments
			for (std::pair<std::vector<unsigned int>, std::vector<unsigned int>> pvuiNewSpot : vpvuiNewSpots) {

				//Récursivité sur ces fragments en créant de nouveau fragment
				CFragment FRGNewFragment(FRGMatrice.FRGGetMatrice(), pvuiNewSpot.first, pvuiNewSpot.second);

				//If thread count isn't equal to the limit => thread management using the CThreadInformation class
				if (uiValeurActuel <= CThreadInformation::TDIGetThreadLimit()) {

					//Emplace for create the thread in the vector (because a thread is different of a variable - can't be copy)
					OptimizationByThreads.emplace_back(&CSplitOperation::SOTSplitMatriceThreads, this, FRGNewFragment, CritereHomogeneite, uiSeuilMin, std::ref(vFRGVectorFinal), std::ref(OptimizationByThreads)); //Recursivity
				}
				else {

					SOTSplitMatriceThreads(FRGNewFragment, CritereHomogeneite, uiSeuilMin, vFRGVectorFinal, OptimizationByThreads); //Recursivity without threads
				}
			}
		}
		else { //If no dimensions can be splittable => "leaf" fragement 
			FRGMatrice.FRGSetMinMax(FRGMatrice.FRGFindMinMax()); //Set Min / Max of "leaf" fragment

			//Mutex for writting in the vector
			SOTMutex.lock();
			vFRGVectorFinal.push_back(FRGMatrice); //Add the new fragment to the list
			SOTMutex.unlock();
		}
	}
}

/************************************************************************************************************************************************
***** SOTSplitMatrice : Method for Split A Fragment																							*****
*************************************************************************************************************************************************
***** Input : FRGMatrice : CFragment & | CritereHomogeneite, uiSeuilMin : const unsigned int | vFRGVectorFinal : vector<CFragment> &		*****
***** Precondition : uiSeuilMin need to not be null                                                                                         *****
***** Output : None																															*****
***** Effects : Split Method according to parameter requirements, same a initial but with switch conditions verifications					*****
************************************************************************************************************************************************/
void CSplitOperation::SOTSplitMatriceSwitch(CFragment& FRGMatrice, const unsigned int CritereHomogeneite, const unsigned int uiSeuilMin, vector<CFragment>& vFRGVectorFinal) {

	//Calculating if the fragment (not uniform) are splittable
	std::vector<bool> vbSplitDim = FRGMatrice.FRGIsSplitable(uiSeuilMin);	//Vector of 3 boolean, true if the fragment can be split (for the dimension)

	//If at least can be splittable
	if (vbSplitDim[0] || vbSplitDim[1] || vbSplitDim[2]) {
		//Build a Pair with Min / Max or nullptr if this Fragemnt isn't uniform
		std::pair<unsigned int, unsigned int>* puiHomoMinMax = FRGMatrice.FRGHomogeneityV2(CritereHomogeneite);

		//if not null => uniform
		if (puiHomoMinMax) {
			FRGMatrice.FRGSetMinMax(*puiHomoMinMax); //Set Min / Max of "leaf" fragment
			delete puiHomoMinMax;

			vFRGVectorFinal.push_back(FRGMatrice); //Add the new fragment to the list
		}
		else {
			//return a vector of each new fragment (with coos and dimensions for each)
			std::vector< std::pair< std::vector<unsigned int>, std::vector<unsigned int>>> vpvuiNewSpots;
			FRGMatrice.FRGGetNewSpots(vbSplitDim, vpvuiNewSpots);

			//For each new fragments
			for (std::pair<std::vector<unsigned int>, std::vector<unsigned int>> pvuiNewSpot : vpvuiNewSpots) {

				//Recursivity for all new fragments
				CFragment FRGNewFragment(FRGMatrice.FRGGetMatrice(), pvuiNewSpot.first, pvuiNewSpot.second);
				SOTSplitMatrice(FRGNewFragment, CritereHomogeneite, uiSeuilMin, vFRGVectorFinal);
			}
		}
	}
	else { //If no dimensions can be splittable => "leaf" fragement 
		FRGMatrice.FRGSetMinMax(FRGMatrice.FRGFindMinMax()); //Set Min / Max of "leaf" fragment

		vFRGVectorFinal.push_back(FRGMatrice); //Add the new fragment to the list
	}
}