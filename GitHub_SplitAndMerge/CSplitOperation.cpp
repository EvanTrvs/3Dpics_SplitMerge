#pragma once 

#include "CSplitOperation.h"

/*****************************************************************************************************************************************************************
***** SOTSPLITMATRICE : Méthode Divisant une matrice en fonction d'un critère d'homogénéité													                 *****
******************************************************************************************************************************************************************
***** Entrée : FRGMatriceComplete : CFragment | uiCritereHomogeneite : unsigned int | uiTailleMinCube : unsigned int | vFRGVectorFinal : vector <CFragment>	 *****
***** Nécessite : Ne nécessite rien																															 *****
***** Sortie : vFRGLeafs : vector <CFragment>																											     *****
***** Entraine : Divise une matrice en fonction d'un critère d'homogénéité																					 *****
*****************************************************************************************************************************************************************/
vector <CFragment> CSplitOperation::SOTSplitMatrice(CFragment FRGMatrice, unsigned int uiCritereHomogeneite, unsigned int uiTailleMinCube, vector <CFragment> vFRGVectorFinal) {

	unsigned int uiVolumeCube = FRGMatrice.FRGGetDimensions()[0] * FRGMatrice.FRGGetDimensions()[1] * FRGMatrice.FRGGetDimensions()[2];
	if ((!FRGMatrice.FRGHomogeneity(uiCritereHomogeneite)) && (uiVolumeCube >= uiTailleMinCube * uiTailleMinCube*uiTailleMinCube)) {

		cout << "taille : " << uiVolumeCube << endl;
		unsigned int uiDimX = static_cast<unsigned int> (round((double)FRGMatrice.FRGGetDimensions()[0] / 2)); //Coos X milieu
		unsigned int uiDimY = static_cast<unsigned int> (round((double)FRGMatrice.FRGGetDimensions()[1] / 2)); //Coos Y milieu
		unsigned int uiDimZ = static_cast<unsigned int> (round((double)FRGMatrice.FRGGetDimensions()[2] / 2)); //Coos Z milieu

		unsigned int uiDimX2 = FRGMatrice.FRGGetDimensions()[0] - uiDimX; //Dim Pour Coos X Milieu
		unsigned int uiDimY2 = FRGMatrice.FRGGetDimensions()[1] - uiDimY; //Dim Pour Coos Y Milieu
		unsigned int uiDimZ2 = FRGMatrice.FRGGetDimensions()[2] - uiDimZ; //Dim Pour Coos Z Milieu

		CFragment FRGNewFragmentNWF(FRGMatrice.FRGGetMatrice(), FRGMatrice.FRGGetCoos(), { uiDimX , uiDimY, uiDimZ }); //Fragment positionner au Nord + West + Front 
		vFRGVectorFinal = SOTSplitMatrice(FRGNewFragmentNWF, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal); //Recursivité

		if ((FRGMatrice.FRGGetDimensions()[2] != 1)) {
			CFragment FRGNewFragmentNWB(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0], FRGMatrice.FRGGetCoos()[1], FRGMatrice.FRGGetCoos()[2] + uiDimZ }, { uiDimX , uiDimY, uiDimZ2 }); //Fragment positionner au Nord + West + Behind 
			vFRGVectorFinal = SOTSplitMatrice(FRGNewFragmentNWB, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal); //Recursivité
		}

		if ((FRGMatrice.FRGGetDimensions()[0] != 1)) {
			CFragment FRGNewFragmentNEF(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0] + uiDimX, FRGMatrice.FRGGetCoos()[1], FRGMatrice.FRGGetCoos()[2] }, { uiDimX2 , uiDimY, uiDimZ }); //Fragment positionner au Nord + East + Front 
			vFRGVectorFinal = SOTSplitMatrice(FRGNewFragmentNEF, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal); //Recursivité
		}

		if ((FRGMatrice.FRGGetDimensions()[0] != 1) && (FRGMatrice.FRGGetDimensions()[2] != 1)) {
			CFragment FRGNewFragmentNEB(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0] + uiDimX, FRGMatrice.FRGGetCoos()[1], FRGMatrice.FRGGetCoos()[2] + uiDimZ }, { uiDimX2 , uiDimY, uiDimZ2 }); //Fragment positionner au Nord + East + Behind 
			vFRGVectorFinal = SOTSplitMatrice(FRGNewFragmentNEB, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal); //Recursivité
		}

		if ((FRGMatrice.FRGGetDimensions()[1] != 1)) {
			CFragment FRGNewFragmentSWF(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0], FRGMatrice.FRGGetCoos()[1] + uiDimY, FRGMatrice.FRGGetCoos()[2] }, { uiDimX , uiDimY2, uiDimZ }); //Fragment positionner au South + West + Front 
			vFRGVectorFinal = SOTSplitMatrice(FRGNewFragmentSWF, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal); //Recursivité
		}

		if ((FRGMatrice.FRGGetDimensions()[1] != 1) && (FRGMatrice.FRGGetDimensions()[2] != 1)) {
			CFragment FRGNewFragmentSWB(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0], FRGMatrice.FRGGetCoos()[1] + uiDimY, FRGMatrice.FRGGetCoos()[2] + uiDimZ }, { uiDimX , uiDimY2, uiDimZ2 }); //Fragment positionner au South + West + Behind 
			vFRGVectorFinal = SOTSplitMatrice(FRGNewFragmentSWB, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal); //Recursivité
		}

		if ((FRGMatrice.FRGGetDimensions()[0] != 1) && (FRGMatrice.FRGGetDimensions()[1] != 1)) {
			CFragment FRGNewFragmentSEF(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0] + uiDimX, FRGMatrice.FRGGetCoos()[1] + uiDimY, FRGMatrice.FRGGetCoos()[2] }, { uiDimX2 , uiDimY2, uiDimZ }); //Fragment positionner au South + East + Front 
			vFRGVectorFinal = SOTSplitMatrice(FRGNewFragmentSEF, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal); //Recursivité
		}

		if ((FRGMatrice.FRGGetDimensions()[0] != 1) && (FRGMatrice.FRGGetDimensions()[1] != 1) && (FRGMatrice.FRGGetDimensions()[2] != 1)) {
			CFragment FRGNewFragmentSEB(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0] + uiDimX, FRGMatrice.FRGGetCoos()[1] + uiDimY, FRGMatrice.FRGGetCoos()[2] + uiDimZ }, { uiDimX2 , uiDimY2, uiDimZ2 }); //Fragment positionner au South + East + Behind 
			vFRGVectorFinal = SOTSplitMatrice(FRGNewFragmentSEB, uiCritereHomogeneite, uiTailleMinCube, vFRGVectorFinal); //Recursivité
		}
	}
	else {
		vFRGVectorFinal.push_back(FRGMatrice);
	}

	return vFRGVectorFinal;
}