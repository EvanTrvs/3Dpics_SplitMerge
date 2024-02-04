#include "COperationsSurGraphes.h"

/************************************************************************************************************************************************
***** GetAllVoxels : Function for associate each element of the multi_array to a connexity													*****
*************************************************************************************************************************************************
***** Input : FRGVertices : CFragment | uiGroupe : const unsigned int | maVXLMatriceGroupe : boost::multi_array <unsigned int, 3> &   		*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Modification of the multi_array for associate each voxel to a connexity                                                     *****
************************************************************************************************************************************************/
void GetAllVoxels(CFragment FRGVertices, const unsigned int uiGroupe, boost::multi_array <unsigned int, 3> & maMatriceGroupe) {

	//storage of coos and dimensions of the fragment
	vector <unsigned int> vuiCoos = FRGVertices.FRGGetCoos();
	vector <unsigned int> vuiDim = FRGVertices.FRGGetDimensions();

	//Triple loop for visit all element 
	for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDim[0]; uiBoucleX++) {
		for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDim[1]; uiBoucleY++) {
			for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDim[2]; uiBoucleZ++) {

				maMatriceGroupe[uiBoucleX + vuiCoos[0]][uiBoucleY + vuiCoos[1]][uiBoucleZ + vuiCoos[2]] = uiGroupe;
			}
		}
	}
}

/************************************************************************************************************************************************
***** OSGGrapheToMatrice : Function convert graphe to multi_array																			*****
*************************************************************************************************************************************************
***** Input : alGraphe : BGLGrapheAffichage																									*****
***** Precondition : Nothing                                                                                                                *****
***** Output : maMatriceGroupe : boost::multi_array <unsigned int, 3>																		*****
***** Effects : Convert graphe to multi_array with connexity for each elements			                                                    *****
************************************************************************************************************************************************/
boost::multi_array <unsigned int, 3> COperationsSurGraphes::OSGGrapheToMatrice(BGLGrapheAffichage alGraphe) {

	//Exception Management = no vertices 
	if (boost::num_vertices(alGraphe) == 0) {
		CException EXCErreur;
		EXCErreur.EXCModifierValeur(GRAPHE_VIDE);
		throw EXCErreur;
	}

	//storage dimensions of the fragment
	vector <unsigned int> vuiDimensionsMatrice = alGraphe[0].FRGGetDimensionMatrice();
	
	//Creation of new multi_array
	typedef boost::multi_array <unsigned int, 3> multi_array_type;
	multi_array_type maMatriceGroupe(boost::extents[vuiDimensionsMatrice[0]][vuiDimensionsMatrice[1]][vuiDimensionsMatrice[2]]);

	//Deplacement in the graphe
	BGLGrapheAffichage::vertex_iterator vInit, vEnd;

	//For each vertices (fragment) of the graphe
	for (boost::tie(vInit, vEnd) = boost::vertices(alGraphe); vInit != vEnd; ++vInit) {

		//Fragment from the graphe
		CFragment FRGVertex = alGraphe[*vInit];

		//Modification of the multi_array
		GetAllVoxels(FRGVertex, FRGVertex.FRGGetConnexite(), maMatriceGroupe);
	}

	//Return new multi_array
	return maMatriceGroupe;
}