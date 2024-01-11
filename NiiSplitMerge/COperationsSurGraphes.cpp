#include "COperationsSurGraphes.h"



/************************************************************************************************************************************************
***** GETALLVOXELS : M�thode ajoutant � la matrice, les voxels avec leurs groupes															*****
*************************************************************************************************************************************************
***** Entr�e : FRGVertices : CFragment | uiGroupe : unsigned int | maVXLMatriceGroupe : * boost::multi_array <CVoxel, 3>					*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : Aucun �l�ment retourn�			                                                                                            *****
***** Entraine : Ajout � la matrice, les voxels avec leurs groupes																			*****
************************************************************************************************************************************************/
void GetAllVoxels(CFragment FRGVertices, unsigned int uiGroupe, boost::multi_array <CVoxel, 3> * maVXLMatriceGroupe) {
	vector <unsigned int> vuiCoos = FRGVertices.FRGGetCoos();
	vector <unsigned int> vuiDim = FRGVertices.FRGGetDimensions();

	for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDim[0]; uiBoucleX++) {
		for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDim[1]; uiBoucleY++) {
			for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDim[2]; uiBoucleZ++) {

				CVoxel VXLVoxel = CVoxel({ uiBoucleX + vuiCoos[0], uiBoucleY + vuiCoos[1], uiBoucleZ + vuiCoos[2] }, uiGroupe);
				maVXLMatriceGroupe[0][uiBoucleX + vuiCoos[0]][uiBoucleY + vuiCoos[1]][uiBoucleZ + vuiCoos[2]] = VXLVoxel;
			}
		}
	}
}

/************************************************************************************************************************************************
***** GETALLVOXELS : M�thode ajoutant � la matrice, les groupes aux coordonn�e des voxels													*****
*************************************************************************************************************************************************
***** Entr�e : FRGVertices : CFragment | uiGroupe : unsigned int | maVXLMatriceGroupe : * boost::multi_array <CVoxel, 3>					*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : Aucun �l�ment retourn�			                                                                                            *****
***** Entraine : Modifie la matrice pour avoir les groupes � chaque coordon�e de voxel														*****
************************************************************************************************************************************************/
void GetAllVoxelsV2(CFragment FRGVertices, unsigned int uiGroupe, boost::multi_array <unsigned int, 3> & maMatriceGroupe) {
	vector <unsigned int> vuiCoos = FRGVertices.FRGGetCoos();
	vector <unsigned int> vuiDim = FRGVertices.FRGGetDimensions();

	for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDim[0]; uiBoucleX++) {
		for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDim[1]; uiBoucleY++) {
			for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDim[2]; uiBoucleZ++) {

				maMatriceGroupe[uiBoucleX + vuiCoos[0]][uiBoucleY + vuiCoos[1]][uiBoucleZ + vuiCoos[2]] = uiGroupe;
			}
		}
	}
}

/************************************************************************************************************************************************
***** OSGGRAPHETOMATRICE : M�thode transformant un graphe de fragment en matrice															*****
*************************************************************************************************************************************************
***** Entr�e : alGraphe : BGLGrapheAffichage																								*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : maMatriceGroupe : boost::multi_array <unsigned int, 3>													                    *****
***** Entraine : Transforme un graphe en matrice avec comme �l�ment les groupes de chaque voxels											*****
************************************************************************************************************************************************/
boost::multi_array <unsigned int, 3> COperationsSurGraphes::OSGGrapheToMatrice(BGLGrapheAffichage alGraphe) {

	//Gestion de l'exception : Graphe vide
	if (boost::num_vertices(alGraphe) == 0) {
		CException EXCErreur;
		EXCErreur.EXCModifierValeur(GRAPHE_VIDE);
		throw EXCErreur;
	}

	//R�cup�ration des dimensions de la matrice
	vector <unsigned int> vuiDimensionsMatrice = alGraphe[0].FRGGetDimensionMatrice();
	
	//Cr�ation de la nouvelle matrice
	typedef boost::multi_array <unsigned int, 3> multi_array_type;
	multi_array_type maMatriceGroupe(boost::extents[vuiDimensionsMatrice[0]][vuiDimensionsMatrice[1]][vuiDimensionsMatrice[2]]);

	BGLGrapheAffichage::vertex_iterator vInit, vEnd;

	//Pour tous les sommets (frgaments) du graphe
	for (boost::tie(vInit, vEnd) = boost::vertices(alGraphe); vInit != vEnd; ++vInit) {

		//Modification de la matrice
		CFragment FRGVertex = alGraphe[*vInit];

		GetAllVoxelsV2(FRGVertex, FRGVertex.FRGGetConnexite(), maMatriceGroupe);
	}

	//Retourne la nouvelle matrice modifi�e
	return maMatriceGroupe;
}