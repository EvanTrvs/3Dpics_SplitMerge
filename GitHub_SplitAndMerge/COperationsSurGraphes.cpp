#include "COperationsSurGraphes.h"

/************************************************************************************************************************************************
***** OSGMERGEGRAPHE : M�thode fusionnant les graphes avec des correspondances																*****
*************************************************************************************************************************************************
***** Entr�e : vGPCGraphes : vector <CGrapheColore>	& uiHomogeneite : unsigned int															*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : vGPCGraphes : vector <CGrapheColore>																							*****
***** Entraine : Fusionne les graphes avec des correspondances																				*****
************************************************************************************************************************************************/
vector <CGrapheColore> COperationsSurGraphes::OSGMergeGraphe(vector <CGrapheColore> vGPCGraphes, unsigned int uiHomogeneite) {

	cout << "FUSION !!" << endl;
	vector <CGrapheColore> vGPCMergeGraphes = {};

	//Si 2 �l�ments sont communs
	//Si le m�lange des couleurs respectent l'homog�n�it� d�finie -> d�terministe = prendre le plus faible changement en premier

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

		//doit �tre proche

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