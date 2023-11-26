#ifndef CGrapheColore_h
#define CGrapheColore_h

#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <math.h>
#include <algorithm>

#include "CGrayScale.h"
#include "CFragment.h"

enum Direction {
	North_South, //0
	South_North, //1
	West_East, //2
	East_West, //3
	Behind_Front, //4
	Front_Behind //5
};

struct Propreties_Edges {
	Direction direction;
	unsigned int value_use = 0;
	//unsigned int value_max = Dimension
};

typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::directedS, CFragment, Propreties_Edges> BGLGraphe;

class CGrapheColore {
private:
	vector <unsigned int> vuiColors;
	CGrayScale GSLGPCGray;

	BGLGraphe alGPCGraphe;

public:
	/************************************************************************************************************************************************
	***** CGRAPHECOLORE : Constructeur par d�faut de la classe CGrapheColore																	*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Initialise uiGSLGray � null et cr�e un nouveau graphe vide																	*****
	************************************************************************************************************************************************/
	CGrapheColore();

	/************************************************************************************************************************************************
	***** CGRAPHECOLORE : Constructeur de confort de la classe CGrapheColore																	*****
	*************************************************************************************************************************************************
	***** Entr�e : CFragment : FRGFragment																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Initialise un nouveau graphe avec un sommet																				*****
	************************************************************************************************************************************************/
	CGrapheColore(CFragment FRGFragment);

	/************************************************************************************************************************************************
	***** GPCGETGRAPHE : Accesseur en lecture de la variable alGPCGraphe																		*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : alGPCGraphe : boost::adjacency_list <boost::vecS, boost::vecS, boost::directedS, CFragment, Propreties_Edges>				*****
	***** Entraine : Returne le graphe alGPCGraphe																								*****
	************************************************************************************************************************************************/
	boost::adjacency_list <boost::vecS, boost::vecS, boost::directedS, CFragment, Propreties_Edges> GPCGetGraphe();

	/************************************************************************************************************************************************
	***** GPCGETVERTICES : Accesseur en lecture de la variable alGPCGraphe																		*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : vector <CFragment> vFRGVertices																								*****
	***** Entraine : Returne les vertices du graphe alGPCGraphe																					*****
	************************************************************************************************************************************************/
	vector <CFragment> GPCGetVertices();

	/************************************************************************************************************************************************
	***** GPCGETGRAY : Accesseur en lecture de la variable GSLGPCGray																			*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : GSLGPCGray : CGrayScale																										*****
	***** Entraine : Retourne l'objet GSLGPCGray																								*****
	************************************************************************************************************************************************/
	CGrayScale GPCGetGray();

	/************************************************************************************************************************************************
	***** GPCSETGRAY : Accesseur en �criture de la variable GSLGPCGray																			*****
	*************************************************************************************************************************************************
	***** Entr�e : GSLGray : CGrayScale																											*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Modifie l'objet GSLGPCGray																									*****
	************************************************************************************************************************************************/
	void GPCSetGray(CGrayScale GSLGray);

private:
	/************************************************************************************************************************************************
	***** GPCVERTICEONBORDER : M�thode ajoutant des arcs sur les sommets aux bords de la matrice												*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun param�tre d'entr�																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : uiNb_Edges : unsigned int																									*****
	***** Entraine : Ajoute des arcs dans les directions hors matrice																			*****
	************************************************************************************************************************************************/
	unsigned int GPCVerticeOnBorder();

public:
	/************************************************************************************************************************************************
	***** GPCADDTOGRAPH : Accesseur en �criture de la variable alGPCGraphe																		*****
	*************************************************************************************************************************************************
	***** Entr�e : FRGFragment : CFragment																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : bGoodADD : boolean																											*****
	***** Entraine : Ajoute un nouveau sommet dans le graphe																					*****
	************************************************************************************************************************************************/
	bool GPCAddToGraph(CFragment FRGFragment);

	/************************************************************************************************************************************************
	***** GPCMERGEVERTICE : Accesseur en �criture de la variable alGPCGraphe																	*****
	*************************************************************************************************************************************************
	***** Entr�e : alGrapheToMerge : BGLGraphe & vdVertices : BGLGraphe::vertex_descriptor & vFRGAddInComing : vector <CFragment> * 			*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Ajoute un sommet au graphe avec ses arcs																					*****
	************************************************************************************************************************************************/
	BGLGraphe::vertex_descriptor GPCMergeVertice(BGLGraphe alGrapheToMerge, BGLGraphe::vertex_descriptor vdVertice, vector <CFragment> * vFRGAddInComing);

	/************************************************************************************************************************************************
	***** GPCMERGEGRAPHS : Accesseur en �criture de la variable alGPCGraphe																		*****
	*************************************************************************************************************************************************
	***** Entr�e : GPCGraphe : CGrapheColore																									*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : bVerif : boolean																												*****
	***** Entraine : Fusionne 2 graphes entre eux																								*****
	************************************************************************************************************************************************/
	bool GPCMergeGraphs(CGrapheColore GPCGraphe);
};

#endif