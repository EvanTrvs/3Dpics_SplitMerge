#ifndef CGraphesCreator_h
#define CGraphesCreator_h

#pragma once

#include "CGrapheColore.h"

#include <vector>


class CGraphesCreator {
private:
	vector <CGrapheColore> vGPCGCRGraphes;

public:

	/************************************************************************************************************************************************
	***** CGRAPHESCREATOR : Constructeur par défaut de la classe CGraphesCreator																*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Initialise vGPCGCRGraphes à null																							*****
	************************************************************************************************************************************************/
	CGraphesCreator();

	/************************************************************************************************************************************************
	***** GCRGETGRAPHES : Accesseur en lecture de vGPCGCRGraphes																				*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : vGPCGCRGraphes : vector <CGraphesColore>																						*****
	***** Entraine : Retourne la variable vGPCGCRGraphes																						*****
	************************************************************************************************************************************************/
	vector <CGrapheColore> GCRGetGraphes();

	/************************************************************************************************************************************************
	***** GCRCREATIONGRAPHES : Méthode pour créer les différents graphes à partir des feuilles de l'arbre										*****
	*************************************************************************************************************************************************
	***** Entrée : vFRGLeafs : vector <CFragment> & uiHomogeneite : unsigned int 																*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Remplis la variable vGPCGCRGraphes																							*****
	************************************************************************************************************************************************/
	void GCRCreationGraphes(vector <CFragment> vFRGLeafs, unsigned int uiHomogeneite);
};

#endif
