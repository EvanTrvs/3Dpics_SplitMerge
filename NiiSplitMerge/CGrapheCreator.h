#ifndef CGrapheCreator_h
#define CGrapheCreator_h

#pragma once

#include <vector>
#include <thread>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/connected_components.hpp>

#include <math.h>
#include <limits>
#include <cmath>
#include <algorithm>
#include <mutex>

#include "CFragment.h"

#define SEUIL_MIN 2
#define UNDIFIED_VERSION 4
#define NO_LEAFS 5

typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS, CFragment> BGLGraphe;

class CGrapheCreator {
private:
	BGLGraphe alGPCGraphe;
	vector <BGLGraphe::vertex_descriptor> vvdGPCVertex_Desc;
	vector <vector <unsigned int>> vvuiGPCConnexite;

	vector <std::pair<unsigned int, unsigned int>> vpuiGPCVoisinPrimal;

	std::mutex GPCMutex;

public:

	/************************************************************************************************************************************************
	***** CGRAPHESCREATOR : Constructeur par défaut de la classe CGraphesCreator																*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Initialise alGPCGraphe à null																								*****
	************************************************************************************************************************************************/
	CGrapheCreator();

	/************************************************************************************************************************************************
	***** GCRGETGRAPHE : Accesseur en lecture de alGPCGraphe																					*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																										*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : GPCGCRGraphe : CGrapheColore																									*****
	***** Entraine : Retourne la variable alGPCGraphe																							*****
	************************************************************************************************************************************************/
	BGLGraphe GCRGetGraphe();

	/************************************************************************************************************************************************
	***** GCRCREATIONGRAPHE : Méthode pour créer le graphe à partir des feuilles de l'arbre														*****
	*************************************************************************************************************************************************
	***** Entrée : vFRGLeafs : vector <CFragment> | uiHomogeneite : unsigned int 																*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Complète le graphe de GPCGCRGraphe 																						*****
	************************************************************************************************************************************************/
	void GCRCreationGraphe(vector <CFragment> vFRGLeafs, unsigned int uiHomogeneite, unsigned int uiTailleMin, unsigned int uiVersion);

private:
	/************************************************************************************************************************************************
	***** GCRLINKVERTICES : Méthode liant 2 fragments du graphe																					*****
	*************************************************************************************************************************************************
	***** Entrée : puiPair : std::pair<unsigned int, unsigned int>																				*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Relie les Sommets en modifiant si besoin la connexité																		*****
	************************************************************************************************************************************************/
	void GCRLinkVertices(std::pair<unsigned int, unsigned int> puiPair);

	/************************************************************************************************************************************************
	***** GCRTHREADREDEF : Méthode appelé par un thread																							*****
	*************************************************************************************************************************************************
	***** Entrée : uiConnexite1, uiConnexite2 : unsigned int | puiMinMax : std::pair <unsigned int, unsigned int> 								*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Modifie le Min/Max des sommets présent dans la second connexité															*****
	************************************************************************************************************************************************/
	void GCRThreadRedef(unsigned int uiConnexite1, unsigned int uiConnexite2, std::pair <unsigned int, unsigned int> puiMinMax);

	/************************************************************************************************************************************************
	***** GCRVERTICEONBORDER : Méthode déterminant la présence d'un fragment au bord de la matrice												*****
	*************************************************************************************************************************************************
	***** Entrée : vdVertice : BGLGraphe::vertex_descriptor																						*****
	***** Nécessite : Doit exister dans le graphe                                                                                               *****
	***** Sortie : vbDirection : vector <bool>																									*****
	***** Entraine : Détermine la présence d'un fragment au bord de la matrice																	*****
	************************************************************************************************************************************************/
	vector <bool> GCRVerticesOnBorder(BGLGraphe::vertex_descriptor vdVertices);

	/************************************************************************************************************************************************************************
	***** GCRDETECTIONVOISINVOXEL : Méthode déterminant la liste des voisins à l'aide des voxels																		*****
	*************************************************************************************************************************************************************************
	***** Entrée : vFRGLeafs : vector <CFragment> | uiTailleMin : unsigned int																							*****
	***** Nécessite : Ne nécessite rien																																	*****
	***** Sortie : Aucun élément retourné																																*****
	***** Entraine : Détermine les voisins à partir de la liste des feuilles du Split																					*****
	************************************************************************************************************************************************************************/
	void GCRDetectionVoisinVoxel(vector <CFragment> vFRGLeafs, unsigned int uiTailleMin);

	/************************************************************************************************************************************************************************
	***** GCRDETECTIONVOISINV2DICHO : Méthode déterminant la liste des voisins en utilisant des vecteurs de vecteur et une dichotomie									*****
	*************************************************************************************************************************************************************************
	***** Entrée : vFRGLeafs : vector <CFragment> | uiTailleMin : unsigned int																							*****
	***** Nécessite : Ne nécessite rien																																	*****
	***** Sortie : Aucun élément retourné																																*****
	***** Entraine : Détermine les voisins à partir de la liste des feuilles du Split																					*****
	************************************************************************************************************************************************************************/
	void GCRDetectionVoisinV2Dicho(vector <CFragment> vFRGLeafs, unsigned int uiTailleMin);

	/************************************************************************************************************************************************************************
	***** GCRDETECTIONVOISINDICHO : Méthode déterminant la liste des voisins en utilisant des vecteurs et une dichotomie												*****
	*************************************************************************************************************************************************************************
	***** Entrée : vFRGLeafs : vector <CFragment> | uiTailleMin : unsigned int																							*****
	***** Nécessite : Ne nécessite rien																																	*****
	***** Sortie : Aucun élément retourné																																*****
	***** Entraine : Détermine les voisins à partir de la liste des feuilles du Split																					*****
	************************************************************************************************************************************************************************/
	void GCRDetectionVoisinDicho(vector <CFragment> vFRGLeafs, unsigned int uiTailleMin);

	/********************************************************************************************************************************************************************************************
	***** GCRBESTCOMPATIBILITY : Méthode déterminant les 2 meilleurs compatibilité entre 2 fragments voisins																				*****
	*********************************************************************************************************************************************************************************************
	***** Entrée : ppuipuiFacteurFusionnable : std::pair<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>, std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> &  *****
	*****		   puiPair : std::pair<unsigned int, unsigned int> & | uiHomogeneite : unsigned int																							*****
	***** Nécessite : Ne nécessite rien																																						*****
	***** Sortie : Aucun élément retourné																																					*****
	***** Entraine : Déterminant les 2 meilleurs compatibilité entre 2 fragments voisins																									*****
	********************************************************************************************************************************************************************************************/
	void GCRBestCompatibility(std::pair<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>, std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> & ppuipuiFacteurFusionnable, std::pair<unsigned int, unsigned int> & puiPair, unsigned int uiHomogeneite);

	/********************************************************************************************************************************************************************************************
	***** GCRTHREADFORMERGE : Méthode lançant tous les threads afin de les comparer																											*****
	*********************************************************************************************************************************************************************************************
	***** Entrée : ppuipuiFacteurFusionnable : std::pair<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>, std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> &  *****
	*****		   puiPair : std::pair<unsigned int, unsigned int> & | uiHomogeneite : unsigned int																							*****
	***** Nécessite : Ne nécessite rien																																						*****
	***** Sortie : Aucun élément retourné																																					*****
	***** Entraine : Lance tous les threads afin de les comparer																															*****
	********************************************************************************************************************************************************************************************/
	void GCRThreadForMerge(std::pair<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>, std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> & ppuipuiFacteurFusionnable, unsigned int uiHomogeneite, unsigned int uiDebut, unsigned int uiFin);

	/************************************************************************************************************************************************
	***** GCRMERGE : Méthode fusionnant les fragments voisins																					*****
	*************************************************************************************************************************************************
	***** Entrée : uiHomogeneite : unsigned int																									*****
	***** Nécessite : Ne Nécesste Rien				                                                                                            *****
	***** Sortie : Aucun élement retournée																										*****
	***** Entraine : Fusionne les fragments voisins																								*****
	************************************************************************************************************************************************/
	void GCRMerge(unsigned int uiHomogeneite);

	/************************************************************************************************************************************************
	***** GCRMERGETHREAD : Méthode fusionnant les fragments voisins	avec des threads															*****
	*************************************************************************************************************************************************
	***** Entrée : uiHomogeneite : unsigned int																									*****
	***** Nécessite : Ne Nécesste Rien				                                                                                            *****
	***** Sortie : Aucun élement retournée																										*****
	***** Entraine : Fusionne les fragments voisins	à l'aide de threads																			*****
	************************************************************************************************************************************************/
	void GCRMergeThread(unsigned int uiHomogeneite);
};

#endif
