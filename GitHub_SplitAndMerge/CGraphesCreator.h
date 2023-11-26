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
	***** CGRAPHESCREATOR : Constructeur par d�faut de la classe CGraphesCreator																*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Initialise vGPCGCRGraphes � null																							*****
	************************************************************************************************************************************************/
	CGraphesCreator();

	/************************************************************************************************************************************************
	***** GCRGETGRAPHES : Accesseur en lecture de vGPCGCRGraphes																				*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : vGPCGCRGraphes : vector <CGraphesColore>																						*****
	***** Entraine : Retourne la variable vGPCGCRGraphes																						*****
	************************************************************************************************************************************************/
	vector <CGrapheColore> GCRGetGraphes();

	/************************************************************************************************************************************************
	***** GCRCREATIONGRAPHES : M�thode pour cr�er les diff�rents graphes � partir des feuilles de l'arbre										*****
	*************************************************************************************************************************************************
	***** Entr�e : vFRGLeafs : vector <CFragment> & uiHomogeneite : unsigned int 																*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Remplis la variable vGPCGCRGraphes																							*****
	************************************************************************************************************************************************/
	void GCRCreationGraphes(vector <CFragment> vFRGLeafs, unsigned int uiHomogeneite);
};

#endif
