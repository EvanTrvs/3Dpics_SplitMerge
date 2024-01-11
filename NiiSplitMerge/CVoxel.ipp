#pragma once

#include <iostream>

#include "CVoxel.h"

using namespace std;

/************************************************************************************************************************************************
***** CVOXEL : Constructeur par d�faut de la classe CVoxel																					*****
*************************************************************************************************************************************************
***** Entr�e : Aucun Param�tre d'entr�e																									    *****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : Aucun �l�ment retourn�                                                                                                       *****
***** Entraine : Initialise les variables vuiVXLCoos et uiVXLGroupe � "null"																*****
************************************************************************************************************************************************/
inline CVoxel::CVoxel() {

	//Initialisation des variables � "null"
	vuiVXLCoos = {};
	uiVXLGroupe = 0;

}

/************************************************************************************************************************************************
***** CVOXEL : Constructeur de confort de la classe CVoxel																					*****
*************************************************************************************************************************************************
***** Entr�e : vuiCoos : vector <unsigned int> | uiVXLGroupe : unsigned int																	*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : Aucun �l�ment retourn�                                                                                                       *****
***** Entraine : Initialise les variables vuiVXLCoos et uiVXLGroupe respectivement � vuiCoos et uiGroupe									*****
************************************************************************************************************************************************/
inline CVoxel::CVoxel(vector <unsigned int> vuiCoos, unsigned int uiGroupe) {

	//La taille des vecteurs doit �tre �gale � 3 (x,y,z) et (R,G,V)
	if (vuiCoos.size() != 3) {
		CException EXCErreur;
		EXCErreur.EXCModifierValeur(TAILLE);
		throw EXCErreur;
	}

	//Initialisation des variables respectivement aux arguments pass�s
	vuiVXLCoos = vuiCoos;
	uiVXLGroupe = uiGroupe;

}

/************************************************************************************************************************************************
***** CVOXEL : Constructeur de recopie de la classe CVoxel																					*****
*************************************************************************************************************************************************
***** Entr�e : VXLCopieV : & CVoxel																											*****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : Aucun �l�ment retourn�                                                                                                       *****
***** Entraine : Initialise les variables vuiVXLCoos et uiVXLGroupe respectivement � celles pr�sentes chez VXLCopieV						*****
************************************************************************************************************************************************/
inline CVoxel::CVoxel(CVoxel const& VXLCopieV) {

	//Initialise les variables respectivement � celles pr�sentes chez VXLCopieV
	vuiVXLCoos = VXLCopieV.vuiVXLCoos;
	uiVXLGroupe = VXLCopieV.uiVXLGroupe;
}

/************************************************************************************************************************************************
***** VXLGETCOOS : Accesseur en lecture de la variable vuiVXLCoos																			*****
*************************************************************************************************************************************************
***** Entr�e : Aucun Param�tre d'entr�e																									    *****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : vuiVXLCoos : vector <unsigned int>																							*****
***** Entraine : Retourne le vecteur vuiVXLCoos																								*****
************************************************************************************************************************************************/
inline vector <unsigned int> CVoxel::VXLGetCoos() {

	//Retourne le vecteur vuiVXLCoos
	return vuiVXLCoos;
}

/************************************************************************************************************************************************
***** VXLGETGROUPE : Accesseur en lecture de la variable uiVXLGroupe																		*****
*************************************************************************************************************************************************
***** Entr�e : Aucun Param�tre d'entr�e																									    *****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : uiVXLGroupe : unsigned int																									*****
***** Entraine : Retourne l'attribut uiVXLGroupe																							*****
************************************************************************************************************************************************/
inline unsigned int CVoxel::VXLGetGroupe() {

	//Retourne le vecteur uiVXLGroupe
	return uiVXLGroupe;
}

/************************************************************************************************************************************************
***** VXLGETELEMENTCOOS : Accesseur en lecture de la variable vuiVXLCoos																	*****
*************************************************************************************************************************************************
***** Entr�e : uiIndice : unsigned int																										*****
***** N�cessite : L'Indice doit �tre inf�rieur ou �gale � la taille du vecteur                                                              *****
***** Sortie : vuiVXLCoos : unsigned int																									*****
***** Entraine : Retourne la valeur � la position de l'indice de la variable vuiVXLCoos														*****
************************************************************************************************************************************************/
inline unsigned int CVoxel::VXLGetElementCoos(unsigned int uiIndice) {

	//Si l'indice est sup�rieur � la taille du vecteur -> l�ve une exception
	if (vuiVXLCoos.size() < uiIndice) {
		CException EXCErreur;
		EXCErreur.EXCModifierValeur(TAILLE);
		throw EXCErreur;
	}

	//Dans le cas contraire, retourne l'�l�ment � la position demand�e
	return vuiVXLCoos [uiIndice];

}

/************************************************************************************************************************************************
***** VXLTOSTRING : Fonction affichant toutes les donn�es du Voxel																			*****
*************************************************************************************************************************************************
***** Entr�e : Aucun Param�tre d'entr�e																									    *****
***** N�cessite : Ne n�cessite rien                                                                                                         *****
***** Sortie : Aucun �l�ment retourn�			                                                                                            *****
***** Entraine : Affiche, sur la sortie standart, les donn�es du Voxel																		*****
************************************************************************************************************************************************/
inline void CVoxel::VXLToString() {

	cout << "Les coordonn�es du Voxel sont : ";

	//V�rification de la taille du vecteur (�gale � 3)
	if (vuiVXLCoos.size() == 3) {
		cout << "(" << vuiVXLCoos[0] << "," << vuiVXLCoos[1] << "," << vuiVXLCoos[2] << ")" << endl;
	}
	else {
		cout << "()" << endl;
	}

	cout << "Le Groupe du Voxel est : " << uiVXLGroupe << endl;
}
