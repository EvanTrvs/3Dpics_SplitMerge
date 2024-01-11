#pragma once 

#include <time.h>
#include "CGrapheCreator.h"

/************************************************************************************************************************************************
***** CGRAPHESCREATOR : Constructeur par d�faut de la classe CGraphesCreator																*****
*************************************************************************************************************************************************
***** Entr�e : Aucun Param�tre d'entr�e																										*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : Aucun �l�ment retourn�																										*****
***** Entraine : Initialise alGPCGraphe, vvdGPCVertex_Desc et vvuiGPCConnexite � null														*****
************************************************************************************************************************************************/
CGrapheCreator::CGrapheCreator() {
	alGPCGraphe = BGLGraphe();

	vvdGPCVertex_Desc = {};
	vvuiGPCConnexite = {};
}

/************************************************************************************************************************************************
***** GCRGETGRAPHE : Accesseur en lecture de alGPCGraphe																					*****
*************************************************************************************************************************************************
***** Entr�e : Aucun Param�tre d'entr�e																										*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : alGPCGraphe : BGLGraphe																										*****
***** Entraine : Retourne la variable alGPCGraphe																							*****
************************************************************************************************************************************************/
BGLGraphe CGrapheCreator::GCRGetGraphe() {
	return alGPCGraphe;
}

/************************************************************************************************************************************************
***** GCRTHREADREDEF : M�thode appel� par un thread																							*****
*************************************************************************************************************************************************
***** Entr�e : uiConnexite1, uiConnexite2 : unsigned int | puiMinMax : std::pair <unsigned int, unsigned int> 								*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : Aucun �l�ment retourn�																										*****
***** Entraine : Modifie le Min/Max des sommets pr�sent dans la second connexit�															*****
************************************************************************************************************************************************/
void CGrapheCreator::GCRThreadRedef(unsigned int uiConnexite1, unsigned int uiConnexite2, std::pair <unsigned int, unsigned int> puiMinMax) {

	//Pour tous les sommets de l'autre connexit�, modification de leur connexit� ainsi que leurs Min/Max
	for (unsigned int uiConnexe : vvuiGPCConnexite[uiConnexite2]) {

		vvuiGPCConnexite[uiConnexite1].push_back(alGPCGraphe[vvdGPCVertex_Desc[uiConnexe]].FRGGetConnexite());

		alGPCGraphe[vvdGPCVertex_Desc[uiConnexe]].FRGSetMinMax(puiMinMax);
		alGPCGraphe[vvdGPCVertex_Desc[uiConnexe]].FRGSetConnexite(uiConnexite1);

	}
}

/************************************************************************************************************************************************
***** GCRLINKVERTICES : M�thode liant 2 fragments du graphe																					*****
*************************************************************************************************************************************************
***** Entr�e : puiPair : std::pair<unsigned int, unsigned int>																				*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : Aucun �l�ment retourn�																										*****
***** Entraine : Relie les Sommets en modifiant si besoin la connexit�																		*****
************************************************************************************************************************************************/
void CGrapheCreator::GCRLinkVertices(std::pair<unsigned int, unsigned int> puiPair) {

	//Initialisation des fragments (vertex) � l'aide du stockage pr�c�demment r�alis�
	BGLGraphe::vertex_descriptor vdFragment1 = vvdGPCVertex_Desc[puiPair.first], vdFragment2 = vvdGPCVertex_Desc[puiPair.second];
	
	//D�termine le Min des mins et le Max des maxs
	std::pair <unsigned int, unsigned int> puiMinMax(min(alGPCGraphe[vdFragment1].FRGGetMin(), alGPCGraphe[vdFragment2].FRGGetMin()), max(alGPCGraphe[vdFragment1].FRGGetMax(), alGPCGraphe[vdFragment2].FRGGetMax()));
	
	/* Mise � jour de toute la partie connexe */

	unsigned int uiConnexite1 = min (alGPCGraphe[vdFragment1].FRGGetConnexite(), alGPCGraphe[vdFragment2].FRGGetConnexite());
	unsigned int uiConnexite2 = max (alGPCGraphe[vdFragment1].FRGGetConnexite(), alGPCGraphe[vdFragment2].FRGGetConnexite());

	//Si les 2 sommets n'appartiennent pas � la m�me connexit�
	if (uiConnexite1 != uiConnexite2) {

		//D�termine la connexit� avec le plus et le moins de sommets => changement de connexit� pour les moins nombreux
		if (vvuiGPCConnexite[uiConnexite1].size() < vvuiGPCConnexite[uiConnexite2].size()) {
			unsigned int uiConnexiteTMP = uiConnexite1;
			uiConnexite1 = uiConnexite2;
			uiConnexite2 = uiConnexiteTMP;
		}

		//Cr�ation d'une copie du vecteur pour �viter les interf�rences du thread
		vector <unsigned int> vuiGPCConnexiteSave = vvuiGPCConnexite[uiConnexite1];

		//Appel de la m�thode de la classe en thread
		std::thread ThreadConnexite = thread(&CGrapheCreator::GCRThreadRedef, this, uiConnexite1, uiConnexite2, puiMinMax);
		
		//Red�finition du Min/Max des Sommets
		for (unsigned int uiConnexe : vuiGPCConnexiteSave) {
			alGPCGraphe[vvdGPCVertex_Desc[uiConnexe]].FRGSetMinMax(puiMinMax);
		}

		//Attente de la fin du thread
		ThreadConnexite.join();
	}

	//Ajout de l'arc entre les 2 sommets voisins
	boost::add_edge(vdFragment1, vdFragment2, alGPCGraphe);
}

/********************************************************************************************************************************************************
***** LECTUREDICHOTOMIE : Fonction permettant la lecture dichotomique																				*****
*********************************************************************************************************************************************************
***** Entr�e : vpuivuiJonction : vector <std::pair<unsigned int, vector<unsigned int>>>	& | vuiCoos : vector <unsigned int>	| sOrientation : string	*****
***** N�cessite : Ne n�cessite rien																													*****
***** Sortie : itvvuiVoisin : vector <std::pair<unsigned int, vector<unsigned int>>>::iterator														*****
***** Entraine : Retourne l'it�rateur du vecteur correspondant au voisin d'un voxel																	*****
********************************************************************************************************************************************************/
vector <std::pair<unsigned int, vector<unsigned int>>>::iterator LectureDichotomie (vector <std::pair<unsigned int, vector<unsigned int>>> & vpuivuiJonction, vector <unsigned int> vuiCoos, string sOrientation) {

	//Initialise les bornes du vecteur
	unsigned int uiBorneInf = 0;
	unsigned int uiBorneSup = (unsigned int)vpuivuiJonction.size();

	if (uiBorneInf == uiBorneSup) { //Liste Vide
		return vpuivuiJonction.end();
	}

	//Initialisation des �l�ments n�cessaire � la recherche
	unsigned int uiIndice;
	std::pair<unsigned int, vector<unsigned int>> puivuiComparaison;

	unsigned int uiSommeXZ = vuiCoos[0] + vuiCoos[2];
	unsigned int uiSommeYZ = vuiCoos[1] + vuiCoos[2];
	unsigned int uiSommeXY = vuiCoos[0] + vuiCoos[1];

	//Pour les faces Nord et Sud
	if (sOrientation == "North_South") { //Regard sur X et Z 
		while (uiBorneInf != uiBorneSup) {

			uiIndice = (uiBorneInf + uiBorneSup) / 2; //Indice du milieu de la section analys� pr�c�demment
			puivuiComparaison = vpuivuiJonction[uiIndice]; //Valeur de ce milieu

			//Si les 2 valeurs sont �gales => stop
			if (vpuivuiJonction[uiBorneInf].second[0] + vpuivuiJonction[uiBorneInf].second[2] == vpuivuiJonction[uiBorneSup - 1].second[0] + vpuivuiJonction[uiBorneSup - 1].second[2]) {
				break;
			}

			/* SINON */

			//Analyse partie Gauche
			if (puivuiComparaison.second[0] + puivuiComparaison.second[2] > uiSommeXZ) {
				uiBorneSup = uiIndice;
			}
			else { //Analyse partie Droite
				uiBorneInf = uiIndice + 1;
			}
		}

		//Possibilit� d'�galit� donc parcours de ces derni�res
		for (vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFinded = vpuivuiJonction.begin(); itFinded != vpuivuiJonction.end(); itFinded++) {
			if ((*itFinded).second == vuiCoos) {
				return itFinded;
			}
		}

		//Aucun �l�ment trouv�
		return vpuivuiJonction.end();
	}

	//Pour les faces Est et West
	else if (sOrientation == "East_West") { //Regard sur Y et Z
		while (uiBorneInf != uiBorneSup) {

			uiIndice = (uiBorneInf + uiBorneSup) / 2; //Indice du milieu de la section analys� pr�c�demment
			puivuiComparaison = vpuivuiJonction[uiIndice]; //Valeur de ce milieu

			//Si les 2 valeurs sont �gales => stop
			if (vpuivuiJonction[uiBorneInf].second[1] + vpuivuiJonction[uiBorneInf].second[2] == vpuivuiJonction[uiBorneSup - 1].second[1] + vpuivuiJonction[uiBorneSup - 1].second[2]) {
				break;
			}

			/* SINON */

			//Analyse partie Gauche
			if (puivuiComparaison.second[1] + puivuiComparaison.second[2] > uiSommeYZ) {
				uiBorneSup = uiIndice;
			}
			else { //Analyse partie Droite
				uiBorneInf = uiIndice + 1;
			}
		}

		//Possibilit� d'�galit� donc parcours de ces derni�res
		for (vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFinded = vpuivuiJonction.begin(); itFinded != vpuivuiJonction.end(); itFinded++) {
			if ((*itFinded).second == vuiCoos) {
				return itFinded;
			}
		}

		//Aucun �l�ment trouv�
		return vpuivuiJonction.end();

	}

	//Pour les faces Behind et Front
	else { //Regard sur X et Y
		while (uiBorneInf != uiBorneSup) {

			uiIndice = (uiBorneInf + uiBorneSup) / 2; //Indice du milieu de la section analys� pr�c�demment
			puivuiComparaison = vpuivuiJonction[uiIndice]; //Valeur de ce milieu

			//Si les 2 valeurs sont �gales => stop
			if (vpuivuiJonction[uiBorneInf].second[0] + vpuivuiJonction[uiBorneInf].second[1] == vpuivuiJonction[uiBorneSup - 1].second[0] + vpuivuiJonction[uiBorneSup - 1].second[1]) {
				break;
			}

			/* SINON */

			//Analyse partie Gauche
			if (puivuiComparaison.second[0] + puivuiComparaison.second[1] > uiSommeXY) {
				uiBorneSup = uiIndice;
			}
			else { //Analyse partie Droite
				uiBorneInf = uiIndice + 1;
			}
		}

		//Possibilit� d'�galit� donc parcours de ces derni�res
		for (vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFinded = vpuivuiJonction.begin(); itFinded != vpuivuiJonction.end(); itFinded++) {
			if ((*itFinded).second == vuiCoos) {
				return itFinded;
			}
		}

		//Aucun �l�ment trouv�
		return vpuivuiJonction.end();
	}
}

/****************************************************************************************************************************************************************************************
***** ECRITUREDICHOTOMIE : Fonction permettant l'�criture dichotomique																												*****
*****************************************************************************************************************************************************************************************
***** Entr�e : vpuivuiJonction : vector <std::pair<unsigned int, vector<unsigned int>>>	& | puivuiNewPair : std::pair<unsigned int, vector<unsigned int>>	| sOrientation : string	*****
***** N�cessite : Ne n�cessite rien																																					*****
***** Sortie : Ne retourne aucun �l�ment																																			*****
***** Entraine : Ecrit dans le vecteur le voxel (pour le retrouver gr�ce � la lecture)																								*****
****************************************************************************************************************************************************************************************/
void EcritureDichotomie(vector <std::pair<unsigned int, vector<unsigned int>>> & vpuivuiJonction, std::pair<unsigned int, vector<unsigned int>> puivuiNewPair, string sOrientation) {

	//Initialise les bornes du vecteur
	unsigned int uiBorneInf = 0;
	unsigned int uiBorneSup = (unsigned int)vpuivuiJonction.size();

	if (uiBorneInf == uiBorneSup) { //Liste Vide
		vpuivuiJonction.push_back(puivuiNewPair);
		return;
	}

	//Initialisation des �l�ments n�cessaire � la recherche
	unsigned int uiIndice;
	std::pair<unsigned int, vector<unsigned int>> puivuiComparaison;

	unsigned int uiSommeXZ = puivuiNewPair.second[0] + puivuiNewPair.second[2];
	unsigned int uiSommeYZ = puivuiNewPair.second[1] + puivuiNewPair.second[2];
	unsigned int uiSommeXY = puivuiNewPair.second[0] + puivuiNewPair.second[1];

	//Pour les faces Nord et Sud
	if (sOrientation == "North_South") { //regard sur X et Z 
		while (uiBorneInf != uiBorneSup) {

			uiIndice = (uiBorneInf + uiBorneSup) / 2; //Indice du milieu de la section analys� pr�c�demment
			puivuiComparaison = vpuivuiJonction[uiIndice]; //Valeur de ce milieu

			//Future Ecriture dans la partie Gauche
			if (puivuiComparaison.second[0] + puivuiComparaison.second[2] > uiSommeXZ) {
				uiBorneSup = uiIndice;
			}
			else { //Future Ecriture dans la partie Droite
				uiBorneInf = uiIndice + 1;
			}
		}

		//Ecriture
		vpuivuiJonction.insert(vpuivuiJonction.begin() + uiBorneInf, puivuiNewPair);
	}

	//Pour les faces Est et West
	else if (sOrientation == "East_West") {//Regard sur Y et Z
		while (uiBorneInf != uiBorneSup) {

			uiIndice = (uiBorneInf + uiBorneSup) / 2; //Indice du milieu de la section analys� pr�c�demment
			puivuiComparaison = vpuivuiJonction[uiIndice]; //Valeur de ce milieu

			//Future Ecriture dans la partie Gauche
			if (puivuiComparaison.second[1] + puivuiComparaison.second[2] > uiSommeYZ) {
				uiBorneSup = uiIndice;
			}
			else { //Future Ecriture dans la partie Droite
				uiBorneInf = uiIndice + 1;
			}
		}

		//Ecriture
		vpuivuiJonction.insert(vpuivuiJonction.begin() + uiBorneInf, puivuiNewPair);
	}

	//Pour les faces Behind et Front
	else { //Regard sur X et Y
		while (uiBorneInf != uiBorneSup) {

			uiIndice = (uiBorneInf + uiBorneSup) / 2; //Indice du milieu de la section analys� pr�c�demment
			puivuiComparaison = vpuivuiJonction[uiIndice]; //Valeur de ce milieu

			//Future Ecriture dans la partie Gauche
			if (puivuiComparaison.second[0] + puivuiComparaison.second[1] > uiSommeXY) {
				uiBorneSup = uiIndice;
			}
			else { //Future Ecriture dans la partie Droite
				uiBorneInf = uiIndice + 1;
			}
		}

		//Ecriture
		vpuivuiJonction.insert(vpuivuiJonction.begin() + uiBorneInf, puivuiNewPair);
	}
}

/************************************************************************************************************************************************
***** GCRVERTICEONBORDER : M�thode d�terminant la pr�sence d'un fragment au bord de la matrice												*****
*************************************************************************************************************************************************
***** Entr�e : vdVertice : BGLGraphe::vertex_descriptor																						*****
***** N�cessite : Doit exister dans le graphe                                                                                               *****
***** Sortie : vbDirection : vector <bool>																									*****
***** Entraine : D�termine la pr�sence d'un fragment au bord de la matrice																	*****
************************************************************************************************************************************************/
vector <bool> CGrapheCreator::GCRVerticesOnBorder(BGLGraphe::vertex_descriptor vdVertices) {

	//R�cup�ration du Fragment ainsi que ces coordonn�es
	CFragment FRGLastVertice = alGPCGraphe[vdVertices];
	vector <unsigned int> vuiCoosFragment = FRGLastVertice.FRGGetCoos();

	vector <bool> vbDirection = {false, false, false, false, false, false};

	//D�termine � partir des coordonn�es et des dimensions du fragment, la proximit� ou non d'un bord
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

	//Retourne le vecteur de bool�en
	return vbDirection;
}

/************************************************************************************************************************************************************************
***** GCRDETECTIONVOISINVOXEL : M�thode d�terminant la liste des voisins � l'aide des voxels																		*****
*************************************************************************************************************************************************************************
***** Entr�e : vFRGLeafs : vector <CFragment> | uiTailleMin : unsigned int | vpuiLeafs : vector <vector <std::pair<unsigned int, unsigned int>>> &					*****
***** N�cessite : Ne n�cessite rien																																	*****
***** Sortie : Aucun �l�ment retourn�																																*****
***** Entraine : D�termine les voisins � partir de la liste des feuilles du Split																					*****
************************************************************************************************************************************************************************/
void CGrapheCreator::GCRDetectionVoisinVoxel(vector <CFragment> vFRGLeafs, unsigned int uiTailleMin) {

	//Gestion de l'exception : Taille min = 0
	if (uiTailleMin == 0) {
		CException EXCErreur;
		EXCErreur.EXCModifierValeur(SEUIL_MIN);
		throw (EXCErreur);
	}

	std::cout << "DETECTIN VOISIN V3 Voxel" << std::endl << std::endl;

	//R�cup�ration des dimensions de la matrice et de la matrice
	vector <unsigned int> vuiDimensionsMatrice = vFRGLeafs[0].FRGGetDimensionMatrice();
	boost::multi_array <CGrayScale, 3> * maMatrice = vFRGLeafs[0].FRGGetMatrice();

	//Boucle sur toutes les feuilles 
	unsigned int uiConnexite = 0;
	for (vector<CFragment>::iterator itFRGFeuille = vFRGLeafs.begin(); itFRGFeuille != vFRGLeafs.end(); itFRGFeuille++) {

		//R�cup�ration des coordonn�es et des dimensions du fragment
		vector <unsigned int> vuiCoosFragment = (*itFRGFeuille).FRGGetCoos();
		vector <unsigned int> vuiDimensionsFragment = (*itFRGFeuille).FRGGetDimensions();

		/* Pour la suite : Set de la connexit� du fragment */
		(*itFRGFeuille).FRGSetConnexite(uiConnexite);
		vvuiGPCConnexite.push_back({ uiConnexite });

		//Stockage de tous les fragments dans un graphe
		BGLGraphe::vertex_descriptor vdVertices = boost::add_vertex((*itFRGFeuille), alGPCGraphe);
		vvdGPCVertex_Desc.push_back(vdVertices); //descriptor dans l'ordre des num�ros des Fragments

		//Calcul si le fragment est sur l'un des bords (pas de d�tection des voisins)
		vector <bool> vbDirection = GCRVerticesOnBorder(vdVertices);

		if (!vbDirection[0]) { //North -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Ecriture dans la matrice de la connexit� du Voxel (li� � la connexit� du fragment)
					maMatrice[0][vuiCoos[0]][vuiCoos[1]][vuiCoos[2]].GSLSetConnexite(uiConnexite);

					//D�termine le fragment au Nord de ce dernier ainsi que sa connexit�
					vector <unsigned int> vuiCoosNorth = { uiBoucleX + vuiCoosFragment[0], vuiCoosFragment[1] - 1, uiBoucleZ + vuiCoosFragment[2] };
					int iConnexiteNorth = maMatrice[0][vuiCoosNorth[0]][vuiCoosNorth[1]][vuiCoosNorth[2]].GSLGetConnexite();

					//Si la connexit� n'est pas �gale � -1 (valeur d'initialisation) => alors d�j� explorer et poss�de la connexit� de son fragment
					if (iConnexiteNorth != -1) {
						
						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(static_cast <int> (uiConnexite), iConnexiteNorth), uiMax = max(static_cast <int> (uiConnexite), iConnexiteNorth);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);
					}
				}
			}
		}

		if (!vbDirection[1]) { //South -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {
					// Y + Dimension 2

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], vuiCoosFragment[1] + vuiDimensionsFragment[1] - 1, uiBoucleZ + vuiCoosFragment[2] };

					//Ecriture dans la matrice de la connexit� du Voxel (li� � la connexit� du fragment)
					maMatrice[0][vuiCoos[0]][vuiCoos[1]][vuiCoos[2]].GSLSetConnexite(uiConnexite);

					//D�termine le fragment au Sud de ce dernier ainsi que sa connexit�
					vector <unsigned int> vuiCoosSouth = { uiBoucleX + vuiCoosFragment[0], vuiCoosFragment[1] + vuiDimensionsFragment[1], uiBoucleZ + vuiCoosFragment[2] }; //Voxel au Sud
					int iConnexiteSouth = maMatrice[0][vuiCoosSouth[0]][vuiCoosSouth[1]][vuiCoosSouth[2]].GSLGetConnexite();

					//Si la connexit� n'est pas �gale � -1 (valeur d'initialisation) => alors d�j� explorer et poss�de la connexit� de son fragment
					if (iConnexiteSouth != -1) {

						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(static_cast <int> (uiConnexite), iConnexiteSouth), uiMax = max(static_cast <int> (uiConnexite), iConnexiteSouth);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);
					}
				}
			}
		}

		if (!vbDirection[2]) { //West -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Ecriture dans la matrice de la connexit� du Voxel (li� � la connexit� du fragment)
					maMatrice[0][vuiCoos[0]][vuiCoos[1]][vuiCoos[2]].GSLSetConnexite(uiConnexite);

					//D�termine le fragment � l'West de ce dernier ainsi que sa connexit�
					vector <unsigned int> vuiCoosWest = { vuiCoosFragment[0] - 1, uiBoucleY + vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] }; //Voxel � l'Ouest
					int iConnexiteWest = maMatrice[0][vuiCoosWest[0]][vuiCoosWest[1]][vuiCoosWest[2]].GSLGetConnexite();

					//Si la connexit� n'est pas �gale � -1 (valeur d'initialisation) => alors d�j� explorer et poss�de la connexit� de son fragment
					if (iConnexiteWest != -1) { 
						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						int uiMin = min(static_cast <int> (uiConnexite), iConnexiteWest), uiMax = max(static_cast <int> (uiConnexite), iConnexiteWest);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);
					}
				}
			}
		}

		if (!vbDirection[3]) { //East -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {
					//X + Dimension 1

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { vuiCoosFragment[0] + vuiDimensionsFragment[0] - 1, uiBoucleY + vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Ecriture dans la matrice de la connexit� du Voxel (li� � la connexit� du fragment)
					maMatrice[0][vuiCoos[0]][vuiCoos[1]][vuiCoos[2]].GSLSetConnexite(uiConnexite);

					//D�termine le fragment � l'East de ce dernier ainsi que sa connexit�
					vector <unsigned int> vuiCoosEast = { vuiCoosFragment[0] + vuiDimensionsFragment[0], uiBoucleY + vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] }; //Voxel � L'est
					int iConnexiteEast = maMatrice[0][vuiCoosEast[0]][vuiCoosEast[1]][vuiCoosEast[2]].GSLGetConnexite();

					//Si la connexit� n'est pas �gale � -1 (valeur d'initialisation) => alors d�j� explorer et poss�de la connexit� de son fragment
					if (iConnexiteEast != -1) {
						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(static_cast <int> (uiConnexite), iConnexiteEast), uiMax = max(static_cast <int> (uiConnexite), iConnexiteEast);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);
					}
				}
			}
		}

		if (!vbDirection[4]) { //Behind -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
					//Z + dimension 3

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], vuiCoosFragment[2] + vuiDimensionsFragment[2] - 1};

					//Ecriture dans la matrice de la connexit� du Voxel (li� � la connexit� du fragment)
					maMatrice[0][vuiCoos[0]][vuiCoos[1]][vuiCoos[2]].GSLSetConnexite(uiConnexite);

					//D�termine le fragment au Behind de ce dernier ainsi que sa connexit�
					vector <unsigned int> vuiCoosBehind = { uiBoucleX + vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], vuiCoosFragment[2] + vuiDimensionsFragment[2] }; //Voxel Devant
					int iConnexiteBehind = maMatrice[0][vuiCoosBehind[0]][vuiCoosBehind[1]][vuiCoosBehind[2]].GSLGetConnexite();

					//Si la connexit� n'est pas �gale � -1 (valeur d'initialisation) => alors d�j� explorer et poss�de la connexit� de son fragment
					if (iConnexiteBehind != -1) {
						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(static_cast <int> (uiConnexite), iConnexiteBehind), uiMax = max(static_cast <int> (uiConnexite), iConnexiteBehind);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);
					}
				}
			}
		}

		if (!vbDirection[5]) { //Front -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], vuiCoosFragment[2] };

					//Ecriture dans la matrice de la connexit� du Voxel (li� � la connexit� du fragment)
					maMatrice[0][vuiCoos[0]][vuiCoos[1]][vuiCoos[2]].GSLSetConnexite(uiConnexite);

					//D�termine le fragment au Front de ce dernier ainsi que sa connexit�
					vector <unsigned int> vuiCoosFront = { uiBoucleX + vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], vuiCoosFragment[2] - 1 }; //Voxel Devant
					int iConnexiteFront = maMatrice[0][vuiCoosFront[0]][vuiCoosFront[1]][vuiCoosFront[2]].GSLGetConnexite();

					//Si la connexit� n'est pas �gale � -1 (valeur d'initialisation) => alors d�j� explorer et poss�de la connexit� de son fragment
					if (iConnexiteFront != -1) {
						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(static_cast <int> (uiConnexite), iConnexiteFront), uiMax = max(static_cast <int> (uiConnexite), iConnexiteFront);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);
					}
				}
			}
		}

		//Incr�mentation de la connexit�
		uiConnexite++;
	}

	//Suppression de tous les doublons
	std::sort(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end());
	vpuiGPCVoisinPrimal.erase(std::unique(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end()), vpuiGPCVoisinPrimal.end());
}

/************************************************************************************************************************************************************************
***** GCRDETECTIONVOISINV2DICHO : M�thode d�terminant la liste des voisins en utilisant des vecteurs de vecteur et une dichotomie									*****
*************************************************************************************************************************************************************************
***** Entr�e : vFRGLeafs : vector <CFragment> | uiTailleMin : unsigned int | vpuiLeafs : vector <vector <std::pair<unsigned int, unsigned int>>> &					*****
***** N�cessite : Ne n�cessite rien																																	*****
***** Sortie : Aucun �l�ment retourn�																																*****
***** Entraine : D�termine les voisins � partir de la liste des feuilles du Split																					*****
************************************************************************************************************************************************************************/
void CGrapheCreator::GCRDetectionVoisinV2Dicho(vector <CFragment> vFRGLeafs, unsigned int uiTailleMin) {

	//Gestion de l'exception : Taille min = 0
	if (uiTailleMin == 0) {
		CException EXCErreur;
		EXCErreur.EXCModifierValeur(SEUIL_MIN);
		throw (EXCErreur);
	}

	cout << "DETECTION VOISIN V2 DICHOTOMIQUE (VECTEUR DE VECTEUR)" << endl << endl;

	//R�cup�ration des dimensions de la matrice
	vector <unsigned int> vuiDimensionsMatrice = vFRGLeafs[0].FRGGetDimensionMatrice();

	//Initialisation des vecteurs de vecteurs pour stocker les futurs voisins en fonction d'un axe
	vector <vector <std::pair<unsigned int, vector<unsigned int>>>> JonctionNorth;
	vector <vector <std::pair<unsigned int, vector<unsigned int>>>> JonctionSouth;

	for (unsigned int uiBoucle = 0; uiBoucle < vuiDimensionsMatrice[1]; uiBoucle++) {
		JonctionNorth.push_back({});
		JonctionSouth.push_back({});
	}

	//Initialisation des vecteurs de vecteurs pour stocker les futurs voisins en fonction d'un axe
	vector <vector <std::pair<unsigned int, vector<unsigned int>>>> JonctionWest;
	vector <vector <std::pair<unsigned int, vector<unsigned int>>>> JonctionEast;

	for (unsigned int uiBoucle1 = 0; uiBoucle1 < vuiDimensionsMatrice[0]; uiBoucle1++) {
		JonctionWest.push_back({});
		JonctionEast.push_back({});
	}

	//Initialisation des vecteurs de vecteurs pour stocker les futurs voisins en fonction d'un axe
	vector <vector <std::pair<unsigned int, vector<unsigned int>>>> JonctionBehind;
	vector <vector <std::pair<unsigned int, vector<unsigned int>>>> JonctionFront;

	for (unsigned int uiBoucle2 = 0; uiBoucle2 < vuiDimensionsMatrice[2]; uiBoucle2++) {
		JonctionBehind.push_back({});
		JonctionFront.push_back({});
	}

	//Boucle sur toutes les feuilles 
	for (vector<CFragment>::iterator itFRGFeuille = vFRGLeafs.begin(); itFRGFeuille != vFRGLeafs.end(); itFRGFeuille++) {

		//R�cup�ration des coordonn�es et des dimensions du fragment
		vector <unsigned int> vuiCoosFragment = (*itFRGFeuille).FRGGetCoos();
		vector <unsigned int> vuiDimensionsFragment = (*itFRGFeuille).FRGGetDimensions();
		
		/* Pour la suite : Set de la connexit� du fragment */
		unsigned int uiConnexite = (*itFRGFeuille).FRGGetConnexite();
		vvuiGPCConnexite.push_back({ uiConnexite });

		//Stockage de tous les fragments dans un graphe
		BGLGraphe::vertex_descriptor vdVertices = boost::add_vertex((*itFRGFeuille), alGPCGraphe);
		vvdGPCVertex_Desc.push_back(vdVertices); //descriptor dans l'ordre des num�ros des Fragments

		//Calcul si le fragment est sur l'un des bords (pas de d�tection des voisins)
		vector <bool> vbDirection = GCRVerticesOnBorder(vdVertices);

		if (!vbDirection[0]) { //North -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Recherche dans le vecteur oppos� une coh�rence (chaque voxel sans coh�rence est stock� pour une futur coh�rence avec un autre voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionSouth[vuiCoosFragment[1]], vuiCoos, "North_South");

					//Si une coh�rence est trouv�e
					if (itFind != JonctionSouth[vuiCoosFragment[1]].end()) {

						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Suppression de la coh�rence (diminuer les recherches suivantes)
						JonctionSouth[vuiCoosFragment[1]].erase(itFind);
					}
					else {
						//Si aucune coh�rence trouv�e, stock le voxel dans un vecteur
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionNorth((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionNorth[vuiCoosFragment[1]], puivuiCoosJonctionNorth, "North_South");
					}
				}
			}
		}

		if (!vbDirection[1]) { //South -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {
					// Y + Dimension 2

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], vuiCoosFragment[1] + vuiDimensionsFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Recherche dans le vecteur oppos� une coh�rence (chaque voxel sans coh�rence est stock� pour une futur coh�rence avec un autre voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionNorth[vuiCoosFragment[1] + vuiDimensionsFragment[1]], vuiCoos, "North_South");

					//Si une coh�rence est trouv�e
					if (itFind != JonctionNorth[vuiCoosFragment[1] + vuiDimensionsFragment[1]].end()) {

						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Suppression de la coh�rence (diminuer les recherches suivantes)
						JonctionNorth[vuiCoosFragment[1] + vuiDimensionsFragment[1]].erase(itFind);
					}
					else {
						//Si aucune coh�rence trouv�e, stock le voxel dans un vecteur
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionSouth((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionSouth[vuiCoosFragment[1] + vuiDimensionsFragment[1]], puivuiCoosJonctionSouth, "North_South");
					}
				}
			}
		}

		if (!vbDirection[2]) { //West -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Recherche dans le vecteur oppos� une coh�rence (chaque voxel sans coh�rence est stock� pour une futur coh�rence avec un autre voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionEast[vuiCoosFragment[0]], vuiCoos, "East_West");

					//Si une coh�rence est trouv�e
					if (itFind != JonctionEast[vuiCoosFragment[0]].end()) {

						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Suppression de la coh�rence (diminuer les recherches suivantes)
						JonctionEast[vuiCoosFragment[0]].erase(itFind);
					}
					else {
						//Si aucune coh�rence trouv�e, stock le voxel dans un vecteur
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionWest((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionWest[vuiCoosFragment[0]], puivuiCoosJonctionWest, "East_West");
					}
				}
			}
		}

		if (!vbDirection[3]) { //East -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {
					//X + Dimension 1

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { vuiCoosFragment[0] + vuiDimensionsFragment[0], uiBoucleY + vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Recherche dans le vecteur oppos� une coh�rence (chaque voxel sans coh�rence est stock� pour une futur coh�rence avec un autre voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionWest[vuiCoosFragment[0] + vuiDimensionsFragment[0]], vuiCoos, "East_West");

					//Si une coh�rence est trouv�e
					if (itFind != JonctionWest[vuiCoosFragment[0] + vuiDimensionsFragment[0]].end()) {

						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Suppression de la coh�rence (diminuer les recherches suivantes)
						JonctionWest[vuiCoosFragment[0] + vuiDimensionsFragment[0]].erase(itFind);
					}
					else {
						//Si aucune coh�rence trouv�e, stock le voxel dans un vecteur
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionEast((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionEast[vuiCoosFragment[0] + vuiDimensionsFragment[0]], puivuiCoosJonctionEast, "East_West");
					}
				}
			}
		}

		if (!vbDirection[4]) { //Behind -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
					//Z + dimension 3

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], vuiCoosFragment[2] + vuiDimensionsFragment[2] };

					//Recherche dans le vecteur oppos� une coh�rence (chaque voxel sans coh�rence est stock� pour une futur coh�rence avec un autre voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionFront[vuiCoosFragment[2] + vuiDimensionsFragment[2]], vuiCoos, "Front_Behind");

					//Si une coh�rence est trouv�e
					if (itFind != JonctionFront[vuiCoosFragment[2] + vuiDimensionsFragment[2]].end()) {

						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Suppression de la coh�rence (diminuer les recherches suivantes)
						JonctionFront[vuiCoosFragment[2] + vuiDimensionsFragment[2]].erase(itFind);
					}
					else {
						//Si aucune coh�rence trouv�e, stock le voxel dans un vecteur
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionBehind((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionBehind[vuiCoosFragment[2] + vuiDimensionsFragment[2]], puivuiCoosJonctionBehind, "Front_Behind");
					}
				}
			}
		}

		if (!vbDirection[5]) { //Front -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], vuiCoosFragment[2] };

					//Recherche dans le vecteur oppos� une coh�rence (chaque voxel sans coh�rence est stock� pour une futur coh�rence avec un autre voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionBehind[vuiCoosFragment[2]], vuiCoos, "Front_Behind");

					//Si une coh�rence est trouv�e
					if (itFind != JonctionBehind[vuiCoosFragment[2]].end()) {

						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Suppression de la coh�rence (diminuer les recherches suivantes)
						JonctionBehind[vuiCoosFragment[2]].erase(itFind);
					}
					else {
						//Si aucune coh�rence trouv�e, stock le voxel dans un vecteur
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionFront((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionFront[vuiCoosFragment[2]], puivuiCoosJonctionFront, "Front_Behind");
					}
				}
			}
		}
	}

	//Suppression de tous les doublons
	std::sort(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end());
	vpuiGPCVoisinPrimal.erase(std::unique(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end()), vpuiGPCVoisinPrimal.end());
}

/************************************************************************************************************************************************************************
***** GCRDETECTIONVOISINDICHO : M�thode d�terminant la liste des voisins en utilisant des vecteurs et une dichotomie												*****
*************************************************************************************************************************************************************************
***** Entr�e : vFRGLeafs : vector <CFragment> | uiTailleMin : unsigned int | vpuiLeafs : vector <vector <std::pair<unsigned int, unsigned int>>> &					*****
***** N�cessite : Ne n�cessite rien																																	*****
***** Sortie : Aucun �l�ment retourn�																																*****
***** Entraine : D�termine les voisins � partir de la liste des feuilles du Split																					*****
************************************************************************************************************************************************************************/
void CGrapheCreator::GCRDetectionVoisinDicho(vector <CFragment> vFRGLeafs, unsigned int uiTailleMin) {

	//Gestion de l'exception : Taille min = 0
	if (uiTailleMin == 0) {
		CException EXCErreur;
		EXCErreur.EXCModifierValeur(SEUIL_MIN);
		throw (EXCErreur);
	}

	cout << "DETECTION VOISIN V1 DICHOTOMIQUE" << endl << endl;

	//Pr�paration des vectors n�cessaires aux calculs des voisins
	vector <std::pair<unsigned int, vector<unsigned int>>> JonctionNorth;
	vector <std::pair<unsigned int, vector<unsigned int>>> JonctionSouth;
	vector <std::pair<unsigned int, vector<unsigned int>>> JonctionWest;
	vector <std::pair<unsigned int, vector<unsigned int>>> JonctionEast;
	vector <std::pair<unsigned int, vector<unsigned int>>> JonctionBehind;
	vector <std::pair<unsigned int, vector<unsigned int>>> JonctionFront;

	//Boucle parcourant toutes les feuiles
	for (vector<CFragment>::iterator itFRGFeuille = vFRGLeafs.begin(); itFRGFeuille != vFRGLeafs.end(); itFRGFeuille++) {

		//R�cup�ration des coordonn�es et des dimensions du fragment
		vector <unsigned int> vuiCoosFragment = (*itFRGFeuille).FRGGetCoos();
		vector <unsigned int> vuiDimensionsFragment = (*itFRGFeuille).FRGGetDimensions();

		/* Pour la suite : Set de la connexit� du fragment */
		unsigned int uiConnexite = (*itFRGFeuille).FRGGetConnexite();
		vvuiGPCConnexite.push_back({ uiConnexite });

		//Stockage de tous les fragments dans un graphe
		BGLGraphe::vertex_descriptor vdVertices = boost::add_vertex((*itFRGFeuille), alGPCGraphe);
		vvdGPCVertex_Desc.push_back(vdVertices); //descriptor dans l'ordre des num�ros des Fragments

		//Calcul si le fragment est sur l'un des bords (pas de d�tection des voisins)
		vector <bool> vbDirection = GCRVerticesOnBorder(vdVertices);

		if (!vbDirection[0]) { //North -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Recherche dans le vecteur oppos� une coh�rence (chaque voxel sans coh�rence est stock� pour une futur coh�rence avec un autre voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionSouth, vuiCoos, "North_South");

					//Si une coh�rence est trouv�e
					if (itFind != JonctionSouth.end()) {

						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Suppression de la coh�rence (diminuer les recherches suivantes)
						JonctionSouth.erase(itFind);
					}
					else {
						//Si aucune coh�rence trouv�e, stock le voxel dans un vecteur
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionNorth((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionNorth, puivuiCoosJonctionNorth, "North_South");
					}
				}
			}
		}

		if (!vbDirection[1]) { //South -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {
					// Y + Dimension 2

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], vuiCoosFragment[1] + vuiDimensionsFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Recherche dans le vecteur oppos� une coh�rence (chaque voxel sans coh�rence est stock� pour une futur coh�rence avec un autre voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionNorth, vuiCoos, "North_South");

					//Si une coh�rence est trouv�e
					if (itFind != JonctionNorth.end()) {

						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Suppression de la coh�rence (diminuer les recherches suivantes)
						JonctionNorth.erase(itFind);
					}
					else {

						//Si aucune coh�rence trouv�e, stock le voxel dans un vecteur
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionSouth((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionSouth, puivuiCoosJonctionSouth, "North_South");
					}
				}
			}
		}

		if (!vbDirection[2]) { //West -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Recherche dans le vecteur oppos� une coh�rence (chaque voxel sans coh�rence est stock� pour une futur coh�rence avec un autre voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionEast, vuiCoos, "East_West");

					//Si une coh�rence est trouv�e
					if (itFind != JonctionEast.end()) {

						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Suppression de la coh�rence (diminuer les recherches suivantes)
						JonctionEast.erase(itFind);
					}
					else {

						//Si aucune coh�rence trouv�e, stock le voxel dans un vecteur
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionWest((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionWest, puivuiCoosJonctionWest, "East_West");
					}
				}
			}
		}

		if (!vbDirection[3]) { //East -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
				for (unsigned int uiBoucleZ = 0; uiBoucleZ < vuiDimensionsFragment[2]; uiBoucleZ += uiTailleMin) {
					//X + Dimension 1

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { vuiCoosFragment[0] + vuiDimensionsFragment[0], uiBoucleY + vuiCoosFragment[1], uiBoucleZ + vuiCoosFragment[2] };

					//Recherche dans le vecteur oppos� une coh�rence (chaque voxel sans coh�rence est stock� pour une futur coh�rence avec un autre voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionWest, vuiCoos, "East_West");

					//Si une coh�rence est trouv�e
					if (itFind != JonctionWest.end()) {

						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Suppression de la coh�rence (diminuer les recherches suivantes)
						JonctionWest.erase(itFind);
					}
					else {
						//Si aucune coh�rence trouv�e, stock le voxel dans un vecteur
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionEast((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionEast, puivuiCoosJonctionEast, "East_West");
					}
				}
			}
		}

		if (!vbDirection[4]) { //Behind -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {
					//Z + dimension 3

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], vuiCoosFragment[2] + vuiDimensionsFragment[2] };

					//Recherche dans le vecteur oppos� une coh�rence (chaque voxel sans coh�rence est stock� pour une futur coh�rence avec un autre voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionFront, vuiCoos, "Front_Behind");

					//Si une coh�rence est trouv�e
					if (itFind != JonctionFront.end()) {

						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Suppression de la coh�rence (diminuer les recherches suivantes)
						JonctionFront.erase(itFind);
					}
					else {
						//Si aucune coh�rence trouv�e, stock le voxel dans un vecteur
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionBehind((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionBehind, puivuiCoosJonctionBehind, "Front_Behind");
					}
				}
			}
		}

		if (!vbDirection[5]) { //Front -> pas au bord
			//Pour chaque voxels de la face (limit� aux points d'intersection av�r�s)
			for (unsigned int uiBoucleX = 0; uiBoucleX < vuiDimensionsFragment[0]; uiBoucleX += uiTailleMin) {
				for (unsigned int uiBoucleY = 0; uiBoucleY < vuiDimensionsFragment[1]; uiBoucleY += uiTailleMin) {

					//Coordonn�es du Voxel
					vector <unsigned int> vuiCoos = { uiBoucleX + vuiCoosFragment[0], uiBoucleY + vuiCoosFragment[1], vuiCoosFragment[2] };

					//Recherche dans le vecteur oppos� une coh�rence (chaque voxel sans coh�rence est stock� pour une futur coh�rence avec un autre voxel)
					vector <std::pair<unsigned int, vector<unsigned int>>>::iterator itFind = LectureDichotomie(JonctionBehind, vuiCoos, "Front_Behind");

					//Si une coh�rence est trouv�e
					if (itFind != JonctionBehind.end()) {

						//Cr�ation d'une pair avec le min en 1er �l�ment (et max en 2nd �l�ment)
						unsigned int uiMin = min(uiConnexite, (*itFind).first), uiMax = max(uiConnexite, (*itFind).first);
						std::pair<unsigned int, unsigned int> puiPair(uiMin, uiMax);

						//Ajout dans le vecteur de stockage des pairs (de voisins)
						vpuiGPCVoisinPrimal.push_back(puiPair);

						//Suppression de la coh�rence (diminuer les recherches suivantes)
						JonctionBehind.erase(itFind);
					}
					else {
						//Si aucune coh�rence trouv�e, stock le voxel dans un vecteur
						std::pair<unsigned int, vector<unsigned int>> puivuiCoosJonctionFront((*itFRGFeuille).FRGGetConnexite(), vuiCoos);
						EcritureDichotomie(JonctionFront, puivuiCoosJonctionFront, "Front_Behind");
					}
				}
			}
		}
	}


	//Suppression de tous les doublons
	std::sort(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end());
	vpuiGPCVoisinPrimal.erase(std::unique(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end()), vpuiGPCVoisinPrimal.end());
}

/********************************************************************************************************************************************************************************************
***** GCRBESTCOMPATIBILITY : M�thode d�terminant les 2 meilleurs compatibilit� entre 2 fragments voisins																				*****
*********************************************************************************************************************************************************************************************
***** Entr�e : ppuipuiFacteurFusionnable : std::pair<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>, std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> &  *****
*****		   puiPair : std::pair<unsigned int, unsigned int> & | uiHomogeneite : unsigned int																							*****
***** N�cessite : Ne n�cessite rien																																						*****
***** Sortie : Aucun �l�ment retourn�																																					*****
***** Entraine : D�terminant les 2 meilleurs compatibilit� entre 2 fragments voisins																									*****
********************************************************************************************************************************************************************************************/
void CGrapheCreator::GCRBestCompatibility(std::pair<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>, std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> & ppuipuiFacteurFusionnable, std::pair<unsigned int, unsigned int> & puiPair, unsigned int uiHomogeneite) {

	//R�cup�ration des fragments
	BGLGraphe::vertex_descriptor vdFragment1 = vvdGPCVertex_Desc[puiPair.first], vdFragment2 = vvdGPCVertex_Desc[puiPair.second];

	//Calcul de la diff�rence des Mins et Maxs
	unsigned int uiDiffMax = std::abs(static_cast<int>(alGPCGraphe[vdFragment1].FRGGetMax() - alGPCGraphe[vdFragment2].FRGGetMax()));
	unsigned int uiDiffMin = std::abs(static_cast<int>(alGPCGraphe[vdFragment1].FRGGetMin() - alGPCGraphe[vdFragment2].FRGGetMin()));

	//Si ces diff�rences respectent l'homog�n�it�
	if (uiDiffMax <= uiHomogeneite && uiDiffMin <= uiHomogeneite) {

		/* D�termine le meilleur facteur de compatibilit� => plus uiCompatibilite est faible plus facteur de fusionnabilit� est grand */
		unsigned int uiCompatibilite = uiDiffMax + uiDiffMin;

		//En cas d'�galit�, choix d�finie arbitrairement et non al�atoirement
		unsigned int uiSommeBestBest = ppuipuiFacteurFusionnable.first.second.first + ppuipuiFacteurFusionnable.first.second.second;
		unsigned int uiSommeBestSecond = ppuipuiFacteurFusionnable.second.second.first + ppuipuiFacteurFusionnable.second.second.second;
		unsigned int uiSommePaire = puiPair.first + puiPair.second;

		//Compare avec le meilleur ou V�rifie dans le cas d'une �galit� pour faire un choix
		if ((ppuipuiFacteurFusionnable.first.first > uiCompatibilite) || (ppuipuiFacteurFusionnable.first.first == uiCompatibilite && uiSommeBestBest > uiSommePaire)) {

			//Le meilleur devient le second meilleur et remplace le meilleur
			ppuipuiFacteurFusionnable.second = ppuipuiFacteurFusionnable.first;
			ppuipuiFacteurFusionnable.first = std::pair<unsigned int, std::pair<unsigned int, unsigned int>>(uiCompatibilite, puiPair);

		}
		//Sinon compare le second meilleur
		else if (puiPair != ppuipuiFacteurFusionnable.first.second) {
			if ((ppuipuiFacteurFusionnable.second.first > uiCompatibilite) || (ppuipuiFacteurFusionnable.second.first == uiCompatibilite && uiSommeBestSecond > uiSommePaire)) {

				//Remplace le second meilleur
				ppuipuiFacteurFusionnable.second = std::pair<unsigned int, std::pair<unsigned int, unsigned int>>(uiCompatibilite, puiPair);
			}
		}
	}
}

/********************************************************************************************************************************************************************************************
***** GCRTHREADFORMERGE : M�thode lan�ant tous les threads afin de les comparer																											*****
*********************************************************************************************************************************************************************************************
***** Entr�e : ppuipuiFacteurFusionnable : std::pair<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>, std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> &  *****
*****		   puiPair : std::pair<unsigned int, unsigned int> & | uiHomogeneite : unsigned int																							*****
***** N�cessite : Ne n�cessite rien																																						*****
***** Sortie : Aucun �l�ment retourn�																																					*****
***** Entraine : Lance tous les threads afin de les comparer																															*****
********************************************************************************************************************************************************************************************/
void CGrapheCreator::GCRThreadForMerge(std::pair<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>, std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> & ppuipuiFacteurFusionnable, unsigned int uiHomogeneite, unsigned int uiDebut, unsigned int uiFin) {
	
	//Initialisation de la pair des meilleurs facteur de fusionnabilit�
	std::pair<unsigned int, std::pair<unsigned int, unsigned int>> puipuiInit(std::numeric_limits<unsigned int>::max(), std::pair<unsigned int, unsigned int>());
	std::pair<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>, std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> localBest(puipuiInit, puipuiInit);

	//Lancement des meilleures paires
	for (vector<std::pair<unsigned int, unsigned int>>::iterator itpuiPair = vpuiGPCVoisinPrimal.begin() + uiDebut; itpuiPair != vpuiGPCVoisinPrimal.begin() + uiFin; ++itpuiPair) {
		GCRBestCompatibility(localBest, (*itpuiPair), uiHomogeneite);
	}

	/* Comparaison de tous les threads */
	{
		std::lock_guard<std::mutex> lock(GPCMutex);

		//Stockage des meilleurs locals et communs
		unsigned int uiSommeBestBest = ppuipuiFacteurFusionnable.first.second.first + ppuipuiFacteurFusionnable.first.second.second;
		unsigned int uiSommeBestSecond = ppuipuiFacteurFusionnable.second.second.first + ppuipuiFacteurFusionnable.second.second.second;
		unsigned int uiSommeLocalBestBest = localBest.first.second.first + localBest.first.second.second;
		unsigned int uiSommeLocalBestSecond = localBest.second.second.first + localBest.second.second.second;

		/* Comparaison du meilleur local */
		if ((localBest.first.first < ppuipuiFacteurFusionnable.first.first) || (localBest.first.first == ppuipuiFacteurFusionnable.first.first && uiSommeBestBest > uiSommeLocalBestBest)) {
			ppuipuiFacteurFusionnable.second = ppuipuiFacteurFusionnable.first;
			ppuipuiFacteurFusionnable.first = localBest.first;
		}
		else if (localBest.first.second != ppuipuiFacteurFusionnable.first.second) {
			if ((ppuipuiFacteurFusionnable.second.first > localBest.first.first) || (ppuipuiFacteurFusionnable.second.first == localBest.first.first && uiSommeBestSecond > uiSommeLocalBestBest)) {

				//Remplace le second meilleur
				ppuipuiFacteurFusionnable.second = localBest.first;
			}
		}

		/* Comparaison du second meilleur local */
		if ((localBest.second.first < ppuipuiFacteurFusionnable.first.first) || (localBest.second.first == ppuipuiFacteurFusionnable.first.first && uiSommeBestBest > uiSommeLocalBestSecond)) {
			ppuipuiFacteurFusionnable.second = ppuipuiFacteurFusionnable.first;
			ppuipuiFacteurFusionnable.first = localBest.second;
		}
		else if (localBest.second.second != ppuipuiFacteurFusionnable.first.second) {
			if ((ppuipuiFacteurFusionnable.second.first > localBest.second.first) || (ppuipuiFacteurFusionnable.second.first == localBest.second.first && uiSommeBestSecond > uiSommeLocalBestSecond)) {

				//Remplace le second meilleur
				ppuipuiFacteurFusionnable.second = localBest.second;
			}
		}
	}
}

/************************************************************************************************************************************************
***** GCRMERGE : M�thode fusionnant les fragments voisins																					*****
*************************************************************************************************************************************************
***** Entr�e : uiHomogeneite : unsigned int																									*****
***** N�cessite : Ne N�cesste Rien				                                                                                            *****
***** Sortie : Aucun �lement retourn�e																										*****
***** Entraine : Fusionne les fragments voisins																								*****
************************************************************************************************************************************************/
void CGrapheCreator::GCRMerge(unsigned int uiHomogeneite) {

	//Initialisation de la pair des meilleurs facteur de fusionnabilit�
	std::pair<unsigned int, std::pair<unsigned int, unsigned int>> puipuiInit(std::numeric_limits<unsigned int>::max(), std::pair<unsigned int, unsigned int>());
	std::pair<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>, std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> ppuipuiFacteurFusionnable(puipuiInit, puipuiInit);

	unsigned int uiNbFusion = 0;
	while (vpuiGPCVoisinPrimal.size() != 0) {

		for (std::pair<unsigned int, unsigned int> puiPair : vpuiGPCVoisinPrimal) {

			//Si Homog�n�it� et comparaison avec les 2 meilleurs facteur de fusionnabilit�
			GCRBestCompatibility(ppuipuiFacteurFusionnable, puiPair, uiHomogeneite);
		}

		/* Verification si un nouveau meilleur facteur de fusionnabilit� a �t� trouv� */
		if (ppuipuiFacteurFusionnable.first == puipuiInit) { //Si aucun nouveau facteur n'est trouv� 
			break;
		}

		//Merge PART -> ppuipuiFacteurFusionnable.first.second
		GCRLinkVertices(ppuipuiFacteurFusionnable.first.second); //=> Merge des voisins (du couple)

		//Supprime la pair qui vient d'�tre fusionner (link entre les 2 fragments)
		vpuiGPCVoisinPrimal.erase(std::remove(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end(), ppuipuiFacteurFusionnable.first.second), vpuiGPCVoisinPrimal.end()); //supprime de la liste des voisins

		//Remplace le meilleur (d�sormais supprimer) par le second meilleur
		ppuipuiFacteurFusionnable.first = ppuipuiFacteurFusionnable.second;
		ppuipuiFacteurFusionnable.second = puipuiInit; //R�Initialise le second

		uiNbFusion++;
	}

	std::cout << "Nombre de Fusion : " << uiNbFusion << std::endl;
}

/************************************************************************************************************************************************
***** GCRMERGETHREAD : M�thode fusionnant les fragments voisins	avec des threads															*****
*************************************************************************************************************************************************
***** Entr�e : uiHomogeneite : unsigned int																									*****
***** N�cessite : Ne N�cesste Rien				                                                                                            *****
***** Sortie : Aucun �lement retourn�e																										*****
***** Entraine : Fusionne les fragments voisins	� l'aide de threads																			*****
************************************************************************************************************************************************/
void CGrapheCreator::GCRMergeThread(unsigned int uiHomogeneite) {

	//Initialisation de la pair des meilleurs facteur de fusionnabilit�
	std::pair<unsigned int, std::pair<unsigned int, unsigned int>> puipuiInit(std::numeric_limits<unsigned int>::max(), std::pair<unsigned int, unsigned int>());
	std::pair<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>, std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> ppuipuiFacteurFusionnable(puipuiInit, puipuiInit);

	unsigned int uiNbFusion = 0;
	while (vpuiGPCVoisinPrimal.size() != 0) {

		const unsigned int totalSize = (unsigned int)vpuiGPCVoisinPrimal.size();

		if (totalSize < 5000) { //Eviter trop de sous-division qui relentissera 
			for (std::pair<unsigned int, unsigned int> puiPair : vpuiGPCVoisinPrimal) {

				//Si Homog�n�it� et comparaison avec les 2 meilleurs facteur de fusionnabilit�
				GCRBestCompatibility(ppuipuiFacteurFusionnable, puiPair, uiHomogeneite);
			}
		}
		else {
			const unsigned int chunkSize = (unsigned int)(vpuiGPCVoisinPrimal.size() + 1) / 4; //Division de la charge de travail
			const unsigned int numThreads = (totalSize + chunkSize - 1) / chunkSize; // Calcul du nombre de threads n�cessaires

			//Stockage des threads
			std::vector<std::thread> threads;

			//Division du travail
			for (unsigned int uiBoucle = 0; uiBoucle < numThreads; ++uiBoucle) {

				unsigned int start = uiBoucle * chunkSize;
				unsigned int end = (uiBoucle + 1) * chunkSize;

				//Dans le cas de la fin du vecteur -> reste
				if (end > totalSize) {
					end = totalSize;
				}

				//Lancement du thread
				threads.emplace_back(&CGrapheCreator::GCRThreadForMerge, this, std::ref(ppuipuiFacteurFusionnable), uiHomogeneite, start, end);
			}

			//Attente de la fin de tous les threads
			for (std::thread & Thread : threads) {
				Thread.join();
			}
		}

		/* Verification si un nouveau meilleur facteur de fusionnabilit� a �t� trouv� */
		if (ppuipuiFacteurFusionnable.first == puipuiInit) { //Si aucun nouveau facteur n'est trouv� 
			break;
		}

		//Merge PART -> ppuipuiFacteurFusionnable.first.second
		GCRLinkVertices(ppuipuiFacteurFusionnable.first.second); //=> Merge des voisins (du couple)

		//Supprime la pair qui vient d'�tre fusionner (link entre les 2 fragments)
		vpuiGPCVoisinPrimal.erase(std::remove(vpuiGPCVoisinPrimal.begin(), vpuiGPCVoisinPrimal.end(), ppuipuiFacteurFusionnable.first.second), vpuiGPCVoisinPrimal.end()); //supprime de la liste des voisins

		//Remplace le meilleur (d�sormais supprimer) par le second meilleur
		ppuipuiFacteurFusionnable.first = ppuipuiFacteurFusionnable.second;
		ppuipuiFacteurFusionnable.second = puipuiInit; //R�Initialise le second

		uiNbFusion++;
	}

	std::cout << "Nombre de Fusion : " << uiNbFusion << std::endl;
}

/************************************************************************************************************************************************
***** GCRCREATIONGRAPHE : M�thode pour cr�er le graphe � partir des feuilles de l'arbre														*****
*************************************************************************************************************************************************
***** Entr�e : vFRGLeafs : vector <CFragment> | uiHomogeneite : unsigned int 																*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : Aucun �l�ment retourn�																										*****
***** Entraine : Compl�te le graphe de GPCGCRGraphe 																						*****
************************************************************************************************************************************************/
void CGrapheCreator::GCRCreationGraphe(vector <CFragment> vFRGLeafs, unsigned int uiHomogeneite, unsigned int uiTailleMin, unsigned int uiVersion) {

	if (vFRGLeafs.size() == 0) {
		throw (CException(NO_LEAFS));
	}

	clock_t cTempsVoisin =  clock();

	if (uiVersion == 0) {
		GCRDetectionVoisinVoxel(vFRGLeafs, uiTailleMin);
	}
	else if (uiVersion == 1) {
		GCRDetectionVoisinV2Dicho(vFRGLeafs, uiTailleMin);
	}
	else if (uiVersion == 2) {
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

	if (uiVersion != -1) {
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

	if (uiVersion != -1) {
		cout << "MERGE THREAD " << endl;
		//GCRMergeThread(uiHomogeneite);
	}
	else throw (CException(UNDIFIED_VERSION));

	clock_t cMergeThread = clock() - cTempsV1Thread;

	std::cout << "Temps de la merge thread : " << (double)cMergeThread / CLOCKS_PER_SEC << std::endl << std::endl;
}