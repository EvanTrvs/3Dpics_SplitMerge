#pragma once 

#include "CThreadInformation.h"
#include "CSplitOperation.h"

/************************************************************************************************************************************************
***** SOTSPLITMATRICE : M�thode de Split Classique																							*****
*************************************************************************************************************************************************
***** Entr�e : FRGMatrice : CFragment & | CritereHomogeneite, uiSeuilMin : const unsigned int | vFRGVectorFinal : vector<CFragment> &		*****
***** N�cessite : La taille minimum des cubes ne peux �tre �gale � 0                                                                        *****
***** Sortie : Aucun �l�ment retourn�																										*****
***** Entraine : M�thode de Split selon les crit�res pass�s en param�tre																	*****
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

	//Si non null => Homog�ne
	if (puiHomoMinMax) {
		FRGMatrice.FRGSetMinMax(*puiHomoMinMax); //Set le min / max du fragment "feuille"
		delete puiHomoMinMax; 

		vFRGVectorFinal.push_back(FRGMatrice); //ajoute le fragment "feuille" a la liste
	}
	else {	
		//Calcul si le fragment non homog�ne est divisible
		std::vector<bool> vbSplitDim = FRGMatrice.FRGIsSplitable(uiSeuilMin);	//vector de 3 booleen, pour chaque dimension, true si peut split

		//si au moins 1 dimension peut �tre split
		if (vbSplitDim[0] || vbSplitDim[1] || vbSplitDim[2]) {

			//retourne une liste de chaque nouvelle region avec les nouvelles coordonn�es et dimensions
			std::vector< std::pair< std::vector<unsigned int>, std::vector<unsigned int>>> vpvuiNewSpots;
			FRGMatrice.FRGGetNewSpots(vbSplitDim, vpvuiNewSpots);

			//Pour tout les nouveaux fragments 
			for (std::pair<std::vector<unsigned int>, std::vector<unsigned int>> pvuiNewSpot : vpvuiNewSpots) {

				//R�cursivit� sur ces fragments en cr�ant de nouveau fragment
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
***** SOTSPLITMATRICETHREADS : M�thode de Split avec des Threads																														*****
*********************************************************************************************************************************************************************************************
***** Entr�e : FRGMatrice : CFragment & | CritereHomogeneite, uiSeuilMin : const unsigned int | vFRGVectorFinal : vector<CFragment> & | OptimizationByThreads : vector<std::thread> &	*****
***** N�cessite : La taille minimum des cubes ne peux �tre �gale � 0																													*****
***** Sortie : Aucun �l�ment retourn�																																					*****
***** Entraine : M�thode de Split avec des Threads selon les crit�res pass�s en param�tre																								*****
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

	//Si non null => Homog�ne
	if (puiHomoMinMax) {

		FRGMatrice.FRGSetMinMax(*puiHomoMinMax); //Set le min / max du fragment "feuille"
		delete puiHomoMinMax;

		//Mutex pour l'�criture dans le vecteur
		SOTMutex.lock();
		vFRGVectorFinal.push_back(FRGMatrice); //ajoute le fragment "feuille" a la liste
		SOTMutex.unlock();
	}
	else {	//Calcul si le fragment non homog�ne est divisible
		std::vector<bool> vbSplitDim = FRGMatrice.FRGIsSplitable(uiSeuilMin);	//vector de 3 booleen, pour chaque dimension, true si peut split

		//si au moins 1 dimension peut �tre split
		if (vbSplitDim[0] || vbSplitDim[1] || vbSplitDim[2]) {	//si au moins 1 dimension peut �tre split

			//retourne une liste de chaque nouvelle region avec les nouvelles coordonn�es et dimensions
			std::vector< std::pair< std::vector<unsigned int>, std::vector<unsigned int>>> vpvuiNewSpots;
			FRGMatrice.FRGGetNewSpots(vbSplitDim, vpvuiNewSpots);
			
			//Incr�mentation de 1 pour ne faire qu'une seule sous-division
			CThreadInformation::TDIIncrementCurrentThreadCount();
			unsigned int uiValeurActuel = CThreadInformation::TDIGetCurrentThreadCount(); //Stockage locale

			//Pour tout les nouveaux fragments
			for (std::pair<std::vector<unsigned int>, std::vector<unsigned int>> pvuiNewSpot : vpvuiNewSpots) {

				//R�cursivit� sur ces fragments en cr�ant de nouveau fragment
				CFragment FRGNewFragment(FRGMatrice.FRGGetMatrice(), pvuiNewSpot.first, pvuiNewSpot.second);

				//Si un thread est disponible dans le vecteur => gestion des threads � l'aide de la classe CThreadInformation
				if (uiValeurActuel <= CThreadInformation::TDIGetThreadLimit()) {

					OptimizationByThreads.emplace_back(&CSplitOperation::SOTSplitMatriceThreads, this, FRGNewFragment, CritereHomogeneite, uiSeuilMin, std::ref(vFRGVectorFinal), std::ref(OptimizationByThreads)); //Recursivit�
				}
				else {

					SOTSplitMatriceThreads(FRGNewFragment, CritereHomogeneite, uiSeuilMin, vFRGVectorFinal, OptimizationByThreads); //R�cursivit� sans threads
				}
			}
		}
		else { //Si aucun dimension n'est divisible => fragment "feuille"
			FRGMatrice.FRGSetMinMax(FRGMatrice.FRGFindMinMax()); //Set le min / max du fragment "feuille"

			//Mutex pour l'�criture dans le vecteur
			SOTMutex.lock();
			vFRGVectorFinal.push_back(FRGMatrice); //ajoute le fragment "feuille" a la liste
			SOTMutex.unlock();
		}
	}
}