#pragma once 

#include "CSplitOperation.h"

/************************************************************************************************************************************************
***** SOTSPLITMATRICE : M�thode Divisant une matrice en fonction d'un crit�re d'homog�n�it�													*****
*************************************************************************************************************************************************
***** Entr�e : FRGMatriceComplete : CFragment | CritereHomogeneite : unsigned int | vFRGVectorFinal : vector <CFragment>				    *****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : vFRGLeafs : vector <CFragment>                                                                                               *****
***** Entraine : Divise une matrice en fonction d'un crit�re d'homog�n�it�																	*****
************************************************************************************************************************************************/
vector <CFragment> CSplitOperation::SOTSplitMatrice(CFragment FRGMatrice, unsigned int CritereHomogeneite, vector <CFragment> vFRGVectorFinal) {

	if (!FRGMatrice.FRGHomogeneity(CritereHomogeneite)) {
		unsigned int uiDimX = static_cast<unsigned int> (round((double)FRGMatrice.FRGGetDimensions()[0] / 2)); //Coos X milieu
		unsigned int uiDimY = static_cast<unsigned int> (round((double)FRGMatrice.FRGGetDimensions()[1] / 2)); //Coos Y milieu
		unsigned int uiDimZ = static_cast<unsigned int> (round((double)FRGMatrice.FRGGetDimensions()[2] / 2)); //Coos Z milieu

		unsigned int uiDimX2 = FRGMatrice.FRGGetDimensions()[0] - uiDimX; //Dim Pour Coos X Milieu
		unsigned int uiDimY2 = FRGMatrice.FRGGetDimensions()[1] - uiDimY; //Dim Pour Coos Y Milieu
		unsigned int uiDimZ2 = FRGMatrice.FRGGetDimensions()[2] - uiDimZ; //Dim Pour Coos Z Milieu

		CFragment FRGNewFragmentNWF(FRGMatrice.FRGGetMatrice(), FRGMatrice.FRGGetCoos(), { uiDimX , uiDimY, uiDimZ }); //Fragment positionner au Nord + West + Front 
		vFRGVectorFinal = SOTSplitMatrice(FRGNewFragmentNWF, CritereHomogeneite, vFRGVectorFinal); //Recursivit�

		CFragment FRGNewFragmentNWB(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0], FRGMatrice.FRGGetCoos()[1], FRGMatrice.FRGGetCoos()[2] + uiDimZ }, { uiDimX , uiDimY, uiDimZ2 }); //Fragment positionner au Nord + West + Behind 
		vFRGVectorFinal = SOTSplitMatrice(FRGNewFragmentNWB, CritereHomogeneite, vFRGVectorFinal); //Recursivit�

		CFragment FRGNewFragmentNEF(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0] + uiDimX, FRGMatrice.FRGGetCoos()[1], FRGMatrice.FRGGetCoos()[2] }, { uiDimX2 , uiDimY, uiDimZ }); //Fragment positionner au Nord + East + Front 
		vFRGVectorFinal = SOTSplitMatrice(FRGNewFragmentNEF, CritereHomogeneite, vFRGVectorFinal); //Recursivit�

		CFragment FRGNewFragmentNEB(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0] + uiDimX, FRGMatrice.FRGGetCoos()[1], FRGMatrice.FRGGetCoos()[2] + uiDimZ }, { uiDimX2 , uiDimY, uiDimZ2 }); //Fragment positionner au Nord + East + Behind 
		vFRGVectorFinal = SOTSplitMatrice(FRGNewFragmentNEB, CritereHomogeneite, vFRGVectorFinal); //Recursivit�

		CFragment FRGNewFragmentSWF(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0], FRGMatrice.FRGGetCoos()[1] + uiDimY, FRGMatrice.FRGGetCoos()[2] }, { uiDimX , uiDimY2, uiDimZ }); //Fragment positionner au South + West + Front 
		vFRGVectorFinal = SOTSplitMatrice(FRGNewFragmentSWF, CritereHomogeneite, vFRGVectorFinal); //Recursivit�

		CFragment FRGNewFragmentSWB(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0], FRGMatrice.FRGGetCoos()[1] + uiDimY, FRGMatrice.FRGGetCoos()[2] + uiDimZ }, { uiDimX , uiDimY2, uiDimZ2 }); //Fragment positionner au South + West + Behind 
		vFRGVectorFinal = SOTSplitMatrice(FRGNewFragmentSWB, CritereHomogeneite, vFRGVectorFinal); //Recursivit�

		CFragment FRGNewFragmentSEF(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0] + uiDimX, FRGMatrice.FRGGetCoos()[1] + uiDimY, FRGMatrice.FRGGetCoos()[2] }, { uiDimX2 , uiDimY2, uiDimZ }); //Fragment positionner au South + East + Front 
		vFRGVectorFinal = SOTSplitMatrice(FRGNewFragmentSEF, CritereHomogeneite, vFRGVectorFinal); //Recursivit�

		CFragment FRGNewFragmentSEB(FRGMatrice.FRGGetMatrice(), { FRGMatrice.FRGGetCoos()[0] + uiDimX, FRGMatrice.FRGGetCoos()[1] + uiDimY, FRGMatrice.FRGGetCoos()[2] + uiDimZ }, { uiDimX2 , uiDimY2, uiDimZ2 }); //Fragment positionner au South + East + Behind 
		vFRGVectorFinal = SOTSplitMatrice(FRGNewFragmentSEB, CritereHomogeneite, vFRGVectorFinal); //Recursivit�
	}
	else {
		vFRGVectorFinal.push_back(FRGMatrice);
	}

	return vFRGVectorFinal;
}