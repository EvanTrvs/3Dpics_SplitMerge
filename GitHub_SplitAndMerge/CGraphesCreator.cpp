#pragma once

#include "CGraphesCreator.h"

/************************************************************************************************************************************************
***** CGRAPHESCREATOR : Constructeur par défaut de la classe CGraphesCreator																*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné																										*****
***** Entraine : Initialise vGPCGCRGraphes à null																							*****
************************************************************************************************************************************************/
CGraphesCreator::CGraphesCreator() {
	vGPCGCRGraphes = {};
}

/************************************************************************************************************************************************
***** GCRGETGRAPHES : Accesseur en lecture de vGPCGCRGraphes																				*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : vGPCGCRGraphes : vector <CGraphesColore>																						*****
***** Entraine : Retourne la variable vGPCGCRGraphes																						*****
************************************************************************************************************************************************/
vector <CGrapheColore> CGraphesCreator::GCRGetGraphes() {
	return vGPCGCRGraphes;
}

/************************************************************************************************************************************************
***** GCRCREATIONGRAPHES : Méthode pour créer les différents graphes à partir des feuilles de l'arbre										*****
*************************************************************************************************************************************************
***** Entrée : vFRGLeafs : vector <CFragment>																								*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné																										*****
***** Entraine : Remplis la variable vGPCGCRGraphes																							*****
************************************************************************************************************************************************/
void CGraphesCreator::GCRCreationGraphes(vector <CFragment> vFRGLeafs, unsigned int uiHomogeneite) {

	//Vector de Vector (vector de color) pour simplifier la fusion ??

	vGPCGCRGraphes.push_back(CGrapheColore (vFRGLeafs[0]));

	for (unsigned int uiBoucleF = 1; uiBoucleF < vFRGLeafs.size(); uiBoucleF++) { //Test de parcourir le vector

		unsigned int ToADD = 0;

		for (unsigned int uiBoucleG = 0; uiBoucleG < vGPCGCRGraphes.size(); uiBoucleG++) {
			if (vFRGLeafs[uiBoucleF].FRGDominantColor().GSLUpperLimit(uiHomogeneite) < vGPCGCRGraphes[uiBoucleG].GPCGetGray().GSLGetGray() ||
				vFRGLeafs[uiBoucleF].FRGDominantColor().GSLLowerLimit(uiHomogeneite) > vGPCGCRGraphes[uiBoucleG].GPCGetGray().GSLGetGray()) {

				//Creation future d'un nouveau graphe
				ToADD += 1;
			}
			else {
				//Si le sommet ajouté n'est pas adjacent au reste (graphe)
				if (!vGPCGCRGraphes[uiBoucleG].GPCAddToGraph(vFRGLeafs[uiBoucleF])) {
					ToADD += 1;
				}
			}
		}

		if (ToADD == vGPCGCRGraphes.size()) {
			//Creation nouveau graphe
			vGPCGCRGraphes.push_back(CGrapheColore(vFRGLeafs[uiBoucleF]));
		}
	}
}