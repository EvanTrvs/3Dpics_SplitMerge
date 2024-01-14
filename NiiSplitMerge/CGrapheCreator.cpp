#pragma once 

#include <time.h>
#include "CGrapheCreator.h"

/************************************************************************************************************************************************
***** Default Class Constructor																												*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Initialize alGPCGraphe, vvdGPCVertex_Desc and vvuiGPCConnexite to null                                                      *****
************************************************************************************************************************************************/
CGrapheCreator::CGrapheCreator() {

	//Initialialize variables
	alGPCGraphe = BGLGraphe();

	vvdGPCVertex_Desc = {};
	vvuiGPCConnexite = {};
}

/************************************************************************************************************************************************
***** GCRGetGraphe : Reading Accessor  																										*****
*************************************************************************************************************************************************
***** Input : None																															*****
***** Precondition : Nothing                                                                                                                *****
***** Output : None																															*****
***** Effects : Return variable alGPCGraphe																									*****
************************************************************************************************************************************************/
BGLGraphe CGrapheCreator::GCRGetGraphe() {
	return alGPCGraphe;
}

/********************************************************************************************************************************************************
***** LectureDichotomie : Method for Reading dichotomic  																							*****
*********************************************************************************************************************************************************
***** Input : vpuivuiJonction : vector <std::pair<unsigned int, vector<unsigned int>>> & | vuiCoos : vector <unsigned int> | sOrientation : string	*****
***** Precondition : Nothing																														*****
***** Output : itvvuiVoisin : vector <std::pair<unsigned int, vector<unsigned int>>>::iterator														*****
***** Effects : Return iterator variable of voxel neighbor																							*****
********************************************************************************************************************************************************/
vector <std::pair<unsigned int, vector<unsigned int>>>::iterator LectureDichotomie (vector <std::pair<unsigned int, vector<unsigned int>>> & vpuivuiJonction, vector <unsigned int> vuiCoos, string sOrientation) {

	//vector terminals initialization
	unsigned int uiBorneInf = 0;
	unsigned int uiBorneSup = (unsigned int)vpuivuiJonction.size();

	if (uiBorneInf == uiBorneSup) { //if the vector is empty
		return vpuivuiJonction.end();
	}

	//Initialization of element required for research
	unsigned int uiIndice;
	std::pair<unsigned int, vector<unsigned int>> puivuiComparaison;

	unsigned int uiSommeXZ = vuiCoos[0] + vuiCoos[2];
	unsigned int uiSommeYZ = vuiCoos[1] + vuiCoos[2];
	unsigned int uiSommeXY = vuiCoos[0] + vuiCoos[1];

	//For North / South Faces
	if (sOrientation == "North_South") { //Look on X / Z
		while (uiBorneInf != uiBorneSup) {

			uiIndice = (uiBorneInf + uiBorneSup) / 2; //Mid-section index analyzed
			puivuiComparaison = vpuivuiJonction[uiIndice]; //mid value

			//if 2 values are equals => stop
			if (vpuivuiJonction[uiBorneInf].second[0] + vpuivuiJonction[uiBorneInf].second[2] == vpuivuiJonction[uiBorneSup - 1].second[0] + vpuivuiJonction[uiBorneSup - 1].second[2]) {
				break;
			}

			/* ELSE */

			//Left Part Analyze
			if (puivuiComparaison.second[0] + puivuiComparaison.second[2] > uiSommeXZ) {
				uiBorneSup = uiIndice;
			}
			else { //Right Part Analyze
				uiBorneInf = uiIndice + 1;
			}
		}

		//Egality possibility so visit theirs
		for (vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFound = vpuivuiJonction.begin(); itFound != vpuivuiJonction.end(); itFound++) {
			if ((*itFound).second == vuiCoos) {
				
				//when it find
				return itFound;
			}
		}

		//No element find
		return vpuivuiJonction.end();
	}

	//For East / West Faces
	else if (sOrientation == "East_West") { //Look on Y / Z
		while (uiBorneInf != uiBorneSup) {

			uiIndice = (uiBorneInf + uiBorneSup) / 2; //Mid-section index analyzed
			puivuiComparaison = vpuivuiJonction[uiIndice]; //mid value

			//if 2 values are equals => stop
			if (vpuivuiJonction[uiBorneInf].second[1] + vpuivuiJonction[uiBorneInf].second[2] == vpuivuiJonction[uiBorneSup - 1].second[1] + vpuivuiJonction[uiBorneSup - 1].second[2]) {
				break;
			}

			/* ELSE */

			//Left Part Analyze
			if (puivuiComparaison.second[1] + puivuiComparaison.second[2] > uiSommeYZ) {
				uiBorneSup = uiIndice;
			}
			else { //Right Part Analyze
				uiBorneInf = uiIndice + 1;
			}
		}

		//Egality possibility so visit theirs
		for (vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFound = vpuivuiJonction.begin(); itFound != vpuivuiJonction.end(); itFound++) {
			if ((*itFound).second == vuiCoos) {
				return itFound;
			}
		}

		//No element find
		return vpuivuiJonction.end();

	}

	//For Behind et Front Faces
	else { //Look on X / Y
		while (uiBorneInf != uiBorneSup) {

			uiIndice = (uiBorneInf + uiBorneSup) / 2; //Indice du milieu de la section analysé précédemment
			puivuiComparaison = vpuivuiJonction[uiIndice]; //Valeur de ce milieu

			//if 2 values are equals => stop
			if (vpuivuiJonction[uiBorneInf].second[0] + vpuivuiJonction[uiBorneInf].second[1] == vpuivuiJonction[uiBorneSup - 1].second[0] + vpuivuiJonction[uiBorneSup - 1].second[1]) {
				break;
			}

			/* ELSE */

			//Left Part Analyze
			if (puivuiComparaison.second[0] + puivuiComparaison.second[1] > uiSommeXY) {
				uiBorneSup = uiIndice;
			}
			else { //Right Part Analyze
				uiBorneInf = uiIndice + 1;
			}
		}

		//Egality possibility so visit theirs
		for (vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFound = vpuivuiJonction.begin(); itFound != vpuivuiJonction.end(); itFound++) {
			if ((*itFound).second == vuiCoos) {
				return itFound;
			}
		}

		//No element find
		return vpuivuiJonction.end();
	}
}

/****************************************************************************************************************************************************************************************
***** EcritureDichotomie : Method for Writting dichotomic  																															*****
*****************************************************************************************************************************************************************************************
***** Input : vpuivuiJonction : vector <std::pair<unsigned int, vector<unsigned int>>>	& | puivuiNewPair : std::pair<unsigned int, vector<unsigned int>> | sOrientation : string	*****
***** Precondition : Nothing																																						*****
***** Output : None																																									*****
***** Effects : Write in vector (parameter) informations of voxel																													*****
****************************************************************************************************************************************************************************************/
void EcritureDichotomie(vector <std::pair<unsigned int, vector<unsigned int>>> & vpuivuiJonction, std::pair<unsigned int, vector<unsigned int>> puivuiNewPair, string sOrientation) {

	//vector terminals initialization
	unsigned int uiBorneInf = 0;
	unsigned int uiBorneSup = (unsigned int)vpuivuiJonction.size();

	if (uiBorneInf == uiBorneSup) { //if the vector is empty
		vpuivuiJonction.push_back(puivuiNewPair);
		return;
	}

	//Elements initialization for research
	unsigned int uiIndice;
	std::pair<unsigned int, vector<unsigned int>> puivuiComparaison;

	unsigned int uiSommeXZ = puivuiNewPair.second[0] + puivuiNewPair.second[2];
	unsigned int uiSommeYZ = puivuiNewPair.second[1] + puivuiNewPair.second[2];
	unsigned int uiSommeXY = puivuiNewPair.second[0] + puivuiNewPair.second[1];

	//North / South Faces
	if (sOrientation == "North_South") { //Look on X and Z 
		while (uiBorneInf != uiBorneSup) {

			uiIndice = (uiBorneInf + uiBorneSup) / 2; //Mid-section index analyzed
			puivuiComparaison = vpuivuiJonction[uiIndice]; //mid value

			//Next Writting in the left part
			if (puivuiComparaison.second[0] + puivuiComparaison.second[2] > uiSommeXZ) {
				uiBorneSup = uiIndice;
			}
			else { //Next Writting in the right part
				uiBorneInf = uiIndice + 1;
			}
		}

		//Writting
		vpuivuiJonction.insert(vpuivuiJonction.begin() + uiBorneInf, puivuiNewPair);
	}

	//East / West Faces
	else if (sOrientation == "East_West") {//Look on Y / Z
		while (uiBorneInf != uiBorneSup) {

			uiIndice = (uiBorneInf + uiBorneSup) / 2; //Mid-section index analyzed
			puivuiComparaison = vpuivuiJonction[uiIndice]; //mid value

			//Next Writting in the left part
			if (puivuiComparaison.second[1] + puivuiComparaison.second[2] > uiSommeYZ) {
				uiBorneSup = uiIndice;
			}
			else { //Next Writting in the right part
				uiBorneInf = uiIndice + 1;
			}
		}

		//Writting
		vpuivuiJonction.insert(vpuivuiJonction.begin() + uiBorneInf, puivuiNewPair);
	}

	//Behind / Front Faces
	else { //Look on sur X / Y
		while (uiBorneInf != uiBorneSup) {

			uiIndice = (uiBorneInf + uiBorneSup) / 2; //Mid-section index analyzed
			puivuiComparaison = vpuivuiJonction[uiIndice]; //mid value

			//Next Writting in the left part
			if (puivuiComparaison.second[0] + puivuiComparaison.second[1] > uiSommeXY) {
				uiBorneSup = uiIndice;
			}
			else { //Next Writting in the right part
				uiBorneInf = uiIndice + 1;
			}
		}

		//Writting
		vpuivuiJonction.insert(vpuivuiJonction.begin() + uiBorneInf, puivuiNewPair);
	}
}

/********************************************************************************************************************************************************
***** GCRVerticesOnBorder : Method for detect fragment on borders  																					*****
*********************************************************************************************************************************************************
***** Input : vdVertice : BGLGraphe::vertex_descriptor																								*****
***** Precondition : Need to Exist in the graphe																									*****
***** Output : vbDirection : vector <bool>																											*****
***** Effects : Return a vector of boolean for each direction																						*****
********************************************************************************************************************************************************/
vector <bool> CGrapheCreator::GCRVerticesOnBorder(BGLGraphe::vertex_descriptor vdVertices) {

	//Recovery of fragment and it coos
	CFragment FRGLastVertice = alGPCGraphe[vdVertices];
	vector <unsigned int> vuiCoosFragment = FRGLastVertice.FRGGetCoos();

	//Initialization of all values => false = not on the border
	vector <bool> vbDirection = {false, false, false, false, false, false};

	/* Determines, based on fragment coordinates and dimensions, whether an edge is nearby or not */
	if (vuiCoosFragment[1] == 0) {
		vbDirection[0] = true; //North
	}

	if (vuiCoosFragment[1] + FRGLastVertice.FRGGetDimensions()[1] == FRGLastVertice.FRGGetDimensionMatrice()[1]) {
		vbDirection[1] = true; //South
	}

	if (vuiCoosFragment[0] + FRGLastVertice.FRGGetDimensions()[0] == FRGLastVertice.FRGGetDimensionMatrice()[0]) {
		vbDirection[3] = true; //East
	}

	if (vuiCoosFragment[0] == 0) {
		vbDirection[2] = true; //West
	}

	if (vuiCoosFragment[2] == 0) {
		vbDirection[5] = true; //Front
	}

	if (vuiCoosFragment[2] + FRGLastVertice.FRGGetDimensions()[2] == FRGLastVertice.FRGGetDimensionMatrice()[2]) {
		vbDirection[4] = true; //Behind
	}

	//Return boolean vector
	return vbDirection;
}

/********************************************************************************************************************************************************
***** GCRDetectionVoisinVoxel : Method for create pairs of neighbor																					*****
*********************************************************************************************************************************************************
***** Input : vFRGLeafs : vector <CFragment> | uiTailleMin : unsigned int																			*****
***** Precondition : Nothing																														*****
***** Output : None																																	*****
***** Effects : Filled the vector vpuiGPCVoisinPrimal (attribut) of pairs of neighbors with voxel													*****
********************************************************************************************************************************************************/
void CGrapheCreator::GCRDetectionVoisinVoxel(vector <CFragment> vFRGLeafs, unsigned int uiTailleMin) {

	//Exception management : uiTailleMin = 0
	if (uiTailleMin == 0) {
		CException EXCErreur;
		EXCErreur.EXCModifierValeur(SEUIL_MIN);
		throw (EXCErreur);
	}

	//Recovery of matrice informations (dimensions and entire matrice)
	vector <unsigned int> vuiDimensionsMatrice = vFRGLeafs[0].FRGGetDimensionMatrice();
	boost::multi_array <CGrayScale, 3> * maMatrice = vFRGLeafs[0].FRGGetMatrice();

	//Loop on all leafs (vFRGLeafs = fragments generate with the Split) 
	unsigned int uiConnexite = 0;
	for (vector<CFragment>::iterator itFRGFeuille = vFRGLeafs.begin(); itFRGFeuille != vFRGLeafs.end(); itFRGFeuille++) {

		//Recovery of fragment informations (coos and dimensions)
		vector <unsigned int> vuiCoosFragment = (*itFRGFeuille).FRGGetCoos();
		vector <unsigned int> vuiDimensionsFragment = (*itFRGFeuille).FRGGetDimensions();

		/* For the next part : Set Connexity */
		(*itFRGFeuille).FRGSetConnexite(uiConnexite);
		vvuiGPCConnexite.push_back({ uiConnexite });

		//storage of fragment on the graphe
		BGLGraphe::vertex_descriptor vdVertices = boost::add_vertex((*itFRGFeuille), alGPCGraphe);
		vvdGPCVertex_Desc.push_back(vdVertices); //organisation in list (first connexity = place)

		//Using a method for detect if this fragment is on borders
		vector <bool> vbDirection = GCRVerticesOnBorder(vdVertices);

		if (!vbDirection[0]) { //North Face
			//For each voxel on the face (limited to proven points of intersection)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {

					//Voxel coos
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Wrtting in the matrice, the connexity of the voxel (link with the fragment)
					maMatrice[0][vuiCoos[0]][vuiCoos[1]][vuiCoos[2]].GSLSetConnexite(uiConnexite);

					//Determine the voxel to the north and its connection
					vector <unsigned int> vuiCoosNorth = { uiBoucleX + vuiCoosFragment[0], vuiCoosFragment[1] - 1, uiBoucleZ + vuiCoosFragment[2] };
					int iConnexiteNorth = maMatrice[0][vuiCoosNorth[0]][vuiCoosNorth[1]][vuiCoosNorth[2]].GSLGetConnexite();

					//If the connexity isn't equal to -1 (initialization value) => then already explore and know the connexity of it fragment
					if (iConnexiteNorth != -1) {
						
						//Pair creation with min first and max second
						unsigned int uiMin = min(static_cast <int> (uiConnexite), iConnexiteNorth), uiMax = max(static_cast <int> (uiConnexite), iConnexiteNorth);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add in the storage vector
						vpuiGPCVoisinPrimal.push_back(puiPair);
					}
				}
			}
		}

		if (!vbDirection[1]) { //South Face
			//For each voxel on the face (limited to proven points of intersection)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {
					// Y + Dimension 2

					//Voxel coos
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], vuiCoosFragment[1] + vuiDimensionsFragment[1] - 1, uiBoucleZ + vuiCoosFragment[2] };

					//Wrtting in the matrice, the connexity of the voxel (link with the fragment)
					maMatrice[0][vuiCoos[0]][vuiCoos[1]][vuiCoos[2]].GSLSetConnexite(uiConnexite);

					//Determine the voxel to the north and its connection
					vector <unsigned int> vuiCoosSouth = { uiBoucleX + vuiCoosFragment[0], vuiCoosFragment[1] + vuiDimensionsFragment[1], uiBoucleZ + vuiCoosFragment[2] };
					int iConnexiteSouth = maMatrice[0][vuiCoosSouth[0]][vuiCoosSouth[1]][vuiCoosSouth[2]].GSLGetConnexite();

					//If the connexity isn't equal to -1 (initialization value) => then already explore and know the connexity of it fragment
					if (iConnexiteSouth != -1) {

						//Pair creation with min first and max second
						unsigned int uiMin = min(static_cast <int> (uiConnexite), iConnexiteSouth), uiMax = max(static_cast <int> (uiConnexite), iConnexiteSouth);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add in the storage vector
						vpuiGPCVoisinPrimal.push_back(puiPair);
					}
				}
			}
		}

		if (!vbDirection[2]) { //West Face
			//For each voxel on the face (limited to proven points of intersection)
			for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {

					//Voxel coos
					vector <unsigned int> vuiCoos = { vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Wrtting in the matrice, the connexity of the voxel (link with the fragment)
					maMatrice[0][vuiCoos[0]][vuiCoos[1]][vuiCoos[2]].GSLSetConnexite(uiConnexite);

					//Determine the voxel to the north and its connection
					vector <unsigned int> vuiCoosWest = { vuiCoosFragment[0] - 1, uiBoucleY + vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };
					int iConnexiteWest = maMatrice[0][vuiCoosWest[0]][vuiCoosWest[1]][vuiCoosWest[2]].GSLGetConnexite();

					//If the connexity isn't equal to -1 (initialization value) => then already explore and know the connexity of it fragment
					if (iConnexiteWest != -1) { 

						//Pair creation with min first and max second
						int uiMin = min(static_cast <int> (uiConnexite), iConnexiteWest), uiMax = max(static_cast <int> (uiConnexite), iConnexiteWest);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add in the storage vector
						vpuiGPCVoisinPrimal.push_back(puiPair);
					}
				}
			}
		}

		if (!vbDirection[3]) { //East Face
			//For each voxel on the face (limited to proven points of intersection)
			for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {
					//X + Dimension 1

					//Voxel coos
					vector <unsigned int> vuiCoos = { vuiCoosFragment[0] + vuiDimensionsFragment[0] - 1, uiBoucleY + vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Wrtting in the matrice, the connexity of the voxel (link with the fragment)
					maMatrice[0][vuiCoos[0]][vuiCoos[1]][vuiCoos[2]].GSLSetConnexite(uiConnexite);

					//Determine the voxel to the north and its connection
					vector <unsigned int> vuiCoosEast = { vuiCoosFragment[0] + vuiDimensionsFragment[0], uiBoucleY + vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };
					int iConnexiteEast = maMatrice[0][vuiCoosEast[0]][vuiCoosEast[1]][vuiCoosEast[2]].GSLGetConnexite();

					//If the connexity isn't equal to -1 (initialization value) => then already explore and know the connexity of it fragment
					if (iConnexiteEast != -1) {

						//Pair creation with min first and max second
						unsigned int uiMin = min(static_cast <int> (uiConnexite), iConnexiteEast), uiMax = max(static_cast <int> (uiConnexite), iConnexiteEast);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add in the storage vector
						vpuiGPCVoisinPrimal.push_back(puiPair);
					}
				}
			}
		}

		if (!vbDirection[4]) { //Behind Face
			//For each voxel on the face (limited to proven points of intersection)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
					//Z + dimension 3

					//Voxel coos
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], vuiCoosFragment[2] + vuiDimensionsFragment[2] - 1};

					//Wrtting in the matrice, the connexity of the voxel (link with the fragment)
					maMatrice[0][vuiCoos[0]][vuiCoos[1]][vuiCoos[2]].GSLSetConnexite(uiConnexite);

					//Determine the voxel to the north and its connection
					vector <unsigned int> vuiCoosBehind = { uiBoucleX + vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], vuiCoosFragment[2] + vuiDimensionsFragment[2] };
					int iConnexiteBehind = maMatrice[0][vuiCoosBehind[0]][vuiCoosBehind[1]][vuiCoosBehind[2]].GSLGetConnexite();

					//If the connexity isn't equal to -1 (initialization value) => then already explore and know the connexity of it fragment
					if (iConnexiteBehind != -1) {
						
						//Pair creation with min first and max second
						unsigned int uiMin = min(static_cast <int> (uiConnexite), iConnexiteBehind), uiMax = max(static_cast <int> (uiConnexite), iConnexiteBehind);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add in the storage vector
						vpuiGPCVoisinPrimal.push_back(puiPair);
					}
				}
			}
		}

		if (!vbDirection[5]) { //Front Face
			//For each voxel on the face (limited to proven points of intersection)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {

					//Voxel coos
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], vuiCoosFragment[2] };

					//Wrtting in the matrice, the connexity of the voxel (link with the fragment)
					maMatrice[0][vuiCoos[0]][vuiCoos[1]][vuiCoos[2]].GSLSetConnexite(uiConnexite);

					//Determine the voxel to the north and its connection
					vector <unsigned int> vuiCoosFront = { uiBoucleX + vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], vuiCoosFragment[2] - 1 };
					int iConnexiteFront = maMatrice[0][vuiCoosFront[0]][vuiCoosFront[1]][vuiCoosFront[2]].GSLGetConnexite();

					//If the connexity isn't equal to -1 (initialization value) => then already explore and know the connexity of it fragment
					if (iConnexiteFront != -1) {

						//Pair creation with min first and max second
						unsigned int uiMin = min(static_cast <int> (uiConnexite), iConnexiteFront), uiMax = max(static_cast <int> (uiConnexite), iConnexiteFront);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add in the storage vector
						vpuiGPCVoisinPrimal.push_back(puiPair);
					}
				}
			}
		}

		//Connexity incrementation 
		uiConnexite++;
	}

	//Delete all duplicates
	std::sort(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end());
	vpuiGPCVoisinPrimal.erase(std::unique(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end()), vpuiGPCVoisinPrimal.end());
}

/********************************************************************************************************************************************************
***** GCRDetectionVoisinV2Dicho : Method for create pairs of neighbor																				*****
*********************************************************************************************************************************************************
***** Input : vFRGLeafs : vector <CFragment> | uiTailleMin : unsigned int																			*****
***** Precondition : Nothing																														*****
***** Output : None																																	*****
***** Effects : Filled the vector vpuiGPCVoisinPrimal (attribut) of pairs of neighbors with vectors of vectors and dichotomous						*****
********************************************************************************************************************************************************/
void CGrapheCreator::GCRDetectionVoisinV2Dicho(vector <CFragment> vFRGLeafs, unsigned int uiTailleMin) {

	//Exception management : uiTailleMin = 0
	if (uiTailleMin == 0) {
		CException EXCErreur;
		EXCErreur.EXCModifierValeur(SEUIL_MIN);
		throw (EXCErreur);
	}

	//Recovery of matrice informations (dimensions)
	vector <unsigned int> vuiDimensionsMatrice = vFRGLeafs[0].FRGGetDimensionMatrice();

	//Initialize vectors of vectors to store future neighbors based on an axis
	vector <vector <std::pair<unsigned int, vector<unsigned int>>>> JonctionNorth;
	vector <vector <std::pair<unsigned int, vector<unsigned int>>>> JonctionSouth;

	for (unsigned int uiBoucle = 0; uiBoucle < vuiDimensionsMatrice[1]; uiBoucle++) {
		JonctionNorth.push_back({});
		JonctionSouth.push_back({});
	}

	//Initialize vectors of vectors to store future neighbors based on an axis
	vector <vector <std::pair<unsigned int, vector<unsigned int>>>> JonctionWest;
	vector <vector <std::pair<unsigned int, vector<unsigned int>>>> JonctionEast;

	for (unsigned int uiBoucle1 = 0; uiBoucle1 < vuiDimensionsMatrice[0]; uiBoucle1++) {
		JonctionWest.push_back({});
		JonctionEast.push_back({});
	}

	//Initialize vectors of vectors to store future neighbors based on an axis
	vector <vector <std::pair<unsigned int, vector<unsigned int>>>> JonctionBehind;
	vector <vector <std::pair<unsigned int, vector<unsigned int>>>> JonctionFront;

	for (unsigned int uiBoucle2 = 0; uiBoucle2 < vuiDimensionsMatrice[2]; uiBoucle2++) {
		JonctionBehind.push_back({});
		JonctionFront.push_back({});
	}

	//Loop on all leafs (vFRGLeafs = fragments generate with the Split) 
	for (vector<CFragment>::iterator itFRGFeuille = vFRGLeafs.begin(); itFRGFeuille != vFRGLeafs.end(); itFRGFeuille++) {

		//Recovery of fragment informations (coos and dimensions)
		vector <unsigned int> vuiCoosFragment = (*itFRGFeuille).FRGGetCoos();
		vector <unsigned int> vuiDimensionsFragment = (*itFRGFeuille).FRGGetDimensions();
		
		/* For the next part : Set Connexity */
		unsigned int uiConnexite = (*itFRGFeuille).FRGGetConnexite();
		vvuiGPCConnexite.push_back({ uiConnexite });

		//storage of fragment on the graphe
		BGLGraphe::vertex_descriptor vdVertices = boost::add_vertex((*itFRGFeuille), alGPCGraphe);
		vvdGPCVertex_Desc.push_back(vdVertices); //organisation in list (first connexity = place)

		//Using a method for detect if this fragment is on borders
		vector <bool> vbDirection = GCRVerticesOnBorder(vdVertices);

		if (!vbDirection[0]) { //North Face
			//For each voxel on the face (limited to proven points of intersection)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {

					//Voxel coos
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Search for coherence in the opposite vector (each voxel without coherence is stored for future coherence with another voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionSouth[vuiCoosFragment[1]], vuiCoos, "North_South");

					//If coherence is Found
					if (itFind != JonctionSouth[vuiCoosFragment[1]].end()) {

						//Pair creation with min first and max second
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add in the storage vector
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//delete of the coherence (limit next research)
						JonctionSouth[vuiCoosFragment[1]].erase(itFind);
					}
					else {
						//If no coherence found, store voxel in vector
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionNorth((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionNorth[vuiCoosFragment[1]], puivuiCoosJonctionNorth, "North_South");
					}
				}
			}
		}

		if (!vbDirection[1]) { //South Face
			//For each voxel on the face (limited to proven points of intersection)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {
					// Y + Dimension 2

					//Voxel coos
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], vuiCoosFragment[1] + vuiDimensionsFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Search for coherence in the opposite vector (each voxel without coherence is stored for future coherence with another voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionNorth[vuiCoosFragment[1] + vuiDimensionsFragment[1]], vuiCoos, "North_South");

					//If coherence is Found
					if (itFind != JonctionNorth[vuiCoosFragment[1] + vuiDimensionsFragment[1]].end()) {

						//Pair creation with min first and max second
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add in the storage vector
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//delete of the coherence (limit next research)
						JonctionNorth[vuiCoosFragment[1] + vuiDimensionsFragment[1]].erase(itFind);
					}
					else {
						//If no coherence found, store voxel in vector
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionSouth((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionSouth[vuiCoosFragment[1] + vuiDimensionsFragment[1]], puivuiCoosJonctionSouth, "North_South");
					}
				}
			}
		}

		if (!vbDirection[2]) { //West Face
			//For each voxel on the face (limited to proven points of intersection)
			for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {

					//Voxel coos
					vector <unsigned int> vuiCoos = { vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Search for coherence in the opposite vector (each voxel without coherence is stored for future coherence with another voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionEast[vuiCoosFragment[0]], vuiCoos, "East_West");

					//If coherence is Found
					if (itFind != JonctionEast[vuiCoosFragment[0]].end()) {

						//Pair creation with min first and max second
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add in the storage vector
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//delete of the coherence (limit next research)
						JonctionEast[vuiCoosFragment[0]].erase(itFind);
					}
					else {
						//If no coherence found, store voxel in vector
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionWest((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionWest[vuiCoosFragment[0]], puivuiCoosJonctionWest, "East_West");
					}
				}
			}
		}

		if (!vbDirection[3]) { //East Face
			//For each voxel on the face (limited to proven points of intersection)
			for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {
					//X + Dimension 1

					//Voxel coos
					vector <unsigned int> vuiCoos = { vuiCoosFragment[0] + vuiDimensionsFragment[0], uiBoucleY + vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Search for coherence in the opposite vector (each voxel without coherence is stored for future coherence with another voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionWest[vuiCoosFragment[0] + vuiDimensionsFragment[0]], vuiCoos, "East_West");

					//If coherence is Found
					if (itFind != JonctionWest[vuiCoosFragment[0] + vuiDimensionsFragment[0]].end()) {

						//Pair creation with min first and max second
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add in the storage vector
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//delete of the coherence (limit next research)
						JonctionWest[vuiCoosFragment[0] + vuiDimensionsFragment[0]].erase(itFind);
					}
					else {
						//If no coherence found, store voxel in vector
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionEast((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionEast[vuiCoosFragment[0] + vuiDimensionsFragment[0]], puivuiCoosJonctionEast, "East_West");
					}
				}
			}
		}

		if (!vbDirection[4]) { //Behind Face
			//For each voxel on the face (limited to proven points of intersection)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
					//Z + dimension 3

					//Voxel coos
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], vuiCoosFragment[2] + vuiDimensionsFragment[2] };

					//Search for coherence in the opposite vector (each voxel without coherence is stored for future coherence with another voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionFront[vuiCoosFragment[2] + vuiDimensionsFragment[2]], vuiCoos, "Front_Behind");

					//If coherence is Found
					if (itFind != JonctionFront[vuiCoosFragment[2] + vuiDimensionsFragment[2]].end()) {

						//Pair creation with min first and max second
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add in the storage vector
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//delete of the coherence (limit next research)
						JonctionFront[vuiCoosFragment[2] + vuiDimensionsFragment[2]].erase(itFind);
					}
					else {
						//If no coherence found, store voxel in vector
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionBehind((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionBehind[vuiCoosFragment[2] + vuiDimensionsFragment[2]], puivuiCoosJonctionBehind, "Front_Behind");
					}
				}
			}
		}

		if (!vbDirection[5]) { //Front Face
			//For each voxel on the face (limited to proven points of intersection)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {

					//Voxel coos
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], vuiCoosFragment[2] };

					//Search for coherence in the opposite vector (each voxel without coherence is stored for future coherence with another voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionBehind[vuiCoosFragment[2]], vuiCoos, "Front_Behind");

					//If coherence is Found
					if (itFind != JonctionBehind[vuiCoosFragment[2]].end()) {

						//Pair creation with min first and max second
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de storage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Add in the storage vector
						JonctionBehind[vuiCoosFragment[2]].erase(itFind);
					}
					else {
						//If no coherence found, store voxel in vector
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionFront((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionFront[vuiCoosFragment[2]], puivuiCoosJonctionFront, "Front_Behind");
					}
				}
			}
		}
	}

	//Delete all duplicates
	std::sort(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end());
	vpuiGPCVoisinPrimal.erase(std::unique(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end()), vpuiGPCVoisinPrimal.end());
}

/********************************************************************************************************************************************************
***** GCRDetectionVoisinDicho : Method for create pairs of neighbor																					*****
*********************************************************************************************************************************************************
***** Input : vFRGLeafs : vector <CFragment> | uiTailleMin : unsigned int																			*****
***** Precondition : Nothing																														*****
***** Output : None																																	*****
***** Effects : Filled the vector vpuiGPCVoisinPrimal (attribut) of pairs of neighbors with vectors and dichotomous									*****
********************************************************************************************************************************************************/
void CGrapheCreator::GCRDetectionVoisinDicho(vector <CFragment> vFRGLeafs, unsigned int uiTailleMin) {

	//Exception management : uiTailleMin = 0
	if (uiTailleMin == 0) {
		CException EXCErreur;
		EXCErreur.EXCModifierValeur(SEUIL_MIN);
		throw (EXCErreur);
	}

	//Initialize vectors of vectors to store future neighbors based on an axis
	vector <std::pair<unsigned int, vector<unsigned int>>> JonctionNorth;
	vector <std::pair<unsigned int, vector<unsigned int>>> JonctionSouth;
	vector <std::pair<unsigned int, vector<unsigned int>>> JonctionWest;
	vector <std::pair<unsigned int, vector<unsigned int>>> JonctionEast;
	vector <std::pair<unsigned int, vector<unsigned int>>> JonctionBehind;
	vector <std::pair<unsigned int, vector<unsigned int>>> JonctionFront;

	//Loop on all leafs (vFRGLeafs = fragments generate with the Split)
	for (vector<CFragment>::iterator itFRGFeuille = vFRGLeafs.begin(); itFRGFeuille != vFRGLeafs.end(); itFRGFeuille++) {

		//Recovery of fragment informations (coos and dimensions)
		vector <unsigned int> vuiCoosFragment = (*itFRGFeuille).FRGGetCoos();
		vector <unsigned int> vuiDimensionsFragment = (*itFRGFeuille).FRGGetDimensions();

		/* For the next part : Set Connexity */
		unsigned int uiConnexite = (*itFRGFeuille).FRGGetConnexite();
		vvuiGPCConnexite.push_back({ uiConnexite });

		//storage of fragment on the graphe
		BGLGraphe::vertex_descriptor vdVertices = boost::add_vertex((*itFRGFeuille), alGPCGraphe);
		vvdGPCVertex_Desc.push_back(vdVertices); //organisation in list (first connexity = place)

		//Using a method for detect if this fragment is on borders
		vector <bool> vbDirection = GCRVerticesOnBorder(vdVertices);

		if (!vbDirection[0]) { //North Face
			//For each voxel on the face (limited to proven points of intersection)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {

					//Voxel coos
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Search for coherence in the opposite vector (each voxel without coherence is stored for future coherence with another voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionSouth, vuiCoos, "North_South");

					//If coherence is Found
					if (itFind != JonctionSouth.end()) {

						//Pair creation with min first and max second
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add in the storage vector
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//delete of the coherence (limit next research)
						JonctionSouth.erase(itFind);
					}
					else {
						//If no coherence found, store voxel in vector
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionNorth((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionNorth, puivuiCoosJonctionNorth, "North_South");
					}
				}
			}
		}

		if (!vbDirection[1]) { //South Face
			//For each voxel on the face (limited to proven points of intersection)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {
					// Y + Dimension 2

					//Voxel coos
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], vuiCoosFragment[1] + vuiDimensionsFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Search for coherence in the opposite vector (each voxel without coherence is stored for future coherence with another voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionNorth, vuiCoos, "North_South");

					//If coherence is Found
					if (itFind != JonctionNorth.end()) {

						//Pair creation with min first and max second
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add in the storage vector
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//delete of the coherence (limit next research)
						JonctionNorth.erase(itFind);
					}
					else {
						//If no coherence found, store voxel in vector
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionSouth((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionSouth, puivuiCoosJonctionSouth, "North_South");
					}
				}
			}
		}

		if (!vbDirection[2]) { //West Face
			//For each voxel of the face (limited to confirmed intersection points)
			for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {

					//Voxel coos
					vector<unsigned int> vuiCoos = { vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Search in the opposite vector for coherence (each voxel without coherence is stored for future coherence with another voxel)
					vector<std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionEast, vuiCoos, "East_West");

					//If coherence is found
					if (itFind != JonctionEast.end()) {

						//Create a pair with the minimum as the first element (and maximum as the second element)
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add to the vector storing pairs (neighbors)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Remove coherence (reduce subsequent searches)
						JonctionEast.erase(itFind);
					}
					else {

						//If no coherence is found, store the voxel in a vector
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionWest((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionWest, puivuiCoosJonctionWest, "East_West");
					}
				}
			}
		}

		if (!vbDirection[3]) { //East Face
			//For each voxel of the face (limited to confirmed intersection points)
			for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {
					//X + Dimension 1

					//Voxel coos
					vector<unsigned int> vuiCoos = { vuiCoosFragment[0] + vuiDimensionsFragment[0], uiBoucleY + vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Search in the opposite vector for coherence (each voxel without coherence is stored for future coherence with another voxel)
					vector<std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionWest, vuiCoos, "East_West");

					//If coherence is found
					if (itFind != JonctionWest.end()) {

						//Create a pair with the minimum as the first element (and maximum as the second element)
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add to the vector storing pairs (neighbors)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Remove coherence (reduce subsequent searches)
						JonctionWest.erase(itFind);
					}
					else {
						//If no coherence is found, store the voxel in a vector
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionEast((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionEast, puivuiCoosJonctionEast, "East_West");
					}
				}
			}
		}

		if (!vbDirection[4]) { //Behind Face
			// For each voxel of the face (limited to confirmed intersection points)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
					// Z + dimension 3

					//Voxel coos
					vector<unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], vuiCoosFragment[2] + vuiDimensionsFragment[2] };

					//Search in the opposite vector for coherence (each voxel without coherence is stored for future coherence with another voxel)
					vector<std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionFront, vuiCoos, "Front_Behind");

					//If coherence is found
					if (itFind != JonctionFront.end()) {

						//Create a pair with the minimum as the first element (and maximum as the second element)
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add to the vector storing pairs (neighbors)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Remove coherence (reduce subsequent searches)
						JonctionFront.erase(itFind);
					}
					else {
						//If no coherence is found, store the voxel in a vector
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionBehind((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionBehind, puivuiCoosJonctionBehind, "Front_Behind");
					}
				}
			}
		}

		if (!vbDirection[5]) { //Front Face
			// For each voxel of the face (limited to confirmed intersection points)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {

					//Voxel coos
					vector<unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], vuiCoosFragment[2] };

					// Search in the opposite vector for coherence (each voxel without coherence is stored for future coherence with another voxel)
					vector<std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionBehind, vuiCoos, "Front_Behind");

					//If coherence is found
					if (itFind != JonctionBehind.end()) {

						//Create a pair with the minimum as the first element (and maximum as the second element)
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Add to the vector storing pairs (neighbors)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Remove coherence (reduce subsequent searches)
						JonctionBehind.erase(itFind);
					}
					else {
						//If no coherence is found, store the voxel in a vector
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionFront((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionFront, puivuiCoosJonctionFront, "Front_Behind");
					}
				}
			}
		}
	}

	//Delete all duplicates
	std::sort(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end());
	vpuiGPCVoisinPrimal.erase(std::unique(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end()), vpuiGPCVoisinPrimal.end());
}

/********************************************************************************************************************************************************
***** GCRThreadRedef : Method calling by a thread																									*****
*********************************************************************************************************************************************************
***** Input : uiConnexite1, uiConnexite2 : unsigned int | puiMinMax : std::pair <unsigned int, unsigned int> 										*****
***** Precondition : Nothing																														*****
***** Output : None																																	*****
***** Effects : Modifing Min/Max of vertices in the second connexity																				*****
********************************************************************************************************************************************************/
void CGrapheCreator::GCRThreadRedef(unsigned int uiConnexite1, unsigned int uiConnexite2, std::pair <unsigned int, unsigned int> puiMinMax) {

	//For all vertices of the other connexity, change their connectivity and Min/Max values
	for (unsigned int uiConnexe : vvuiGPCConnexite[uiConnexite2]) {

		vvuiGPCConnexite[uiConnexite1].push_back(alGPCGraphe[vvdGPCVertex_Desc[uiConnexe]].FRGGetConnexite());

		//Modifing Min/Max and connexity of fragments
		alGPCGraphe[vvdGPCVertex_Desc[uiConnexe]].FRGSetMinMax(puiMinMax);
		alGPCGraphe[vvdGPCVertex_Desc[uiConnexe]].FRGSetConnexite(uiConnexite1);

	}
}

/********************************************************************************************************************************************************
***** GCRLinkVertices : Method for link vertices in the graphe																						*****
*********************************************************************************************************************************************************
***** Input : puiPair : std::pair<unsigned int, unsigned int>												 										*****
***** Precondition : Nothing																														*****
***** Output : None																																	*****
***** Effects : Link vertices of graphe	with modification of Min/Max of each vertices required														*****
********************************************************************************************************************************************************/
void CGrapheCreator::GCRLinkVertices(std::pair<unsigned int, unsigned int> puiPair) {

	//Initialization of fragments (vertices) with storage previoulsy realized
	BGLGraphe::vertex_descriptor vdFragment1 = vvdGPCVertex_Desc[puiPair.first], vdFragment2 = vvdGPCVertex_Desc[puiPair.second];

	//Identifies min of Mins and max of Maxs
	std::pair <unsigned int, unsigned int> puiMinMax(min(alGPCGraphe[vdFragment1].FRGGetMin(), alGPCGraphe[vdFragment2].FRGGetMin()), max(alGPCGraphe[vdFragment1].FRGGetMax(), alGPCGraphe[vdFragment2].FRGGetMax()));

	/* Update ofvertices in the same part */

	unsigned int uiConnexite1 = min(alGPCGraphe[vdFragment1].FRGGetConnexite(), alGPCGraphe[vdFragment2].FRGGetConnexite());
	unsigned int uiConnexite2 = max(alGPCGraphe[vdFragment1].FRGGetConnexite(), alGPCGraphe[vdFragment2].FRGGetConnexite());

	//if vertices isn't in the same part
	if (uiConnexite1 != uiConnexite2) {

		//Determines connexity with most and least vertices => change connexity for least vertices
		if (vvuiGPCConnexite[uiConnexite1].size() < vvuiGPCConnexite[uiConnexite2].size()) {
			unsigned int uiConnexiteTMP = uiConnexite1;
			uiConnexite1 = uiConnexite2;
			uiConnexite2 = uiConnexiteTMP;
		}

		//Create a copy of the vector to avoid thread interference
		vector <unsigned int> vuiGPCConnexiteSave = vvuiGPCConnexite[uiConnexite1];

		//Calling of the thread method
		std::thread ThreadConnexite = thread(&CGrapheCreator::GCRThreadRedef, this, uiConnexite1, uiConnexite2, puiMinMax);

		//Modifing Min/Max of fragments
		for (unsigned int uiConnexe : vuiGPCConnexiteSave) {
			alGPCGraphe[vvdGPCVertex_Desc[uiConnexe]].FRGSetMinMax(puiMinMax);
		}

		//Waitting thread
		ThreadConnexite.join();
	}

	//Add edges between this to vertices
	boost::add_edge(vdFragment1, vdFragment2, alGPCGraphe);
}

/********************************************************************************************************************************************************
***** GCRBestCompatibility : Method for find the best neighbor pair																					*****
*********************************************************************************************************************************************************
***** Entrée : puipuiFacteurFusionnable : std::pair<unsigned int, std::pair<unsigned int, unsigned int>> &											*****
*****		   puiPair : std::pair<unsigned int, unsigned int> & | uiHomogeneite : unsigned int														*****
***** Precondition : Nothing																														*****
***** Output : None																																	*****
***** Effects : Find the best compatibility of a neighbor pair																						*****
********************************************************************************************************************************************************/
void CGrapheCreator::GCRBestCompatibility(std::pair<unsigned int, std::pair<unsigned int, unsigned int>> & puipuiFacteurFusionnable, std::pair<unsigned int, unsigned int> & puiPair, unsigned int uiHomogeneite) {

	//Recovering fragments
	BGLGraphe::vertex_descriptor vdFragment1 = vvdGPCVertex_Desc[puiPair.first], vdFragment2 = vvdGPCVertex_Desc[puiPair.second];

	//Calculation of Min/Max difference
	unsigned int uiDiffMax = std::abs(static_cast<int>(alGPCGraphe[vdFragment1].FRGGetMax() - alGPCGraphe[vdFragment2].FRGGetMax()));
	unsigned int uiDiffMin = std::abs(static_cast<int>(alGPCGraphe[vdFragment1].FRGGetMin() - alGPCGraphe[vdFragment2].FRGGetMin()));

	//If these differences respect homogeneity
	if (uiDiffMax <= uiHomogeneite && uiDiffMin <= uiHomogeneite) {

		/* Determines the best compatibility factor => the lower the uiCompatibilite, the higher the mergeability factor */
		unsigned int uiCompatibilite = uiDiffMax + uiDiffMin;

		//Compare with the best or Check in the case of a tie to make a choice
		unsigned int uiSommeBestBest = puipuiFacteurFusionnable.second.first + puipuiFacteurFusionnable.second.second;
		unsigned int uiSommePaire = puiPair.first + puiPair.second;

			
		if ((puipuiFacteurFusionnable.first > uiCompatibilite) || (puipuiFacteurFusionnable.first == uiCompatibilite && uiSommeBestBest > uiSommePaire)) {

			//Remplace the best
			puipuiFacteurFusionnable = std::pair<unsigned int, std::pair<unsigned int, unsigned int>>(uiCompatibilite, puiPair);

		}
	}
}

/********************************************************************************************************************************************************
***** GCRThreadForMerge : Method for start each threads																								*****
*********************************************************************************************************************************************************
***** Entrée : puipuiFacteurFusionnable : std::pair<unsigned int, std::pair<unsigned int, unsigned int>> &											*****
*****		   puiPair : std::pair<unsigned int, unsigned int> & | uiHomogeneite, uiDebut, uiFin : unsigned int										*****
***** Precondition : Nothing																														*****
***** Output : None																																	*****
***** Effects : Starting each thread for reduce analyze time																						*****
********************************************************************************************************************************************************/
void CGrapheCreator::GCRThreadForMerge(std::pair<unsigned int, std::pair<unsigned int, unsigned int>> & puipuiFacteurFusionnable, unsigned int uiHomogeneite, unsigned int uiDebut, unsigned int uiFin) {
	
	//Initialization of the storage of the best pair
	std::pair<unsigned int, std::pair<unsigned int, unsigned int>> puipuiInit(std::numeric_limits<unsigned int>::max(), std::pair<unsigned int, unsigned int>());
	std::pair<unsigned int, std::pair<unsigned int, unsigned int>> localBest(puipuiInit);

	//Start the comparaison
	for (vector<std::pair<unsigned int, unsigned int>>::iterator itpuiPair = vpuiGPCVoisinPrimal.begin() + uiDebut; itpuiPair != vpuiGPCVoisinPrimal.begin() + uiFin; ++itpuiPair) {
		GCRBestCompatibility(localBest, (*itpuiPair), uiHomogeneite);
	}

	/* At the end, mutex for compare all threads */
	{
		std::lock_guard<std::mutex> lock(GPCMutex);

		//Storage for comparaison
		unsigned int uiSommeBestBest = puipuiFacteurFusionnable.second.first + puipuiFacteurFusionnable.second.second;
		unsigned int uiSommeLocalBestBest = localBest.second.first + localBest.second.second;

		/* Comparaison between other threads and this one */
		if ((localBest.first < puipuiFacteurFusionnable.first) || (localBest.first == puipuiFacteurFusionnable.first && uiSommeBestBest > uiSommeLocalBestBest)) {
			puipuiFacteurFusionnable = localBest;
		}
	}
}

/********************************************************************************************************************************************************
***** GCRMerge : Method for merge neighbor																											*****
*********************************************************************************************************************************************************
***** Entrée : uiHomogeneite : unsigned int																											*****
***** Precondition : Nothing																														*****
***** Output : None																																	*****
***** Effects : Merging neighbors																													*****
********************************************************************************************************************************************************/
void CGrapheCreator::GCRMerge(unsigned int uiHomogeneite) {

	//Initialization of the storage the most fusionable neighbor pair
	std::pair<unsigned int, std::pair<unsigned int, unsigned int>> puipuiInit(std::numeric_limits<unsigned int>::max(), std::pair<unsigned int, unsigned int>());
	std::pair<unsigned int, std::pair<unsigned int, unsigned int>> puipuiFacteurFusionnable(puipuiInit);

	unsigned int uiNbFusion = 0;
	while (vpuiGPCVoisinPrimal.size() != 0) {

		//For each neighbor pairs
		for (std::pair<unsigned int, unsigned int> puiPair : vpuiGPCVoisinPrimal) {

			//With Homogeneity, analyzes each pair
			GCRBestCompatibility(puipuiFacteurFusionnable, puiPair, uiHomogeneite);
		}

		/* Verification if a new better mergeability factor has been found */
		if (puipuiFacteurFusionnable == puipuiInit) { //if no better is found
			break;
		}

		//Merge PART => with method
		GCRLinkVertices(puipuiFacteurFusionnable.second);

		//remove the pair that just been merge
		vpuiGPCVoisinPrimal.erase(std::remove(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end(), puipuiFacteurFusionnable.second), vpuiGPCVoisinPrimal.end());

		//Re-Initialize the best
		puipuiFacteurFusionnable = puipuiInit;

		uiNbFusion++;
	}

	std::cout << "Nombre de Fusion : " << uiNbFusion << std::endl;
}

/********************************************************************************************************************************************************
***** GCRMergeThread : Method for merge neighbor with threads																						*****
*********************************************************************************************************************************************************
***** Entrée : uiHomogeneite : unsigned int																											*****
***** Precondition : Nothing																														*****
***** Output : None																																	*****
***** Effects : Merging neighbors with threads																										*****
********************************************************************************************************************************************************/
void CGrapheCreator::GCRMergeThread(unsigned int uiHomogeneite) {

	//Initialization of the storage the most fusionable neighbor pair
	std::pair<unsigned int, std::pair<unsigned int, unsigned int>> puipuiInit(std::numeric_limits<unsigned int>::max(), std::pair<unsigned int, unsigned int>());
	std::pair<unsigned int, std::pair<unsigned int, unsigned int>> puipuiFacteurFusionnable(puipuiInit);

	unsigned int uiNbFusion = 0;
	while (vpuiGPCVoisinPrimal.size() != 0) {

		const unsigned int totalSize = (unsigned int)vpuiGPCVoisinPrimal.size();

		if (totalSize < 5000) { //If the size of vector is lower than 5000 => no threads (slow)

			//For each neighbor pairs
			for (std::pair<unsigned int, unsigned int> puiPair : vpuiGPCVoisinPrimal) {

				//With Homogeneity, analyzes each pair
				GCRBestCompatibility(puipuiFacteurFusionnable, puiPair, uiHomogeneite);
			}
		}
		else {
			const unsigned int chunkSize = (unsigned int)(vpuiGPCVoisinPrimal.size() + 1) / 4; //Division of the work part
			const unsigned int numThreads = (totalSize + chunkSize - 1) / chunkSize; //Calcul of the size for each vector

			//threads storage
			std::vector<std::thread> threads;

			//For each thread
			for (unsigned int uiBoucle = 0; uiBoucle < numThreads; ++uiBoucle) {

				unsigned int start = uiBoucle * chunkSize;
				unsigned int end = (uiBoucle + 1) * chunkSize;

				//For the rest 
				if (end > totalSize) {
					end = totalSize;
				}

				//Start of the thread
				threads.emplace_back(&CGrapheCreator::GCRThreadForMerge, this, std::ref(puipuiFacteurFusionnable), uiHomogeneite, start, end);
			}

			//Waitting the end of all threads
			for (std::thread & Thread : threads) {
				Thread.join();
			}
		}

		/* Verification if a new better mergeability factor has been found */
		if (puipuiFacteurFusionnable == puipuiInit) { //if no better is found
			break;
		}

		//Merge PART => with method
		GCRLinkVertices(puipuiFacteurFusionnable.second);

		//remove the pair that just been merge
		vpuiGPCVoisinPrimal.erase(std::remove(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end(), puipuiFacteurFusionnable.second), vpuiGPCVoisinPrimal.end());

		//Re-Initialize the best
		puipuiFacteurFusionnable = puipuiInit;

		uiNbFusion++;
	}

	std::cout << "Nombre de Fusion : " << uiNbFusion << std::endl;
}

/********************************************************************************************************************************************************
***** GCRMergeSansChoix : Method for merge without choice																							*****
*********************************************************************************************************************************************************
***** Entrée : uiHomogeneite : unsigned int																											*****
***** Precondition : Nothing																														*****
***** Output : None																																	*****
***** Effects : Merging neighbors with choice 																										*****
********************************************************************************************************************************************************/
void CGrapheCreator::GCRMergeSansChoix(unsigned int uiHomogeneite) {

	//recovery of fragments
	BGLGraphe::vertex_descriptor vdFragment1, vdFragment2;

	//Initialization of the storage the most fusionable neighbor pair
	std::pair<unsigned int, unsigned int> puiInit (0, 0);
	std::pair<unsigned int, unsigned int> puiVoisinFusionnable (puiInit);

	unsigned int uiNbFusion = 0;
	while (vpuiGPCVoisinPrimal.size() != 0) {
		//For each neighbor pairs
		for (std::pair<unsigned int, unsigned int> puiPair : vpuiGPCVoisinPrimal) {

			//recovery of fragments
			vdFragment1 = vvdGPCVertex_Desc[puiPair.first], vdFragment2 = vvdGPCVertex_Desc[puiPair.second];

			//Calcul Min/Max difference
			unsigned int uiDiffMax = std::abs(static_cast<int>(alGPCGraphe[vdFragment1].FRGGetMax() - alGPCGraphe[vdFragment2].FRGGetMax()));
			unsigned int uiDiffMin = std::abs(static_cast<int>(alGPCGraphe[vdFragment1].FRGGetMin() - alGPCGraphe[vdFragment2].FRGGetMin()));

			//if difference respect homogenity
			if (uiDiffMax <= uiHomogeneite && uiDiffMin <= uiHomogeneite) {
				puiVoisinFusionnable = puiPair;
				break; //take the first one
			}
		}

		/* Verification if a new better mergeability factor has been found */
		if (puiVoisinFusionnable == puiInit) { //if no better is found
			break;
		}

		//Merge PART => with method
		GCRLinkVertices(puiVoisinFusionnable);

		//remove the pair that just been merge
		vpuiGPCVoisinPrimal.erase(std::remove(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end(), puiVoisinFusionnable), vpuiGPCVoisinPrimal.end());

		//Re-Initialize the best
		puiVoisinFusionnable = puiInit;

		uiNbFusion++;
	}

	std::cout << "Nombre de Fusion : " << uiNbFusion << std::endl;
}

/********************************************************************************************************************************************************
***** GCRCreationGraphe : Method for create graphe from leafs generated by the Split																*****
*********************************************************************************************************************************************************
***** Entrée : vFRGLeafs : vector <CFragment> | uiHomogeneite, uiTailleMin, uiVersionNeighbor, uiVersionMerge : unsigned int						*****
***** Precondition : Nothing																														*****
***** Output : None																																	*****
***** Effects : Create graphe from leafs generated by the Split 																					*****
********************************************************************************************************************************************************/
void CGrapheCreator::GCRCreationGraphe(vector <CFragment> vFRGLeafs, unsigned int uiHomogeneite, unsigned int uiTailleMin, unsigned int uiVersionNeighBor, unsigned int uiVersionMerge) {

	if (vFRGLeafs.size() == 0) {
		throw (CException(NO_LEAFS));
	}

	clock_t cTempsVoisin =  clock();

	if (uiVersionNeighBor == 0) {
		GCRDetectionVoisinVoxel(vFRGLeafs, uiTailleMin);
	}
	else if (uiVersionNeighBor == 1) {
		GCRDetectionVoisinV2Dicho(vFRGLeafs, uiTailleMin);
	}
	else if (uiVersionNeighBor == 2) {
		GCRDetectionVoisinDicho(vFRGLeafs, uiTailleMin);
	}
	else throw (CException(UNDIFIED_VERSION));

	clock_t cVoisin = clock() - cTempsVoisin;
	std::cout << "Temps de la recherche voisin : " << (double)cVoisin / CLOCKS_PER_SEC << std::endl;
	std::cout << "nombre de voisins : " << vpuiGPCVoisinPrimal.size() << std::endl;

	std::cout << "MERGE TIME : " << std::endl;

	BGLGraphe saveGraphe = alGPCGraphe;
	vector <vector <unsigned int>> vvuiConnexiteSave = vvuiGPCConnexite;
	vector <std::pair<unsigned int, unsigned int>> vpuiGPCVoisinPrimalSave = vpuiGPCVoisinPrimal;

	clock_t cTempsV1 = clock();

	if (uiVersionMerge != -1) {
		cout << "MERGE " << endl;
		GCRMerge(uiHomogeneite);
	}
	else throw (CException(UNDIFIED_VERSION));

	clock_t cMerge2 = clock() - cTempsV1;

	std::cout << "Temps de la merge : " << (double)cMerge2 / CLOCKS_PER_SEC << std::endl << std::endl;

	alGPCGraphe = saveGraphe;
	vvuiGPCConnexite = vvuiConnexiteSave;
	vpuiGPCVoisinPrimal = vpuiGPCVoisinPrimalSave;

	clock_t cTempsV1Thread = clock();

	if (uiVersionMerge != -1) {
		cout << "MERGE THREAD " << endl;
		//GCRMergeThread(uiHomogeneite);
	}
	else throw (CException(UNDIFIED_VERSION));

	clock_t cMergeThread = clock() - cTempsV1Thread;

	std::cout << "Temps de la merge thread : " << (double)cMergeThread / CLOCKS_PER_SEC << std::endl << std::endl;

	alGPCGraphe = saveGraphe;
	vvuiGPCConnexite = vvuiConnexiteSave;
	vpuiGPCVoisinPrimal = vpuiGPCVoisinPrimalSave;

	clock_t cTempsSansChoix = clock();

	if (uiVersionMerge != -1) {
		cout << "MERGE Sans Choix " << endl;
		GCRMergeSansChoix(uiHomogeneite);
	}
	else throw (CException(UNDIFIED_VERSION));

	clock_t cMergeSansChoix = clock() - cTempsSansChoix;

	std::cout << "Temps de la merge sans choix : " << (double)cMergeSansChoix / CLOCKS_PER_SEC << std::endl << std::endl;
}