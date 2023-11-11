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
	***** CGRAPHECOLORE : Constructeur par défaut de la classe CGrapheColore																	*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Initialise uiGSLGray à null et crée un nouveau graphe vide																	*****
	************************************************************************************************************************************************/
	CGrapheColore();

	/************************************************************************************************************************************************
	***** CGRAPHECOLORE : Constructeur de confort de la classe CGrapheColore																	*****
	*************************************************************************************************************************************************
	***** Entrée : CFragment : FRGFragment																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Initialise un nouveau graphe avec un sommet																				*****
	************************************************************************************************************************************************/
	CGrapheColore(CFragment FRGFragment);

	/************************************************************************************************************************************************
	***** GPCGETGRAPHE : Accesseur en lecture de la variable alGPCGraphe																		*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : alGPCGraphe : boost::adjacency_list <boost::vecS, boost::vecS, boost::directedS, CFragment, Propreties_Edges>				*****
	***** Entraine : Returne le graphe alGPCGraphe																								*****
	************************************************************************************************************************************************/
	boost::adjacency_list <boost::vecS, boost::vecS, boost::directedS, CFragment, Propreties_Edges> GPCGetGraphe();

	/************************************************************************************************************************************************
	***** GPCGETVERTICES : Accesseur en lecture de la variable alGPCGraphe																		*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : vector <CFragment> vFRGVertices																								*****
	***** Entraine : Returne les vertices du graphe alGPCGraphe																					*****
	************************************************************************************************************************************************/
	vector <CFragment> GPCGetVertices();

	/************************************************************************************************************************************************
	***** GPCGETGRAY : Accesseur en lecture de la variable GSLGPCGray																			*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : GSLGPCGray : CGrayScale																										*****
	***** Entraine : Retourne l'objet GSLGPCGray																								*****
	************************************************************************************************************************************************/
	CGrayScale GPCGetGray();

	/************************************************************************************************************************************************
	***** GPCSETGRAY : Accesseur en écriture de la variable GSLGPCGray																			*****
	*************************************************************************************************************************************************
	***** Entrée : GSLGray : CGrayScale																											*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Modifie l'objet GSLGPCGray																									*****
	************************************************************************************************************************************************/
	void GPCSetGray(CGrayScale GSLGray);

private:
	/************************************************************************************************************************************************
	***** GPCVERTICEONBORDER : Méthode ajoutant des arcs sur les sommets aux bords de la matrice												*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun paramètre d'entré																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : uiNb_Edges : unsigned int																									*****
	***** Entraine : Ajoute des arcs dans les directions hors matrice																			*****
	************************************************************************************************************************************************/
	unsigned int GPCVerticeOnBorder();

public:
	/************************************************************************************************************************************************
	***** GPCADDTOGRAPH : Accesseur en écriture de la variable alGPCGraphe																		*****
	*************************************************************************************************************************************************
	***** Entrée : FRGFragment : CFragment																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : bGoodADD : boolean																											*****
	***** Entraine : Ajoute un nouveau sommet dans le graphe																					*****
	************************************************************************************************************************************************/
	bool GPCAddToGraph(CFragment FRGFragment);

	/************************************************************************************************************************************************
	***** GPCMERGEVERTICE : Accesseur en écriture de la variable alGPCGraphe																	*****
	*************************************************************************************************************************************************
	***** Entrée : alGrapheToMerge : BGLGraphe & vdVertices : BGLGraphe::vertex_descriptor & vFRGAddInComing : vector <CFragment> * 			*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Ajoute un sommet au graphe avec ses arcs																					*****
	************************************************************************************************************************************************/
	BGLGraphe::vertex_descriptor GPCMergeVertice(BGLGraphe alGrapheToMerge, BGLGraphe::vertex_descriptor vdVertice, vector <CFragment> * vFRGAddInComing);

	/************************************************************************************************************************************************
	***** GPCMERGEGRAPHS : Accesseur en écriture de la variable alGPCGraphe																		*****
	*************************************************************************************************************************************************
	***** Entrée : GPCGraphe : CGrapheColore																									*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : bVerif : boolean																												*****
	***** Entraine : Fusionne 2 graphes entre eux																								*****
	************************************************************************************************************************************************/
	bool GPCMergeGraphs(CGrapheColore GPCGraphe);
};

#endif