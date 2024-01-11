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
	***** CGRAPHESCREATOR : Constructeur par d�faut de la classe CGraphesCreator																*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Initialise alGPCGraphe � null																								*****
	************************************************************************************************************************************************/
	CGrapheCreator();

	/************************************************************************************************************************************************
	***** GCRGETGRAPHE : Accesseur en lecture de alGPCGraphe																					*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																										*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : GPCGCRGraphe : CGrapheColore																									*****
	***** Entraine : Retourne la variable alGPCGraphe																							*****
	************************************************************************************************************************************************/
	BGLGraphe GCRGetGraphe();

	/************************************************************************************************************************************************
	***** GCRCREATIONGRAPHE : M�thode pour cr�er le graphe � partir des feuilles de l'arbre														*****
	*************************************************************************************************************************************************
	***** Entr�e : vFRGLeafs : vector <CFragment> | uiHomogeneite : unsigned int 																*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Compl�te le graphe de GPCGCRGraphe 																						*****
	************************************************************************************************************************************************/
	void GCRCreationGraphe(vector <CFragment> vFRGLeafs, unsigned int uiHomogeneite, unsigned int uiTailleMin, unsigned int uiVersion);

private:
	/************************************************************************************************************************************************
	***** GCRLINKVERTICES : M�thode liant 2 fragments du graphe																					*****
	*************************************************************************************************************************************************
	***** Entr�e : puiPair : std::pair<unsigned int, unsigned int>																				*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Relie les Sommets en modifiant si besoin la connexit�																		*****
	************************************************************************************************************************************************/
	void GCRLinkVertices(std::pair<unsigned int, unsigned int> puiPair);

	/************************************************************************************************************************************************
	***** GCRTHREADREDEF : M�thode appel� par un thread																							*****
	*************************************************************************************************************************************************
	***** Entr�e : uiConnexite1, uiConnexite2 : unsigned int | puiMinMax : std::pair <unsigned int, unsigned int> 								*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Modifie le Min/Max des sommets pr�sent dans la second connexit�															*****
	************************************************************************************************************************************************/
	void GCRThreadRedef(unsigned int uiConnexite1, unsigned int uiConnexite2, std::pair <unsigned int, unsigned int> puiMinMax);

	/************************************************************************************************************************************************
	***** GCRVERTICEONBORDER : M�thode d�terminant la pr�sence d'un fragment au bord de la matrice												*****
	*************************************************************************************************************************************************
	***** Entr�e : vdVertice : BGLGraphe::vertex_descriptor																						*****
	***** N�cessite : Doit exister dans le graphe                                                                                               *****
	***** Sortie : vbDirection : vector <bool>																									*****
	***** Entraine : D�termine la pr�sence d'un fragment au bord de la matrice																	*****
	************************************************************************************************************************************************/
	vector <bool> GCRVerticesOnBorder(BGLGraphe::vertex_descriptor vdVertices);

	/************************************************************************************************************************************************************************
	***** GCRDETECTIONVOISINVOXEL : M�thode d�terminant la liste des voisins � l'aide des voxels																		*****
	*************************************************************************************************************************************************************************
	***** Entr�e : vFRGLeafs : vector <CFragment> | uiTailleMin : unsigned int																							*****
	***** N�cessite : Ne n�cessite rien																																	*****
	***** Sortie : Aucun �l�ment retourn�																																*****
	***** Entraine : D�termine les voisins � partir de la liste des feuilles du Split																					*****
	************************************************************************************************************************************************************************/
	void GCRDetectionVoisinVoxel(vector <CFragment> vFRGLeafs, unsigned int uiTailleMin);

	/************************************************************************************************************************************************************************
	***** GCRDETECTIONVOISINV2DICHO : M�thode d�terminant la liste des voisins en utilisant des vecteurs de vecteur et une dichotomie									*****
	*************************************************************************************************************************************************************************
	***** Entr�e : vFRGLeafs : vector <CFragment> | uiTailleMin : unsigned int																							*****
	***** N�cessite : Ne n�cessite rien																																	*****
	***** Sortie : Aucun �l�ment retourn�																																*****
	***** Entraine : D�termine les voisins � partir de la liste des feuilles du Split																					*****
	************************************************************************************************************************************************************************/
	void GCRDetectionVoisinV2Dicho(vector <CFragment> vFRGLeafs, unsigned int uiTailleMin);

	/************************************************************************************************************************************************************************
	***** GCRDETECTIONVOISINDICHO : M�thode d�terminant la liste des voisins en utilisant des vecteurs et une dichotomie												*****
	*************************************************************************************************************************************************************************
	***** Entr�e : vFRGLeafs : vector <CFragment> | uiTailleMin : unsigned int																							*****
	***** N�cessite : Ne n�cessite rien																																	*****
	***** Sortie : Aucun �l�ment retourn�																																*****
	***** Entraine : D�termine les voisins � partir de la liste des feuilles du Split																					*****
	************************************************************************************************************************************************************************/
	void GCRDetectionVoisinDicho(vector <CFragment> vFRGLeafs, unsigned int uiTailleMin);

	/********************************************************************************************************************************************************************************************
	***** GCRBESTCOMPATIBILITY : M�thode d�terminant les 2 meilleurs compatibilit� entre 2 fragments voisins																				*****
	*********************************************************************************************************************************************************************************************
	***** Entr�e : ppuipuiFacteurFusionnable : std::pair<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>, std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> &  *****
	*****		   puiPair : std::pair<unsigned int, unsigned int> & | uiHomogeneite : unsigned int																							*****
	***** N�cessite : Ne n�cessite rien																																						*****
	***** Sortie : Aucun �l�ment retourn�																																					*****
	***** Entraine : D�terminant les 2 meilleurs compatibilit� entre 2 fragments voisins																									*****
	********************************************************************************************************************************************************************************************/
	void GCRBestCompatibility(std::pair<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>, std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> & ppuipuiFacteurFusionnable, std::pair<unsigned int, unsigned int> & puiPair, unsigned int uiHomogeneite);

	/********************************************************************************************************************************************************************************************
	***** GCRTHREADFORMERGE : M�thode lan�ant tous les threads afin de les comparer																											*****
	*********************************************************************************************************************************************************************************************
	***** Entr�e : ppuipuiFacteurFusionnable : std::pair<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>, std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> &  *****
	*****		   puiPair : std::pair<unsigned int, unsigned int> & | uiHomogeneite : unsigned int																							*****
	***** N�cessite : Ne n�cessite rien																																						*****
	***** Sortie : Aucun �l�ment retourn�																																					*****
	***** Entraine : Lance tous les threads afin de les comparer																															*****
	********************************************************************************************************************************************************************************************/
	void GCRThreadForMerge(std::pair<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>, std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> & ppuipuiFacteurFusionnable, unsigned int uiHomogeneite, unsigned int uiDebut, unsigned int uiFin);

	/************************************************************************************************************************************************
	***** GCRMERGE : M�thode fusionnant les fragments voisins																					*****
	*************************************************************************************************************************************************
	***** Entr�e : uiHomogeneite : unsigned int																									*****
	***** N�cessite : Ne N�cesste Rien				                                                                                            *****
	***** Sortie : Aucun �lement retourn�e																										*****
	***** Entraine : Fusionne les fragments voisins																								*****
	************************************************************************************************************************************************/
	void GCRMerge(unsigned int uiHomogeneite);

	/************************************************************************************************************************************************
	***** GCRMERGETHREAD : M�thode fusionnant les fragments voisins	avec des threads															*****
	*************************************************************************************************************************************************
	***** Entr�e : uiHomogeneite : unsigned int																									*****
	***** N�cessite : Ne N�cesste Rien				                                                                                            *****
	***** Sortie : Aucun �lement retourn�e																										*****
	***** Entraine : Fusionne les fragments voisins	� l'aide de threads																			*****
	************************************************************************************************************************************************/
	void GCRMergeThread(unsigned int uiHomogeneite);
};

#endif
