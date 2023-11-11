#ifndef CVoxel_h
#define CVoxel_h 

#include <vector>
#include <string>

using namespace std;

#include "CException.h"

#define TAILLE 1


class CVoxel {
private:

	vector <unsigned int> vuiVXLCoos;
	unsigned int uiVXLGroupe;

public:
	/************************************************************************************************************************************************
	***** CVOXEL : Constructeur par défaut de la classe CVoxel																					*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																									    *****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné                                                                                                       *****
	***** Entraine : Initialise les variables vuiVXLCoos et uiVXLGroupe à "null"																*****
	************************************************************************************************************************************************/
	CVoxel();

	/************************************************************************************************************************************************
	***** CVOXEL : Constructeur de confort de la classe CVoxel																					*****
	*************************************************************************************************************************************************
	***** Entrée : vuiCoos : vector <unsigned int> | uiVXLGroupe : unsigned int																	*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné                                                                                                       *****
	***** Entraine : Initialise les variables vuiVXLCoos et uiVXLGroupe respectivement à vuiCoos et uiGroupe									*****
	************************************************************************************************************************************************/
	CVoxel(vector <unsigned int> vuiCoos, unsigned int uiGroupe);

	/************************************************************************************************************************************************
	***** CVOXEL : Constructeur de recopie de la classe CVoxel																					*****
	*************************************************************************************************************************************************
	***** Entrée : VXLCopieV : & CVoxel																											*****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné                                                                                                       *****
	***** Entraine : Initialise les variables vuiVXLCoos et uiVXLGroupe respectivement à celles présentes chez VXLCopieV						*****
	************************************************************************************************************************************************/
	CVoxel(CVoxel const& VXLCopieV);

	/************************************************************************************************************************************************
	***** VXLGETCOOS : Accesseur en lecture de la variable vuiVXLCoos																			*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																									    *****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : vuiVXLCoos : vector <unsigned int>																							*****
	***** Entraine : Retourne le vecteur vuiVXLCoos																								*****
	************************************************************************************************************************************************/
	vector <unsigned int> VXLGetCoos();

	/************************************************************************************************************************************************
	***** VXLGETGROUPE : Accesseur en lecture de la variable uiVXLGroupe																		*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																									    *****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : uiVXLGroupe : unsigned int																									*****
	***** Entraine : Retourne l'attribut uiVXLGroupe																							*****
	************************************************************************************************************************************************/
	unsigned int VXLGetGroupe();

	/************************************************************************************************************************************************
	***** VXLGETELEMENTCOOS : Accesseur en lecture de la variable vuiVXLCoos																	*****
	*************************************************************************************************************************************************
	***** Entrée : uiIndice : unsigned int																										*****
	***** Nécessite : L'Indice doit être inférieur ou égale à la taille du vecteur                                                              *****
	***** Sortie : vuiVXLCoos : unsigned int																									*****
	***** Entraine : Retourne la valeur à la position de l'indice de la variable vuiVXLCoos														*****
	************************************************************************************************************************************************/
	unsigned int VXLGetElementCoos(unsigned int uiIndice);

	/************************************************************************************************************************************************
	***** VXLTOSTRING : Fonction affichant toutes les données du Voxel																			*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																									    *****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné			                                                                                            *****
	***** Entraine : Affiche, sur la sortie standart, les données du Voxel																		*****
	************************************************************************************************************************************************/
	void VXLToString();
};

#include "CVoxel.ipp"

#endif