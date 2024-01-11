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
	***** CVOXEL : Constructeur par d�faut de la classe CVoxel																					*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																									    *****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�                                                                                                       *****
	***** Entraine : Initialise les variables vuiVXLCoos et uiVXLGroupe � "null"																*****
	************************************************************************************************************************************************/
	CVoxel();

	/************************************************************************************************************************************************
	***** CVOXEL : Constructeur de confort de la classe CVoxel																					*****
	*************************************************************************************************************************************************
	***** Entr�e : vuiCoos : vector <unsigned int> | uiVXLGroupe : unsigned int																	*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�                                                                                                       *****
	***** Entraine : Initialise les variables vuiVXLCoos et uiVXLGroupe respectivement � vuiCoos et uiGroupe									*****
	************************************************************************************************************************************************/
	CVoxel(vector <unsigned int> vuiCoos, unsigned int uiGroupe);

	/************************************************************************************************************************************************
	***** CVOXEL : Constructeur de recopie de la classe CVoxel																					*****
	*************************************************************************************************************************************************
	***** Entr�e : VXLCopieV : & CVoxel																											*****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�                                                                                                       *****
	***** Entraine : Initialise les variables vuiVXLCoos et uiVXLGroupe respectivement � celles pr�sentes chez VXLCopieV						*****
	************************************************************************************************************************************************/
	CVoxel(CVoxel const& VXLCopieV);

	/************************************************************************************************************************************************
	***** VXLGETCOOS : Accesseur en lecture de la variable vuiVXLCoos																			*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																									    *****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : vuiVXLCoos : vector <unsigned int>																							*****
	***** Entraine : Retourne le vecteur vuiVXLCoos																								*****
	************************************************************************************************************************************************/
	vector <unsigned int> VXLGetCoos();

	/************************************************************************************************************************************************
	***** VXLGETGROUPE : Accesseur en lecture de la variable uiVXLGroupe																		*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																									    *****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : uiVXLGroupe : unsigned int																									*****
	***** Entraine : Retourne l'attribut uiVXLGroupe																							*****
	************************************************************************************************************************************************/
	unsigned int VXLGetGroupe();

	/************************************************************************************************************************************************
	***** VXLGETELEMENTCOOS : Accesseur en lecture de la variable vuiVXLCoos																	*****
	*************************************************************************************************************************************************
	***** Entr�e : uiIndice : unsigned int																										*****
	***** N�cessite : L'Indice doit �tre inf�rieur ou �gale � la taille du vecteur                                                              *****
	***** Sortie : vuiVXLCoos : unsigned int																									*****
	***** Entraine : Retourne la valeur � la position de l'indice de la variable vuiVXLCoos														*****
	************************************************************************************************************************************************/
	unsigned int VXLGetElementCoos(unsigned int uiIndice);

	/************************************************************************************************************************************************
	***** VXLTOSTRING : Fonction affichant toutes les donn�es du Voxel																			*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																									    *****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�			                                                                                            *****
	***** Entraine : Affiche, sur la sortie standart, les donn�es du Voxel																		*****
	************************************************************************************************************************************************/
	void VXLToString();
};

#include "CVoxel.ipp"

#endif