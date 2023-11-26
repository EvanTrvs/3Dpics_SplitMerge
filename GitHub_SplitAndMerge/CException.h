#ifndef CException_h
#define CException_h 

#define PAS_ERREUR 0

class CException {
private:
	unsigned int uiEXCValeur;

public:
	/************************************************************************************************************************************************
	***** CEXCEPTION : Constructeur par d�faut de la classe CException 																			*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																									    *****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : Aucun �l�ment retourn�																										*****
	***** Entraine : Initialise la variable uiEXCValeur																							*****
	************************************************************************************************************************************************/
	CException() {
		uiEXCValeur = PAS_ERREUR;
	}


	/************************************************************************************************************************************************
	***** EXCLIREVALEUR : Lecture de la variable uiEXCValeur 																					*****
	*************************************************************************************************************************************************
	***** Entr�e : Aucun Param�tre d'entr�e																									    *****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : uiEXCValeur : Unsigned Int																									*****
	***** Entraine : Retourne la variable uiEXCValeur																							*****
	************************************************************************************************************************************************/
	unsigned int EXCLireValeur() {
		return uiEXCValeur;
	}

	/************************************************************************************************************************************************
	***** EXCMODIFIERVALEUR : Modification de la variable uiEXCValeur																			*****
	*************************************************************************************************************************************************
	***** Entr�e : uiErreur : unsigned int																									    *****
	***** N�cessite : Ne n�cessite rien                                                                                                         *****
	***** Sortie : uiEXCValeur : Unsigned Int																									*****
	***** Entraine : Modification de la variable uiEXCValeur																					*****
	************************************************************************************************************************************************/
	void EXCModifierValeur(unsigned int uiErreur) {
		uiEXCValeur = uiErreur;
	}

};

#endif