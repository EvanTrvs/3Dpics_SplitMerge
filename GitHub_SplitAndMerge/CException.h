#ifndef CException_h
#define CException_h 

#define PAS_ERREUR 0

class CException {
private:
	unsigned int uiEXCValeur;

public:
	/************************************************************************************************************************************************
	***** CEXCEPTION : Constructeur par défaut de la classe CException 																			*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																									    *****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : Aucun élément retourné																										*****
	***** Entraine : Initialise la variable uiEXCValeur																							*****
	************************************************************************************************************************************************/
	CException() {
		uiEXCValeur = PAS_ERREUR;
	}


	/************************************************************************************************************************************************
	***** EXCLIREVALEUR : Lecture de la variable uiEXCValeur 																					*****
	*************************************************************************************************************************************************
	***** Entrée : Aucun Paramètre d'entrée																									    *****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : uiEXCValeur : Unsigned Int																									*****
	***** Entraine : Retourne la variable uiEXCValeur																							*****
	************************************************************************************************************************************************/
	unsigned int EXCLireValeur() {
		return uiEXCValeur;
	}

	/************************************************************************************************************************************************
	***** EXCMODIFIERVALEUR : Modification de la variable uiEXCValeur																			*****
	*************************************************************************************************************************************************
	***** Entrée : uiErreur : unsigned int																									    *****
	***** Nécessite : Ne nécessite rien                                                                                                         *****
	***** Sortie : uiEXCValeur : Unsigned Int																									*****
	***** Entraine : Modification de la variable uiEXCValeur																					*****
	************************************************************************************************************************************************/
	void EXCModifierValeur(unsigned int uiErreur) {
		uiEXCValeur = uiErreur;
	}

};

#endif