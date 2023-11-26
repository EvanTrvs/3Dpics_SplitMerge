#pragma once 

#include "CThreadInformation.h"
#include "CSplitOperation.h"

std::pair <vector <unsigned int>, std::tuple <bool, bool, bool>> SplitCase(vector <unsigned int> vuiDimension, unsigned int uiTailleMinCube) {

	unsigned int uiDimX = static_cast<unsigned int> (round((double)vuiDimension[0] / 2)); //Coos X milieu
	unsigned int uiDimY = static_cast<unsigned int> (round((double)vuiDimension[1] / 2)); //Coos Y milieu
	unsigned int uiDimZ = static_cast<unsigned int> (round((double)vuiDimension[2] / 2)); //Coos Z milieu

	unsigned int uiDimX2 = vuiDimension[0] - uiDimX; //Dim Pour Coos X Milieu
	unsigned int uiDimY2 = vuiDimension[1] - uiDimY; //Dim Pour Coos Y Milieu
	unsigned int uiDimZ2 = vuiDimension[2] - uiDimZ; //Dim Pour Coos Z Milieu

	std::pair <vector <unsigned int>, std::tuple <bool, bool, bool>> DimAndCase;
	DimAndCase.first = { uiDimX, uiDimY, uiDimZ, uiDimX2, uiDimY2, uiDimZ2 };
	DimAndCase.second = { true, true, true };

	return DimAndCase;
}

/************************************************************************************************************************************************************************************************************************
***** SOTSPLITMATRICE : Méthode Divisant une matrice en fonction d'un critère d'homogénéité																													  	    *****
*************************************************************************************************************************************************************************************************************************
***** Entrée : FRGMatriceComplete : CFragment | uiCritereHomogeneite : unsigned int | uiTailleMinCube : unsigned int | vFRGVectorFinal : vector <CFragment>	* | OptimizationByThreads : vector<std::thread>	*		*****
***** Nécessite : Ne nécessite rien																																												    *****
***** Sortie : Aucun Eléments Retournés																																												*****
***** Entraine : Divise une matrice en fonction d'un critère d'homogénéité																																		    *****
************************************************************************************************************************************************************************************************************************/
void CSplitOperation::SOTSplitMatrice(CFragment FRGMatrice, unsigned int uiCritereHomogeneite, unsigned int uiTailleMinCube, vector <CFragment> *vFRGVectorFinal, vector<std::thread> * OptimizationByThreads) {

	unsigned int uiVolumeCube = FRGMatrice.FRGGetDimensions()[0] * FRGMatrice.FRGGetDimensions()[1] * FRGMatrice.FRGGetDimensions()[2];
	if ((!FRGMatrice.FRGHomogeneity(uiCritereHomogeneite)) && (uiVolumeCube > uiTailleMinCube*uiTailleMinCube*uiTailleMinCube)) {

		vector <unsigned int> vuiDimension = { FRGMatrice.FRGGetDimensions()[0], FRGMatrice.FRGGetDimensions()[1], FRGMatrice.FRGGetDimensions()[2] };
		std::pair <vector <unsigned int>, std::tuple <bool, bool, bool>> DimAndCase = SplitCase(vuiDimension, uiTailleMinCube);

		vector <unsigned int> Dimension = DimAndCase.first;
		std::tuple <bool, bool, bool> Case = DimAndCase.second;
		unsigned int uiNum = FRGMatrice.FRGGetNum();

		CFragment FRGNewFragmentNWF(FRGMatrice.FRGGetMatrice(), FRGMatrice.FRGGetCoos(), { Dimension[0] , Dimension[1], Dimension[2] }, uiNum + vFRGVectorFinal->size()); //Fragment positionner au Nord + West + Front 

		CThreadInformation::TDIIncrementCurrentThreadCount();
		if (CThreadInformation::TDIGetCurrentThreadCount() < CThreadInformation::TDIGetThreadLimit()) {
			std::thread NWF = thread(&CSplitOperation::SOTThreadedSplit, this, FRGNewFragmentNWF, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads); //Recursivité
			OptimizationByThreads->push_back(std::move(NWF));
		}
		else {
			SOTSplitMatrice(FRGNewFragmentNWF, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads); //Recursivité
		}

		if ((FRGMatrice.FRGGetDimensions()[2] != 1) && (Dimension[5] >= uiTailleMinCube)) {
			CFragment FRGNewFragmentNWB(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0], FRGMatrice.FRGGetCoos()[1], FRGMatrice.FRGGetCoos()[2] + Dimension[0] }, { Dimension[0] , Dimension[1], Dimension[5] }, uiNum + vFRGVectorFinal->size()); //Fragment positionner au Nord + West + Behind 

			CThreadInformation::TDIIncrementCurrentThreadCount();
			if (CThreadInformation::TDIGetCurrentThreadCount() < CThreadInformation::TDIGetThreadLimit()) {
				std::thread NWB = thread(&CSplitOperation::SOTThreadedSplit, this, FRGNewFragmentNWB, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads); //Recursivité
				OptimizationByThreads->push_back(std::move(NWB));
			}
			else {
				SOTSplitMatrice(FRGNewFragmentNWB, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads); //Recursivité
			}
		}

		if ((FRGMatrice.FRGGetDimensions()[0] != 1) && (Dimension[3] >= uiTailleMinCube)) {
			CFragment FRGNewFragmentNEF(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0] + Dimension[0], FRGMatrice.FRGGetCoos()[1], FRGMatrice.FRGGetCoos()[2] }, { Dimension[3] , Dimension[1], Dimension[2] }, uiNum + vFRGVectorFinal->size()); //Fragment positionner au Nord + East + Front 

			CThreadInformation::TDIIncrementCurrentThreadCount();
			if (CThreadInformation::TDIGetCurrentThreadCount() < CThreadInformation::TDIGetThreadLimit()) {
				std::thread NEF = thread(&CSplitOperation::SOTThreadedSplit, this, FRGNewFragmentNEF, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads); //Recursivité
				OptimizationByThreads->push_back(std::move(NEF));
			}
			else {
				SOTSplitMatrice(FRGNewFragmentNEF, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads); //Recursivité
			}
		}

		if ((FRGMatrice.FRGGetDimensions()[0] != 1) && (FRGMatrice.FRGGetDimensions()[2] != 1) && (Dimension[3] >= uiTailleMinCube) && (Dimension[5] >= uiTailleMinCube)) {
			CFragment FRGNewFragmentNEB(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0] + Dimension[0], FRGMatrice.FRGGetCoos()[1], FRGMatrice.FRGGetCoos()[2] + Dimension[2] }, { Dimension[3] , Dimension[1], Dimension[5] }, uiNum + vFRGVectorFinal->size()); //Fragment positionner au Nord + East + Behind 

			CThreadInformation::TDIIncrementCurrentThreadCount();
			if (CThreadInformation::TDIGetCurrentThreadCount() < CThreadInformation::TDIGetThreadLimit()) {
				std::thread NEB = thread(&CSplitOperation::SOTThreadedSplit, this, FRGNewFragmentNEB, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads); //Recursivité
				OptimizationByThreads->push_back(std::move(NEB));
			}
			else {
				SOTSplitMatrice(FRGNewFragmentNEB, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads); //Recursivité
			}
		}

		if ((FRGMatrice.FRGGetDimensions()[1] != 1) && (Dimension[4] >= uiTailleMinCube)) {
			CFragment FRGNewFragmentSWF(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0], FRGMatrice.FRGGetCoos()[1] + Dimension[2], FRGMatrice.FRGGetCoos()[2] }, { Dimension[0] , Dimension[4], Dimension[2] }, uiNum + vFRGVectorFinal->size()); //Fragment positionner au South + West + Front 

			CThreadInformation::TDIIncrementCurrentThreadCount();
			if (CThreadInformation::TDIGetCurrentThreadCount() < CThreadInformation::TDIGetThreadLimit()) {
				std::thread SWF = thread(&CSplitOperation::SOTThreadedSplit, this, FRGNewFragmentSWF, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads); //Recursivité
				OptimizationByThreads->push_back(std::move(SWF));
			}
			else {
				SOTSplitMatrice(FRGNewFragmentSWF, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads); //Recursivité
			}
		}

		if ((FRGMatrice.FRGGetDimensions()[1] != 1) && (FRGMatrice.FRGGetDimensions()[2] != 1) && (Dimension[4] >= uiTailleMinCube) && (Dimension[5] >= uiTailleMinCube)) {
			CFragment FRGNewFragmentSWB(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0], FRGMatrice.FRGGetCoos()[1] + Dimension[1], FRGMatrice.FRGGetCoos()[2] + Dimension[2] }, { Dimension[0] , Dimension[4], Dimension[5] }, uiNum + vFRGVectorFinal->size()); //Fragment positionner au South + West + Behind 

			CThreadInformation::TDIIncrementCurrentThreadCount();
			if (CThreadInformation::TDIGetCurrentThreadCount() < CThreadInformation::TDIGetThreadLimit()) {
				std::thread SWB = thread(&CSplitOperation::SOTThreadedSplit, this, FRGNewFragmentSWB, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads); //Recursivité
				OptimizationByThreads->push_back(std::move(SWB));
			}
			else {
				SOTSplitMatrice(FRGNewFragmentSWB, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads); //Recursivité
			}
		}

		if ((FRGMatrice.FRGGetDimensions()[0] != 1) && (FRGMatrice.FRGGetDimensions()[1] != 1) && (Dimension[3] >= uiTailleMinCube) && (Dimension[4] >= uiTailleMinCube)) {
			CFragment FRGNewFragmentSEF(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0] + Dimension[0], FRGMatrice.FRGGetCoos()[1] + Dimension[1], FRGMatrice.FRGGetCoos()[2] }, { Dimension[3] , Dimension[4], Dimension[2] }, uiNum + vFRGVectorFinal->size()); //Fragment positionner au South + East + Front 

			CThreadInformation::TDIIncrementCurrentThreadCount();
			if (CThreadInformation::TDIGetCurrentThreadCount() < CThreadInformation::TDIGetThreadLimit()) {
				std::thread SEF = thread(&CSplitOperation::SOTThreadedSplit, this, FRGNewFragmentSEF, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads); //Recursivité
				OptimizationByThreads->push_back(std::move(SEF));
			}
			else {
				SOTSplitMatrice(FRGNewFragmentSEF, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads); //Recursivité
			}
		}

		if ((FRGMatrice.FRGGetDimensions()[0] != 1) && (FRGMatrice.FRGGetDimensions()[1] != 1) && (FRGMatrice.FRGGetDimensions()[2] != 1) && (Dimension[3] >= uiTailleMinCube) && (Dimension[4] >= uiTailleMinCube) && (Dimension[5] >= uiTailleMinCube)) {
			CFragment FRGNewFragmentSEB(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0] + Dimension[0], FRGMatrice.FRGGetCoos()[1] + Dimension[1], FRGMatrice.FRGGetCoos()[2] + Dimension[2] }, { Dimension[3] , Dimension[4], Dimension[5] }, uiNum + vFRGVectorFinal->size()); //Fragment positionner au South + East + Behind 

			CThreadInformation::TDIIncrementCurrentThreadCount();
			if (CThreadInformation::TDIGetCurrentThreadCount() < CThreadInformation::TDIGetThreadLimit()) {
				std::thread SEB = thread(&CSplitOperation::SOTThreadedSplit, this, FRGNewFragmentSEB, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads); //Recursivité
				OptimizationByThreads->push_back(std::move(SEB));
			}
			else {
				SOTSplitMatrice(FRGNewFragmentSEB, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads); //Recursivité
			}
		}
	}
	else {
		std::lock_guard<std::mutex> lock(SOTMutex);
		vFRGVectorFinal->push_back(FRGMatrice);
	}
}

void CSplitOperation::SOTThreadedSplit(CFragment FRGMatrice, unsigned int uiCritereHomogeneite, unsigned int uiTailleMinCube, std::vector<CFragment>* vFRGVectorFinal, vector<std::thread> * OptimizationByThreads) {
	// Fonction récursive appelée par le thread
	SOTSplitMatrice(FRGMatrice, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal, OptimizationByThreads);
}

void CSplitOperation::SOTSplitMatriceV2(CFragment & FRGMatrice, const unsigned int CritereHomogeneite, const unsigned int SeuilMin, vector<CFragment> & vFRGVectorFinal, vector<std::thread> & OptimizationByThreads) {

	std::pair<unsigned int, unsigned int> * puiHomoMinMax = FRGMatrice.FRGHomogeneityV2(CritereHomogeneite);	//construit un pair contenant : min,max si homogene; null sinon
	if (puiHomoMinMax) {		//non nullptr, donc homogene
		//FRGMatrice.FRGSetMinMax(*puiHomoMinMax);		//applique le min/max calcule
		delete puiHomoMinMax;

		SOTMutex.lock();
		vFRGVectorFinal.push_back(FRGMatrice);	//ajoute le fragment "feuille" a la liste
		SOTMutex.unlock();
	}
	else {			//test du respect de la taille minimum
		std::vector<bool> vbSplitDim = FRGMatrice.IsSplitable(SeuilMin);		//vector de 3 booleen, pour chaque dimension, true si peut split

		if (vbSplitDim[0] || vbSplitDim[1] || vbSplitDim[2]) {	//si au moins 1 dimension peut être split

			//retourne une liste de chaque nouvelle region avec les nouvelles coordonee et dimension
			std::vector< std::pair< std::vector<unsigned int>, std::vector<unsigned int>>> vpvuiNewSpots;
			FRGMatrice.FRGGetNewSpots(vbSplitDim, vpvuiNewSpots);
			unsigned int uiNum = FRGMatrice.FRGGetNum();

			//if (vpvuiNewSpots.empty()) CExeption //pas de spot calcule probleme
			for (std::pair<std::vector<unsigned int>, std::vector<unsigned int>> pvuiNewSpot : vpvuiNewSpots) {	//pour chaque element de la liste de region

				CFragment FRGNewFragment(FRGMatrice.FRGGetMatrice(), pvuiNewSpot.first, pvuiNewSpot.second, uiNum + vFRGVectorFinal.size()); //creer un nouveau fragment 
				CThreadInformation::TDIIncrementCurrentThreadCount();
				if (CThreadInformation::TDIGetCurrentThreadCount() < CThreadInformation::TDIGetThreadLimit()) {
					std::thread ThreadSplit = thread(&CSplitOperation::SOTSplitMatriceV2, this, std::ref(FRGNewFragment), CritereHomogeneite, SeuilMin, std::ref(vFRGVectorFinal), std::ref(OptimizationByThreads)); //Recursivité
					OptimizationByThreads.push_back(std::move(ThreadSplit));
				}
				else {
					SOTSplitMatriceV2(FRGNewFragment, CritereHomogeneite, SeuilMin, vFRGVectorFinal, OptimizationByThreads); //lui applique la Recursivite
				}
			}
		}
		else {		//aucune dimension ne peut etre split, fin
			//FRGMatrice.FRGSetMinMax(FRGMatrice.FRGFindMinMax());		//calcule et applique le min/max
			SOTMutex.lock();
			vFRGVectorFinal.push_back(FRGMatrice);			//ajoute le fragment "feuille" a la liste
			SOTMutex.unlock();
		}
	}
}

void CSplitOperation::SOTSplitMatriceV3(CFragment & FRGMatrice, const unsigned int CritereHomogeneite, const unsigned int SeuilMin, vector<CFragment> & vFRGVectorFinal) {

	std::pair<unsigned int, unsigned int> * puiHomoMinMax = FRGMatrice.FRGHomogeneityV2(CritereHomogeneite);	//construit un pair contenant : min,max si homogene; null sinon
	if (puiHomoMinMax) {		//non nullptr, donc homogene
		//FRGMatrice.FRGSetMinMax(*puiHomoMinMax);		//applique le min/max calcule
		delete puiHomoMinMax;

		vFRGVectorFinal.push_back(FRGMatrice);	//ajoute le fragment "feuille" a la liste
	}
	else {			//test du respect de la taille minimum
		std::vector<bool> vbSplitDim = FRGMatrice.IsSplitable(SeuilMin);		//vector de 3 booleen, pour chaque dimension, true si peut split

		if (vbSplitDim[0] || vbSplitDim[1] || vbSplitDim[2]) {	//si au moins 1 dimension peut être split

			//retourne une liste de chaque nouvelle region avec les nouvelles coordonee et dimension
			std::vector< std::pair< std::vector<unsigned int>, std::vector<unsigned int>>> vpvuiNewSpots;
			FRGMatrice.FRGGetNewSpots(vbSplitDim, vpvuiNewSpots);
			unsigned int uiNum = FRGMatrice.FRGGetNum();

			//if (vpvuiNewSpots.empty()) CExeption //pas de spot calcule probleme
			for (std::pair<std::vector<unsigned int>, std::vector<unsigned int>> pvuiNewSpot : vpvuiNewSpots) {	//pour chaque element de la liste de region

				CFragment FRGNewFragment(FRGMatrice.FRGGetMatrice(), pvuiNewSpot.first, pvuiNewSpot.second, uiNum + vFRGVectorFinal.size()); //creer un nouveau fragment 
				SOTSplitMatriceV3(FRGNewFragment, CritereHomogeneite, SeuilMin, vFRGVectorFinal); //lui applique la Recursivite
			}
		}
		else {		//aucune dimension ne peut etre split, fin
			//FRGMatrice.FRGSetMinMax(FRGMatrice.FRGFindMinMax());		//calcule et applique le min/max
			vFRGVectorFinal.push_back(FRGMatrice);			//ajoute le fragment "feuille" a la liste
		}
	}
}