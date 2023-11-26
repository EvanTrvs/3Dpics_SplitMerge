#include "COperationsSurGraphes.h"

/************************************************************************************************************************************************
***** OSGMERGEGRAPHE : Méthode fusionnant les graphes avec des correspondances																*****
*************************************************************************************************************************************************
***** Entrée : vGPCGraphes : vector <CGrapheColore>	& uiHomogeneite : unsigned int															*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : vGPCGraphes : vector <CGrapheColore>																							*****
***** Entraine : Fusionne les graphes avec des correspondances																				*****
************************************************************************************************************************************************/
vector <CGrapheColore> COperationsSurGraphes::OSGMergeGraphe(vector <CGrapheColore> vGPCGraphes, unsigned int uiHomogeneite) {

	vector <CGrapheColore> vGPCMergeGraphes = {};

	//Si 2 éléments sont communs
	//Si le mélange des couleurs respectent l'homogénéité définie -> déterministe = prendre le plus faible changement en premier

	vector <unsigned int> vuiAlreadyTest;

	while (vGPCGraphes.size() != 0) {

		unsigned int uiGray = std::numeric_limits<unsigned int>::max();
		bool ToMerge = false;
		unsigned int uiToMerge;
		CGrapheColore GPCComparaison = vGPCGraphes[0];

		for (unsigned int uiBoucle = 1; uiBoucle < vGPCGraphes.size(); uiBoucle++) {

			if (GPCComparaison.GPCGetGray().GSLUpperLimit(uiHomogeneite) > vGPCGraphes[uiBoucle].GPCGetGray().GSLGetGray() &&
				GPCComparaison.GPCGetGray().GSLLowerLimit(uiHomogeneite) < vGPCGraphes[uiBoucle].GPCGetGray().GSLGetGray()) {

				unsigned int uiMoyenne = static_cast<unsigned int> (round((double)GPCComparaison.GPCGetGray().GSLGetGray() + (double)vGPCGraphes[uiBoucle].GPCGetGray().GSLGetGray()) / 2);
				unsigned int uiEcart = abs((int)GPCComparaison.GPCGetGray().GSLGetGray() - (int)uiMoyenne);

				if ((uiEcart < uiGray) && (std::find (vuiAlreadyTest.begin(), vuiAlreadyTest.end(), uiBoucle) == std::end(vuiAlreadyTest))) {
					uiGray = uiEcart;
					uiToMerge = uiBoucle;
					ToMerge = true;
					break;
				}
			}
		}

		//doit être proche

		if (ToMerge) {
			//Merge

			if (GPCComparaison.GPCMergeGraphs(vGPCGraphes[uiToMerge])) {
				vGPCGraphes.erase(vGPCGraphes.begin() + uiToMerge);

				vGPCGraphes[0] = GPCComparaison; //Actualisation du graphe
			}
			else {
				vuiAlreadyTest.push_back(uiToMerge);
			}
		}
		else {
			vGPCMergeGraphes.push_back(GPCComparaison);
			vGPCGraphes.erase(vGPCGraphes.begin());
		}

		if (vGPCGraphes.size() == 1) {

			vGPCMergeGraphes.push_back(vGPCGraphes[0]);
			vGPCGraphes.erase(vGPCGraphes.begin());
		}
	}

	return vGPCMergeGraphes;
}

/************************************************************************************************************************************************
***** GETALLVOXELS : Méthode ajoutant à la matrice, les voxels avec leurs groupes															*****
*************************************************************************************************************************************************
***** Entrée : FRGVertices : CFragment | uiGroupe : unsigned int | maVXLMatriceGroupe : * boost::multi_array <CVoxel, 3>					*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné			                                                                                            *****
***** Entraine : Ajout à la matrice, les voxels avec leurs groupes																			*****
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
***** OSGGRAPHETOMATRICE : Méthode créant une matrice de Voxel ayant des informations de groupe												*****
*************************************************************************************************************************************************
***** Entrée : vGPCraphes : vector <CGrapheColore>																							*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : vFRGLeafs : vector <CFragment>                                                                                               *****
***** Entraine : Création d'une matrice de Voxel ayant des informations de groupe															*****
************************************************************************************************************************************************/
boost::multi_array <CVoxel, 3> COperationsSurGraphes::OSGGrapheToMatrice(vector <CGrapheColore> vGPCGraphes) {

	vector <unsigned int> vuiDimensionsMatrice = vGPCGraphes[0].GPCGetGraphe()[0].FRGGetDimensionMatrice();


	typedef boost::multi_array <CVoxel, 3> multi_array_type;
	multi_array_type maVXLMatriceGroupe(boost::extents[vuiDimensionsMatrice[0]][vuiDimensionsMatrice[1]][vuiDimensionsMatrice[2]]);

	unsigned int uiGroupe = 1;
	for (unsigned int uiBoucle = 0; uiBoucle < vGPCGraphes.size(); uiBoucle++) {
		vector <CFragment> vFRGVertices = vGPCGraphes[uiBoucle].GPCGetVertices();

		for (vector<CFragment>::iterator vIt = vFRGVertices.begin(); vIt != vFRGVertices.end(); ++vIt) {
			GetAllVoxels(*vIt, uiGroupe, &maVXLMatriceGroupe);
		}

		uiGroupe++;
	}

	return maVXLMatriceGroupe;
}