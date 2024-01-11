#pragma once 

#include "CThreadInformation.h"
#include "CSplitOperation.h"

/************************************************************************************************************************************************
***** SOTSPLITMATRICE : Méthode de Split Classique																							*****
*************************************************************************************************************************************************
***** Entrée : FRGMatrice : CFragment & | CritereHomogeneite, uiSeuilMin : const unsigned int | vFRGVectorFinal : vector<CFragment> &		*****
***** Nécessite : La taille minimum des cubes ne peux être égale à 0                                                                        *****
***** Sortie : Aucun élément retourné																										*****
***** Entraine : Méthode de Split selon les critères passés en paramètre																	*****
************************************************************************************************************************************************/
void CSplitOperation::SOTSplitMatrice(CFragment & FRGMatrice, const unsigned int CritereHomogeneite, const unsigned int uiSeuilMin, vector<CFragment> & vFRGVectorFinal) {

	//Gestion de l'exception : Taille minimum = 0
	if (uiSeuilMin == 0) {
		CException EXCErreur;
		EXCErreur.EXCModifierValeur(SEUIL_MIN);
		throw (EXCErreur);
	}

	//construit un pair contenant : min,max si homogene; null sinon
	std::pair<unsigned int, unsigned int> * puiHomoMinMax = FRGMatrice.FRGHomogeneityV2(CritereHomogeneite);

	//Si non null => Homogène
	if (puiHomoMinMax) {
		FRGMatrice.FRGSetMinMax(*puiHomoMinMax); //Set le min / max du fragment "feuille"
		delete puiHomoMinMax; 

		vFRGVectorFinal.push_back(FRGMatrice); //ajoute le fragment "feuille" a la liste
	}
	else {	
		//Calcul si le fragment non homogène est divisible
		std::vector<bool> vbSplitDim = FRGMatrice.FRGIsSplitable(uiSeuilMin);	//vector de 3 booleen, pour chaque dimension, true si peut split

		//si au moins 1 dimension peut être split
		if (vbSplitDim[0] || vbSplitDim[1] || vbSplitDim[2]) {

			//retourne une liste de chaque nouvelle region avec les nouvelles coordonnées et dimensions
			std::vector< std::pair< std::vector<unsigned int>, std::vector<unsigned int>>> vpvuiNewSpots;
			FRGMatrice.FRGGetNewSpots(vbSplitDim, vpvuiNewSpots);

			//Pour tout les nouveaux fragments 
			for (std::pair<std::vector<unsigned int>, std::vector<unsigned int>> pvuiNewSpot : vpvuiNewSpots) {

				//Récursivité sur ces fragments en créant de nouveau fragment
				CFragment FRGNewFragment(FRGMatrice.FRGGetMatrice(), pvuiNewSpot.first, pvuiNewSpot.second);
				SOTSplitMatrice(FRGNewFragment, CritereHomogeneite, uiSeuilMin, vFRGVectorFinal);
			}
		}
		else { //Si aucun dimension n'est divisible => fragment "feuille"
			FRGMatrice.FRGSetMinMax(FRGMatrice.FRGFindMinMax()); //Set le min / max du fragment "feuille"

			vFRGVectorFinal.push_back(FRGMatrice); //ajoute le fragment "feuille" a la liste
		}
	}
}

/********************************************************************************************************************************************************************************************
***** SOTSPLITMATRICETHREADS : Méthode de Split avec des Threads																														*****
*********************************************************************************************************************************************************************************************
***** Entrée : FRGMatrice : CFragment & | CritereHomogeneite, uiSeuilMin : const unsigned int | vFRGVectorFinal : vector<CFragment> & | OptimizationByThreads : vector<std::thread> &	*****
***** Nécessite : La taille minimum des cubes ne peux être égale à 0																													*****
***** Sortie : Aucun élément retourné																																					*****
***** Entraine : Méthode de Split avec des Threads selon les critères passés en paramètre																								*****
********************************************************************************************************************************************************************************************/
void CSplitOperation::SOTSplitMatriceThreads(CFragment FRGMatrice, const unsigned int CritereHomogeneite, const unsigned int uiSeuilMin, vector<CFragment> & vFRGVectorFinal, vector<std::thread> & OptimizationByThreads) {
		//Gestion de l'exception : Taille minimum = 0
	if (uiSeuilMin == 0) {
		CException EXCErreur;
		EXCErreur.EXCModifierValeur(SEUIL_MIN);
		throw (EXCErreur);
	}

	//construit un pair contenant : min,max si homogene; null sinon
	std::pair<unsigned int, unsigned int> * puiHomoMinMax = FRGMatrice.FRGHomogeneityV2(CritereHomogeneite);	//construit un pair contenant : min,max si homogene; null sinon

	//Si non null => Homogène
	if (puiHomoMinMax) {

		FRGMatrice.FRGSetMinMax(*puiHomoMinMax); //Set le min / max du fragment "feuille"
		delete puiHomoMinMax;

		//Mutex pour l'écriture dans le vecteur
		SOTMutex.lock();
		vFRGVectorFinal.push_back(FRGMatrice); //ajoute le fragment "feuille" a la liste
		SOTMutex.unlock();
	}
	else {	//Calcul si le fragment non homogène est divisible
		std::vector<bool> vbSplitDim = FRGMatrice.FRGIsSplitable(uiSeuilMin);	//vector de 3 booleen, pour chaque dimension, true si peut split

		//si au moins 1 dimension peut être split
		if (vbSplitDim[0] || vbSplitDim[1] || vbSplitDim[2]) {	//si au moins 1 dimension peut être split

			//retourne une liste de chaque nouvelle region avec les nouvelles coordonnées et dimensions
			std::vector< std::pair< std::vector<unsigned int>, std::vector<unsigned int>>> vpvuiNewSpots;
			FRGMatrice.FRGGetNewSpots(vbSplitDim, vpvuiNewSpots);
			
			//Incrémentation de 1 pour ne faire qu'une seule sous-division
			CThreadInformation::TDIIncrementCurrentThreadCount();
			unsigned int uiValeurActuel = CThreadInformation::TDIGetCurrentThreadCount(); //Stockage locale

			//Pour tout les nouveaux fragments
			for (std::pair<std::vector<unsigned int>, std::vector<unsigned int>> pvuiNewSpot : vpvuiNewSpots) {

				//Récursivité sur ces fragments en créant de nouveau fragment
				CFragment FRGNewFragment(FRGMatrice.FRGGetMatrice(), pvuiNewSpot.first, pvuiNewSpot.second);

				//Si un thread est disponible dans le vecteur => gestion des threads à l'aide de la classe CThreadInformation
				if (uiValeurActuel <= CThreadInformation::TDIGetThreadLimit()) {

					OptimizationByThreads.emplace_back(&CSplitOperation::SOTSplitMatriceThreads, this, FRGNewFragment, CritereHomogeneite, uiSeuilMin, std::ref(vFRGVectorFinal), std::ref(OptimizationByThreads)); //Recursivité
				}
				else {

					SOTSplitMatriceThreads(FRGNewFragment, CritereHomogeneite, uiSeuilMin, vFRGVectorFinal, OptimizationByThreads); //Récursivité sans threads
				}
			}
		}
		else { //Si aucun dimension n'est divisible => fragment "feuille"
			FRGMatrice.FRGSetMinMax(FRGMatrice.FRGFindMinMax()); //Set le min / max du fragment "feuille"

			//Mutex pour l'écriture dans le vecteur
			SOTMutex.lock();
			vFRGVectorFinal.push_back(FRGMatrice); //ajoute le fragment "feuille" a la liste
			SOTMutex.unlock();
		}
	}
}