#pragma once

#include <iostream>

#include "CVoxel.h"

using namespace std;

/************************************************************************************************************************************************
***** CVOXEL : Constructeur par défaut de la classe CVoxel																					*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																									    *****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné                                                                                                       *****
***** Entraine : Initialise les variables vuiVXLCoos et uiVXLGroupe à "null"																*****
************************************************************************************************************************************************/
inline CVoxel::CVoxel() {

	//Initialisation des variables à "null"
	vuiVXLCoos = {};
	uiVXLGroupe = 0;

}

/************************************************************************************************************************************************
***** CVOXEL : Constructeur de confort de la classe CVoxel																					*****
*************************************************************************************************************************************************
***** Entrée : vuiCoos : vector <unsigned int> | uiVXLGroupe : unsigned int																	*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné                                                                                                       *****
***** Entraine : Initialise les variables vuiVXLCoos et uiVXLGroupe respectivement à vuiCoos et uiGroupe									*****
************************************************************************************************************************************************/
inline CVoxel::CVoxel(vector <unsigned int> vuiCoos, unsigned int uiGroupe) {

	//La taille des vecteurs doit être égale à 3 (x,y,z) et (R,G,V)
	if (vuiCoos.size() != 3) {
		CException EXCErreur;
		EXCErreur.EXCModifierValeur(TAILLE);
		throw EXCErreur;
	}

	//Initialisation des variables respectivement aux arguments passés
	vuiVXLCoos = vuiCoos;
	uiVXLGroupe = uiGroupe;

}

/************************************************************************************************************************************************
***** CVOXEL : Constructeur de recopie de la classe CVoxel																					*****
*************************************************************************************************************************************************
***** Entrée : VXLCopieV : & CVoxel																											*****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné                                                                                                       *****
***** Entraine : Initialise les variables vuiVXLCoos et uiVXLGroupe respectivement à celles présentes chez VXLCopieV						*****
************************************************************************************************************************************************/
inline CVoxel::CVoxel(CVoxel const& VXLCopieV) {

	//Initialise les variables respectivement à celles présentes chez VXLCopieV
	vuiVXLCoos = VXLCopieV.vuiVXLCoos;
	uiVXLGroupe = VXLCopieV.uiVXLGroupe;
}

/************************************************************************************************************************************************
***** VXLGETCOOS : Accesseur en lecture de la variable vuiVXLCoos																			*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																									    *****
***** Nécessite : Ne nécessite rien                                                                                                         *****
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
***** Entrée : Aucun Paramètre d'entrée																									    *****
***** Nécessite : Ne nécessite rien                                                                                                         *****
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
***** Entrée : uiIndice : unsigned int																										*****
***** Nécessite : L'Indice doit être inférieur ou égale à la taille du vecteur                                                              *****
***** Sortie : vuiVXLCoos : unsigned int																									*****
***** Entraine : Retourne la valeur à la position de l'indice de la variable vuiVXLCoos														*****
************************************************************************************************************************************************/
inline unsigned int CVoxel::VXLGetElementCoos(unsigned int uiIndice) {

	//Si l'indice est supérieur à la taille du vecteur -> lève une exception
	if (vuiVXLCoos.size() < uiIndice) {
		CException EXCErreur;
		EXCErreur.EXCModifierValeur(TAILLE);
		throw EXCErreur;
	}

	//Dans le cas contraire, retourne l'élément à la position demandée
	return vuiVXLCoos [uiIndice];

}

/************************************************************************************************************************************************
***** VXLTOSTRING : Fonction affichant toutes les données du Voxel																			*****
*************************************************************************************************************************************************
***** Entrée : Aucun Paramètre d'entrée																									    *****
***** Nécessite : Ne nécessite rien                                                                                                         *****
***** Sortie : Aucun élément retourné			                                                                                            *****
***** Entraine : Affiche, sur la sortie standart, les données du Voxel																		*****
************************************************************************************************************************************************/
inline void CVoxel::VXLToString() {

	cout << "Les coordonnées du Voxel sont : ";

	//Vérification de la taille du vecteur (égale à 3)
	if (vuiVXLCoos.size() == 3) {
		cout << "(" << vuiVXLCoos[0] << "," << vuiVXLCoos[1] << "," << vuiVXLCoos[2] << ")" << endl;
	}
	else {
		cout << "()" << endl;
	}

	cout << "Le Groupe du Voxel est : " << uiVXLGroupe << endl;
}
