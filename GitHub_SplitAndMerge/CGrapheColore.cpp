#pragma once 

#include "CGrapheColore.h"

/************************************************************************************************************************************************
***** CGRAPHECOLORE : Constructeur par défaut de la classe CGrapheColore																	*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné																										*****
***** Entraine : Initialise uiGSLGray à null et crée un nouveau graphe vide																	*****
************************************************************************************************************************************************/
CGrapheColore::CGrapheColore() {
	GSLGPCGray = CGrayScale ();
}

/************************************************************************************************************************************************
***** CGRAPHECOLORE : Constructeur de confort de la classe CGrapheColore																	*****
*************************************************************************************************************************************************
***** Entrée : CFragment : FRGFragment																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné																										*****
***** Entraine : Initialise un nouveau graphe avec un sommet																				*****
************************************************************************************************************************************************/
CGrapheColore::CGrapheColore(CFragment FRGFragment) {
	
	GPCAddToGraph(FRGFragment);
}

/************************************************************************************************************************************************
***** GPCGETGRAPHE : Accesseur en lecture de la variable alGPCGraphe																		*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : alGPCGraphe : boost::adjacency_list <boost::vecS, boost::vecS, boost::directedS, CFragment, Propreties_Edges>				*****
***** Entraine : Returne le graphe alGPCGraphe																								*****
************************************************************************************************************************************************/
boost::adjacency_list <boost::vecS, boost::vecS, boost::directedS, CFragment, Propreties_Edges> CGrapheColore::GPCGetGraphe() {
	return alGPCGraphe;
}

/************************************************************************************************************************************************
***** GPCGETVERTICES : Accesseur en lecture de la variable alGPCGraphe																		*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : vector <CFragment> vFRGVertices																								*****
***** Entraine : Returne les vertices du graphe alGPCGraphe																					*****
************************************************************************************************************************************************/
vector <CFragment> CGrapheColore::GPCGetVertices() {
	BGLGraphe::vertex_iterator vInit, vEnd;
	vector <CFragment> vFRGVertices;

	for (boost::tie(vInit, vEnd) = boost::vertices(alGPCGraphe); vInit != vEnd; ++vInit) {
		vFRGVertices.push_back(alGPCGraphe[*vInit]);
	}

	return vFRGVertices;
}

/************************************************************************************************************************************************
***** GPCGETGRAY : Accesseur en lecture de la variable GSLGPCGray																			*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : GSLGPCGray : CGrayScale																										*****
***** Entraine : Retourne l'objet GSLGPCGray																								*****
************************************************************************************************************************************************/
CGrayScale CGrapheColore::GPCGetGray() {
	return GSLGPCGray;
}

/************************************************************************************************************************************************
***** GPCSETGRAY : Accesseur en écriture de la variable GSLGPCGray																			*****
*************************************************************************************************************************************************
***** Entrée : GSLGray : CGrayScale																											*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné																										*****
***** Entraine : Modifie l'objet GSLGPCGray																									*****
************************************************************************************************************************************************/
void CGrapheColore::GPCSetGray(CGrayScale GSLGray) {
	GSLGPCGray = GSLGray;
}

/************************************************************************************************************************************************
***** GPCVERTICEONBORDER : Méthode ajoutant des arcs sur les sommets aux bords de la matrice												*****
*************************************************************************************************************************************************
***** Entrée : Aucun paramètre d'entré																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : uiNb_Edges : unsigned int																									*****
***** Entraine : Ajoute des arcs dans les directions hors matrice																			*****
************************************************************************************************************************************************/
unsigned int CGrapheColore::GPCVerticeOnBorder() {

	BGLGraphe::vertex_iterator vInit, vEnd;
	boost::tie(vInit, vEnd) = boost::vertices(alGPCGraphe);
	vEnd--;

	CFragment FRGLastVertice = alGPCGraphe[*vEnd];
	vector <unsigned int> vuiCoosFragment = FRGLastVertice.FRGGetCoos ();

	unsigned int uiNb_Edges = 0;

	//Diminuer les répétitions (création et vérification)
	if (vuiCoosFragment[1] == 0) {
		boost::add_edge(*vEnd, *vEnd, { North_South, alGPCGraphe[*vEnd].FRGGetDimensions()[0] * alGPCGraphe[*vEnd].FRGGetDimensions()[2]}, alGPCGraphe); //Edges sur lui même

		uiNb_Edges += 1;
	}

	if (vuiCoosFragment[1] + FRGLastVertice.FRGGetDimensions()[1] == FRGLastVertice.FRGGetDimensionMatrice()[1]) {
		boost::add_edge(*vEnd, *vEnd, {South_North, alGPCGraphe[*vEnd].FRGGetDimensions()[0] * alGPCGraphe[*vEnd].FRGGetDimensions()[2] }, alGPCGraphe); //Edges sur lui même

		uiNb_Edges += 1;
	}

	if (vuiCoosFragment[0] == 0) {
		boost::add_edge(*vEnd, *vEnd, {West_East, alGPCGraphe[*vEnd].FRGGetDimensions()[1] * alGPCGraphe[*vEnd].FRGGetDimensions()[2] }, alGPCGraphe); //Edges sur lui même

		uiNb_Edges += 1;
	}

	if (vuiCoosFragment[0] + FRGLastVertice.FRGGetDimensions()[0] == FRGLastVertice.FRGGetDimensionMatrice()[0]) {
		boost::add_edge(*vEnd, *vEnd, { East_West, alGPCGraphe[*vEnd].FRGGetDimensions()[1] * alGPCGraphe[*vEnd].FRGGetDimensions()[2] }, alGPCGraphe); //Edges sur lui même

		uiNb_Edges += 1;
	}

	if (vuiCoosFragment[2] == 0) {
		boost::add_edge(*vEnd, *vEnd, { Front_Behind, alGPCGraphe[*vEnd].FRGGetDimensions()[0] * alGPCGraphe[*vEnd].FRGGetDimensions()[1] }, alGPCGraphe); //Edges sur lui même

		uiNb_Edges += 1;
	}

	if (vuiCoosFragment[2] + FRGLastVertice.FRGGetDimensions()[2] == FRGLastVertice.FRGGetDimensionMatrice()[2]) {
		boost::add_edge(*vEnd, *vEnd, { Behind_Front, alGPCGraphe[*vEnd].FRGGetDimensions()[0] * alGPCGraphe[*vEnd].FRGGetDimensions()[1] }, alGPCGraphe); //Edges sur lui même

		uiNb_Edges += 1;
	}

	return uiNb_Edges;
}

/************************************************************************************************************************************************
***** VALUEDIRECTION : Méthode retournant la Somme des values d'une direction																*****
*************************************************************************************************************************************************
***** Entrée : vDuiEdges : vector <std::pair <Direction, unsigned int>>	| direction : Direction												*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : uiValue : unsigned int																										*****
***** Entraine : Retourne la Somme des values d'une direction																				*****
************************************************************************************************************************************************/
unsigned int ValueDirection(vector <std::pair <Direction, unsigned int>> vDuiEdges, Direction direction) {

	unsigned int uiValue = 0;
	for (unsigned int uiBoucle = 0; uiBoucle < vDuiEdges.size(); uiBoucle++) {
		if (vDuiEdges[uiBoucle].first == direction) {
			uiValue += vDuiEdges[uiBoucle].second;
		}
	}

	return uiValue;
}

/************************************************************************************************************************************************
***** GPCADDTOGRAPH : Accesseur en écriture de la variable alGPCGraphe																		*****
*************************************************************************************************************************************************
***** Entrée : FRGFragment : CFragment																										*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : bGoodADD : boolean																											*****
***** Entraine : Ajoute un nouveau sommet dans le graphe																					*****
************************************************************************************************************************************************/
bool CGrapheColore::GPCAddToGraph(CFragment FRGFragment) {

	if (boost::num_vertices(alGPCGraphe) == 0) {

		//Ajout un noeud au graphe
		boost::add_vertex(FRGFragment, alGPCGraphe);
		GPCVerticeOnBorder();

		unsigned int uiColor = FRGFragment.FRGDominantColor().GSLGetGray();

		vuiColors.push_back(uiColor);
		GSLGPCGray.GSLSetGray(uiColor);
	}
	else {
		auto aFragment = boost::add_vertex(FRGFragment, alGPCGraphe);
		unsigned int uiNum_Edges = boost::num_edges(alGPCGraphe);
		uiNum_Edges += GPCVerticeOnBorder();

		//Lien avec les autres noeuds (s'il existe) -> boost::adjacent_vertices()

		BGLGraphe::vertex_iterator vInit, vEnd;

		//for (vp = boost::vertices(alGPCGraphe); vp.first != vp.second; ++vp.first) {
		for (boost::tie(vInit, vEnd) = boost::vertices(alGPCGraphe); vInit != vEnd; ++vInit) {

			CFragment FRGVertices = alGPCGraphe[*vInit];

			//Recupe tous les edges du sommet
			vector <std::pair <Direction, unsigned int>> vDuiEdges;

			boost::graph_traits<BGLGraphe>::out_edge_iterator eInit, eEnd;
			for (boost::tie(eInit, eEnd) = boost::out_edges(*vInit, alGPCGraphe); eInit != eEnd; ++eInit) {
				vDuiEdges.push_back({ alGPCGraphe[*eInit].direction, alGPCGraphe[*eInit].value_use });
			}

			vector <unsigned int> vuiCoosFragment = FRGFragment.FRGGetCoos();

			//Verif si pas le même noeud
			if (FRGVertices.FRGGetCoos() != vuiCoosFragment) {
					
				unsigned int uiValueDirectionN = ValueDirection(vDuiEdges, North_South); //Si North pas trouvé (value = 0)
				if (uiValueDirectionN < FRGVertices.FRGGetDimensions()[0] * FRGVertices.FRGGetDimensions()[2]) {

					unsigned int uiSurfaceUse = 0;
					//North Face
					for (unsigned int uiBoucleZV = 0; uiBoucleZV < FRGVertices.FRGGetDimensions()[2]; uiBoucleZV++) {
						for (unsigned int uiBoucleZF = 0; uiBoucleZF < FRGFragment.FRGGetDimensions()[2]; uiBoucleZF++) {
							for (unsigned int uiBoucleXV = 0; uiBoucleXV < FRGVertices.FRGGetDimensions()[0]; uiBoucleXV++) {
								for (unsigned int uiBoucleXF = 0; uiBoucleXF < FRGFragment.FRGGetDimensions()[0]; uiBoucleXF++) {
									if (FRGVertices.FRGGetCoos()[0] + uiBoucleXV == vuiCoosFragment[0] + uiBoucleXF
										&& FRGVertices.FRGGetCoos()[1] == vuiCoosFragment[1] + FRGFragment.FRGGetDimensions()[1] //borne inférieur du parallélépipède rectangle
										&& FRGVertices.FRGGetCoos()[2] + uiBoucleZV == vuiCoosFragment[2] + uiBoucleZF) {
										
										uiSurfaceUse += 1;
									}
								}
							}
						}
					}

					if (uiSurfaceUse > 0) {
						boost::add_edge(*vInit, aFragment, { North_South, uiSurfaceUse }, alGPCGraphe);
						boost::add_edge(aFragment, *vInit, { South_North, uiSurfaceUse }, alGPCGraphe);
					}
				}
				
				unsigned int uiValueDirectionS = ValueDirection(vDuiEdges, South_North); //Si South pas trouvé (value = 0)
				if (uiValueDirectionS < FRGVertices.FRGGetDimensions()[0] * FRGVertices.FRGGetDimensions()[2]) {

					unsigned int uiSurfaceUse = 0;

					//South Face
					for (unsigned int uiBoucleZV = 0; uiBoucleZV < FRGVertices.FRGGetDimensions()[2]; uiBoucleZV++) {
						for (unsigned int uiBoucleZF = 0; uiBoucleZF < FRGFragment.FRGGetDimensions()[2]; uiBoucleZF++) {
							for (unsigned int uiBoucleXV = 0; uiBoucleXV < FRGVertices.FRGGetDimensions()[0]; uiBoucleXV++) {
								for (unsigned int uiBoucleXF = 0; uiBoucleXF < FRGFragment.FRGGetDimensions()[0]; uiBoucleXF++) {
									if (FRGVertices.FRGGetCoos()[0] + uiBoucleXV == vuiCoosFragment[0] + uiBoucleXF
										&& FRGVertices.FRGGetCoos()[1] + FRGVertices.FRGGetDimensions()[1] == vuiCoosFragment[1] //borne inférieur du parallélépipède rectangle
										&& FRGVertices.FRGGetCoos()[2] + uiBoucleZV == vuiCoosFragment[2] + uiBoucleZF) {

										uiSurfaceUse += 1;
									}
								}
							}
						}
					}

					if (uiSurfaceUse > 0) {
						boost::add_edge(*vInit, aFragment, { South_North, uiSurfaceUse}, alGPCGraphe);
						boost::add_edge(aFragment, *vInit, { North_South, uiSurfaceUse}, alGPCGraphe);
					}
				}

				unsigned int uiValueDirectionW = ValueDirection(vDuiEdges, West_East); //Si West pas trouvé (value = 0)
				if (uiValueDirectionW < FRGVertices.FRGGetDimensions()[1] * FRGVertices.FRGGetDimensions()[2]) {

					unsigned int uiSurfaceUse = 0;
					//East Face
					for (unsigned int uiBoucleZV = 0; uiBoucleZV < FRGVertices.FRGGetDimensions()[2]; uiBoucleZV++) {
						for (unsigned int uiBoucleZF = 0; uiBoucleZF < FRGFragment.FRGGetDimensions()[2]; uiBoucleZF++) {
							for (unsigned int uiBoucleYV = 0; uiBoucleYV < FRGVertices.FRGGetDimensions()[1]; uiBoucleYV++) {
								for (unsigned int uiBoucleYF = 0; uiBoucleYF < FRGFragment.FRGGetDimensions()[1]; uiBoucleYF++) {
									if (FRGVertices.FRGGetCoos()[0] == vuiCoosFragment[0] + FRGFragment.FRGGetDimensions()[0] //borne latérale du parallélépipède rectangle
										&& FRGVertices.FRGGetCoos()[1] + uiBoucleYV == vuiCoosFragment[1] + uiBoucleYF
										&& FRGVertices.FRGGetCoos()[2] + uiBoucleZV == vuiCoosFragment[2] + uiBoucleZF) {

										uiSurfaceUse += 1;
									}
								}
							}
						}
					}

					if (uiSurfaceUse > 0) {
						boost::add_edge(*vInit, aFragment, { West_East, uiSurfaceUse}, alGPCGraphe);
						boost::add_edge(aFragment, *vInit, { East_West, uiSurfaceUse}, alGPCGraphe);
					}
				}

				unsigned int uiValueDirectionE = ValueDirection(vDuiEdges, East_West); //Si East pas trouvé (value = 0)
				if (uiValueDirectionE < FRGVertices.FRGGetDimensions()[1] * FRGVertices.FRGGetDimensions()[2]) {

					unsigned int uiSurfaceUse = 0;
					//West Face
					for (unsigned int uiBoucleZV = 0; uiBoucleZV < FRGVertices.FRGGetDimensions()[2]; uiBoucleZV++) {
						for (unsigned int uiBoucleZF = 0; uiBoucleZF < FRGFragment.FRGGetDimensions()[2]; uiBoucleZF++) {
							for (unsigned int uiBoucleYV = 0; uiBoucleYV < FRGVertices.FRGGetDimensions()[1]; uiBoucleYV++) {
								for (unsigned int uiBoucleYF = 0; uiBoucleYF < FRGFragment.FRGGetDimensions()[1]; uiBoucleYF++) {
									if (FRGVertices.FRGGetCoos()[0] + FRGVertices.FRGGetDimensions()[0] == vuiCoosFragment[0] //borne latérale du parallélépipède rectangle
										&& FRGVertices.FRGGetCoos()[1] + uiBoucleYV == vuiCoosFragment[1] + uiBoucleYF
										&& FRGVertices.FRGGetCoos()[2] + uiBoucleZV == vuiCoosFragment[2] + uiBoucleZF) {

										uiSurfaceUse += 1;
									}
								}
							}
						}
					}

					if (uiSurfaceUse > 0) {
						boost::add_edge(*vInit, aFragment, { East_West, uiSurfaceUse}, alGPCGraphe);
						boost::add_edge(aFragment, *vInit, { West_East, uiSurfaceUse}, alGPCGraphe);
					}
				}

				unsigned int uiValueDirectionF = ValueDirection(vDuiEdges, Front_Behind); //Si Front pas trouvé (value = 0)
				if (uiValueDirectionF < FRGVertices.FRGGetDimensions()[0] * FRGVertices.FRGGetDimensions()[1]) {

					unsigned int uiSurfaceUse = 0;
					//Front Face
					for (unsigned int uiBoucleXV = 0; uiBoucleXV < FRGVertices.FRGGetDimensions()[0]; uiBoucleXV++) {
						for (unsigned int uiBoucleXF = 0; uiBoucleXF < FRGFragment.FRGGetDimensions()[0]; uiBoucleXF++) {
							for (unsigned int uiBoucleYV = 0; uiBoucleYV < FRGVertices.FRGGetDimensions()[1]; uiBoucleYV++) {
								for (unsigned int uiBoucleYF = 0; uiBoucleYF < FRGFragment.FRGGetDimensions()[1]; uiBoucleYF++) {
									if (FRGVertices.FRGGetCoos()[0] + uiBoucleXV == vuiCoosFragment[0] + uiBoucleXF
										&& FRGVertices.FRGGetCoos()[1] + uiBoucleYV == vuiCoosFragment[1] + uiBoucleYF
										&& FRGVertices.FRGGetCoos()[2] == vuiCoosFragment[2] + FRGFragment.FRGGetDimensions()[2]) {

										uiSurfaceUse += 1;
									}
								}
							}
						}
					}

					if (uiSurfaceUse > 0) {

						boost::add_edge(*vInit, aFragment, { Front_Behind, uiSurfaceUse}, alGPCGraphe);
						boost::add_edge(aFragment, *vInit, { Behind_Front, uiSurfaceUse}, alGPCGraphe);
					}
				}

				unsigned int uiValueDirectionB = ValueDirection(vDuiEdges, Behind_Front); //Si West pas trouvé (value = 0)
				if (uiValueDirectionB < FRGVertices.FRGGetDimensions()[0] * FRGVertices.FRGGetDimensions()[1]) {

					unsigned int uiSurfaceUse = 0;
					//Behind Face
					for (unsigned int uiBoucleXV = 0; uiBoucleXV < FRGVertices.FRGGetDimensions()[0]; uiBoucleXV++) {
						for (unsigned int uiBoucleXF = 0; uiBoucleXF < FRGFragment.FRGGetDimensions()[0]; uiBoucleXF++) {
							for (unsigned int uiBoucleYV = 0; uiBoucleYV < FRGVertices.FRGGetDimensions()[1]; uiBoucleYV++) {
								for (unsigned int uiBoucleYF = 0; uiBoucleYF < FRGFragment.FRGGetDimensions()[1]; uiBoucleYF++) {
									if (FRGVertices.FRGGetCoos()[0] + uiBoucleXV == vuiCoosFragment[0] + uiBoucleXF
										&& FRGVertices.FRGGetCoos()[1] + uiBoucleYV == vuiCoosFragment[1] + uiBoucleYF
										&& FRGVertices.FRGGetCoos()[2] + FRGVertices.FRGGetDimensions()[2] == vuiCoosFragment[2]) {

										uiSurfaceUse += 1;
									}
								}
							}
						}
					}

					if (uiSurfaceUse > 0) {
						boost::add_edge(*vInit, aFragment, { Behind_Front, uiSurfaceUse}, alGPCGraphe);
						boost::add_edge(aFragment, *vInit, { Front_Behind, uiSurfaceUse}, alGPCGraphe);
					}
				}
			}
		}

		if (uiNum_Edges == boost::num_edges(alGPCGraphe)) {

			boost::remove_vertex(aFragment, alGPCGraphe);
			return false;
		}
		else {
			vuiColors.push_back (FRGFragment.FRGDominantColor().GSLGetGray());

			unsigned int uiGrayMedian = static_cast<unsigned int> (round ((double)accumulate(vuiColors.begin(), vuiColors.end(), 0) / (double) boost::num_vertices(alGPCGraphe)));

			GSLGPCGray.GSLSetGray(uiGrayMedian);
		}
	}

	std::cout << "nombre sommet et edges : " << boost::num_vertices (alGPCGraphe) << " et " << boost::num_edges(alGPCGraphe) << std::endl;

	return true;
}

//std::pair<boost::graph_traits<G>::vertex_iterator, boost::graph_traits<G>::vertex_iterator> vp;
//for (vp = boost::vertices(alGPCGraphe); vp.first != vp.second; ++vp.first) {
//CFragment FRGVertices = get(boost::vertex_bundle, alGPCGraphe)[*vp.first];

/************************************************************************************************************************************************
***** GPCMERGEVERTICE : Accesseur en écriture de la variable alGPCGraphe																	*****
*************************************************************************************************************************************************
***** Entrée : alGrapheToMerge : BGLGraphe & vdVertices : BGLGraphe::vertex_descriptor & vFRGAddInComing : vector <CFragment> * 			*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné																										*****
***** Entraine : Ajoute un sommet au graphe avec ses arcs																					*****
************************************************************************************************************************************************/
BGLGraphe::vertex_descriptor CGrapheColore::GPCMergeVertice(BGLGraphe alGrapheToMerge, BGLGraphe::vertex_descriptor vdVertice, vector <CFragment> * vFRGAddInComing) {

	cout << "taille vFRGAddIncoming : " << vFRGAddInComing->size() << endl;
	BGLGraphe::vertex_iterator vInit, vEnd; //Vertices du alGPCGraphe
	BGLGraphe::vertex_descriptor vdNewVertex, vdNewTarget;

	bool ToAdd = true;
	for (boost::tie(vInit, vEnd) = boost::vertices(alGPCGraphe); vInit != vEnd; ++vInit) { //try with find (atention pour voisin)
		//Si il existe -> pas ajouter sinon ajouter => boost::add_vertex(alGrapheToMerge[*viVertice], alGPCGraphe);
		//surface = surface max

		if (alGPCGraphe[*vInit].FRGGetCoos() == alGrapheToMerge[vdVertice].FRGGetCoos()) {
			ToAdd = false;
			vdNewVertex = *vInit;
		}

		//noté voisin ? normalement pas possible
	}

	if (ToAdd) {
		vdNewVertex = boost::add_vertex(alGrapheToMerge[vdVertice], alGPCGraphe);
		cout << "nouveau " << endl;
	}

	cout << alGrapheToMerge[vdVertice].FRGGetCoos()[0] << alGrapheToMerge[vdVertice].FRGGetCoos()[1] << alGrapheToMerge[vdVertice].FRGGetCoos()[2] << endl;
	vFRGAddInComing->push_back(alGrapheToMerge[vdVertice]);

	boost::graph_traits<BGLGraphe>::out_edge_iterator eInitM, eEndM; //eInit = iterator et *eInit = descriptor
	//alGrapheToMerge[*eInitM] => structure de l'edge


	for (boost::tie(eInitM, eEndM) = boost::out_edges(vdVertice, alGrapheToMerge); eInitM != eEndM; ++eInitM) {

		BGLGraphe::vertex_descriptor vdVerticeTarget = boost::target(*eInitM, alGrapheToMerge); //vertex descriptor of alGrapheToMerge != alGPCGraphe

		if ((alGrapheToMerge[vdVerticeTarget].FRGGetCoos() == alGrapheToMerge[vdVertice].FRGGetCoos()) && ToAdd) { //Si boucle et pas ceux déjà existant
			cout << "lui meme" << endl;
			boost::add_edge(vdNewVertex, vdNewVertex, alGrapheToMerge[*eInitM], alGPCGraphe);
		}
		else if (alGrapheToMerge[vdVerticeTarget].FRGGetCoos() != alGrapheToMerge[vdVertice].FRGGetCoos()) {
			if (std::find(vFRGAddInComing->begin(), vFRGAddInComing->end(), alGrapheToMerge[vdVerticeTarget]) == vFRGAddInComing->end()) { //Si pas boucle et pas dans ceux déjà existant

				vdNewTarget = GPCMergeVertice(alGrapheToMerge, vdVerticeTarget, vFRGAddInComing);
			}
			else {
				vdNewTarget = vdVerticeTarget;
			}



			cout << "edges => " << alGrapheToMerge[vdVertice].FRGGetCoos()[0] << alGrapheToMerge[vdVertice].FRGGetCoos()[1] << alGrapheToMerge[vdVertice].FRGGetCoos()[2] << " et "
				<< alGrapheToMerge[vdVerticeTarget].FRGGetCoos()[0] << alGrapheToMerge[vdVerticeTarget].FRGGetCoos()[1] << alGrapheToMerge[vdVerticeTarget].FRGGetCoos()[2] << endl;
			boost::add_edge(vdNewVertex, vdNewTarget, alGrapheToMerge[*eInitM], alGPCGraphe);
		}
	}

	return vdNewVertex;

	//boost::graph_traits<BGLGraphe>::out_edge_iterator eInitM, eEndM;
	//alGrapheToMerge[boost::target(*eInitM, alGrapheToMerge)]
}

/************************************************************************************************************************************************
***** GPCMERGEGRAPHS : Accesseur en écriture de la variable alGPCGraphe																		*****
*************************************************************************************************************************************************
***** Entrée : GPCGraphe : CGrapheColore																									*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : bVerif : boolean																												*****
***** Entraine : Fusionne 2 graphes entre eux																								*****
************************************************************************************************************************************************/
bool CGrapheColore::GPCMergeGraphs(CGrapheColore GPCGraphe) {

	BGLGraphe alGrapheToMerge = GPCGraphe.GPCGetGraphe();
	BGLGraphe alGrapheSave = alGPCGraphe;

	unsigned int uiNbrVerticesPre = boost::num_vertices(alGPCGraphe);
	unsigned int uiNbrEdgesPre = boost::num_edges(alGPCGraphe);

	unsigned int uiNbrVerticesMerge = boost::num_vertices(alGrapheToMerge);
	unsigned int uiNbrEdgesMerge = boost::num_edges(alGrapheToMerge);

	cout << "Nombre de vertices " << boost::num_vertices(alGPCGraphe) << " avec edges : " << boost::num_edges(alGPCGraphe) << endl;
	cout << "Nombre de vertices à fusionner " << boost::num_vertices(alGrapheToMerge) << " avec edges : " << boost::num_edges(alGrapheToMerge) << endl;

	BGLGraphe::vertex_iterator vInit = boost::vertices(alGrapheToMerge).first;
	BGLGraphe::vertex_descriptor dVertice = *vInit;

	vector <CFragment> vFRGAddInComing = {};
	GPCMergeVertice(alGrapheToMerge, dVertice, &vFRGAddInComing);

	cout << "Final Nombre de vertices " << boost::num_vertices(alGPCGraphe) << " avec edges : " << boost::num_edges(alGPCGraphe) << endl;

	if ((uiNbrEdgesPre + uiNbrEdgesMerge == boost::num_edges(alGPCGraphe)) && (uiNbrVerticesPre + uiNbrVerticesMerge == boost::num_vertices(alGPCGraphe))) {
		alGPCGraphe = alGrapheSave;
		return false;
	}
	else {
		cout << "ok ok" << endl;
		GSLGPCGray.GSLSetGray(static_cast<unsigned int> (round((double)GSLGPCGray.GSLGetGray() + (double)GPCGraphe.GPCGetGray().GSLGetGray()) / 2));
	}
	
	return true;
}