#include "CMultiArrayOperation.h"

/************************************************************************************************************************************************
***** MAOSPLITS : Méthode d'appel des méthodes de Splits																					*****
*************************************************************************************************************************************************
***** Entrée : maData : boost::multi_array<CGrayScale, 3> & | uiHomogeneite, uiMinSize, uiVersion : unsigned int							*****
***** Nécessite : La taille minimum des cubes ne peux être égale à 0                                                                        *****
***** Sortie : vFRGLeafs : vector <CFragment>																								*****
***** Entraine : Appel les méthodes de Split en gérant les cas d'exception																	*****
************************************************************************************************************************************************/
vector<CFragment> CMultiArrayOperation::MAOSplits(boost::multi_array<CGrayScale, 3> & maData, unsigned int uiHomogeneite, unsigned int uiMinSize, unsigned int uiVersion)
{
	//Gestion de l'exception : Taille minimum = 0
	if (uiMinSize == 0) throw (CException(SEUIL_MIN));

	//Gestion de l'exception : Dimension = 0
	if (maData.shape()[0] == 0 || maData.shape()[1] == 0 || maData.shape()[2] == 0) throw (CException(DIMENSION_ERROR));

	//Initialisation des données nécessaires au fonctionnement des splits
	vector<CFragment> vFRGresult = {};
	CFragment FRGOrigine = CFragment(& maData, { 0,0,0 }, { (unsigned int)maData.shape()[0], (unsigned int)maData.shape()[1], (unsigned int)maData.shape()[2] });

	//Création de l'objet d'appel des méthodes, ces méthodes sont privates et liés par un friend
	CSplitOperation SplitOperation;

	//Choix de la Version
	if (uiVersion == 0) {
		SplitOperation.SOTSplitMatrice(FRGOrigine, uiHomogeneite, uiMinSize, vFRGresult);
	}
	else if (uiVersion == 1) {

		vector<std::thread> OptimizationByThreads = {};

		//Initialisation du vecteur de thread (fonctionnel)
		SplitOperation.SOTSplitMatriceThreads(FRGOrigine, uiHomogeneite, uiMinSize, vFRGresult, OptimizationByThreads);

		//Attente de la fin des threads par le Main 
		for (std::thread & Thread : OptimizationByThreads) {
			Thread.join();
		}
	}
	else throw (CException(UNDIFIED_VERSION)); //Gestion de l'exception : Aucun / Mauvaise Version choisie

	//Retourne le vecteur des feuilles final
	return vFRGresult;
}


void CMultiArrayOperation::MAOsetMireData(unsigned int uiDimZ, boost::multi_array<CGrayScale, 3>& MultiArrayMire) {

	vector<vector<CGrayScale>> GSLMire = {
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	42,	40,	38,	36,	34,	32,	30,	28,	28,	30,	32,	34,	36,	38,	40,	42 },
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	38,	36,	34,	32,	30,	28,	26,	24,	24,	26,	28,	30,	32,	34,	36,	38 },
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	34,	32,	30,	28,	26,	24,	22,	20,	20,	22,	24,	26,	28,	30,	32,	34 },
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	30,	28,	26,	24,	22,	20,	18,	16,	16,	18,	20,	22,	24,	26,	28,	30 },
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	26,	24,	22,	20,	18,	16,	14,	12,	12,	14,	16,	18,	20,	22,	24,	26 },
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	22,	20,	18,	16,	14,	12,	10,	8,	8,	10,	12,	14,	16,	18,	20,	22 },
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	18,	16,	14,	12,	10,	8,	6,	4,	4,	6,	8,	10,	12,	14,	16,	18 },
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	14,	12,	10,	8,	6,	4,	2,	0,	0,	2,	4,	6,	8,	10,	12,	14 },
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	28,	30,	32,	34,	36,	38,	40,	42,	42,	40,	38,	36,	34,	32,	30,	28 },
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	24,	26,	28,	30,	32,	34,	36,	38,	38,	36,	34,	32,	30,	28,	26,	24 },
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	20,	22,	24,	26,	28,	30,	32,	34,	34,	32,	30,	28,	26,	24,	22,	20 },
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	16,	18,	20,	22,	24,	26,	28,	30,	30,	28,	26,	24,	22,	20,	18,	16 },
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	12,	14,	16,	18,	20,	22,	24,	26,	26,	24,	22,	20,	18,	16,	14,	12 },
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	8,	10,	12,	14,	16,	18,	20,	22,	22,	20,	18,	16,	14,	12,	10,	8 },
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	4,	6,	8,	10,	12,	14,	16,	18,	18,	16,	14,	12,	10,	8,	6,	4 },
		{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	2,	4,	6,	8,	10,	12,	14,	14,	12,	10,	8,	6,	4,	2,	0 },
		{7,	13,	12,	17,	12,	11,	15,	13,	11,	8,	4,	8,	7,	6,	11,	14,	9,	11,	9,	9,	10,	9,	15,	14,	10,	10,	9,	10,	10,	5,	5,	10 },
		{24,12,	7,	24,	10,	9,	9,	9,	10,	21,	10,	10,	6,	3,	11,	7,	17,	8,	9,	20,	10,	11,	16,	15,	10,	20,	10,	11,	10,	5,	5,	10 },
		{20,7,	9,	20,	10,	6,	12,	10,	11,	27,	12,	7,	8,	11,	9,	12,	20,	10,	11,	20,	10,	10,	11,	12,	10,	25,	14,	9,	10,	10,	10,	10 },
		{23,17,	4,	24,	8,	12,	13,	16,	31,	30,	9,	9,	20,	21,	9,	12,	21,	11,	10,	20,	11,	11,	4,	5,	11,	28,	30,	14,	10,	10,	10,	10 },
		{19,24,	19,	20,	10,	12,	30,	28,	28,	15,	11,	10,	20,	19,	10,	9,	21,	19,	20,	18,	11,	9,	5,	5,	10,	14,	28,	25,	20,	10,	10,	10 },
		{13,21,	12,	16,	6,	4,	8,	11,	8,	13,	11,	9,	11,	9,	9,	9,	12,	10,	10,	12,	9,	9,	9,	10,	10,	10,	11,	10,	10,	10,	10,	10 },
		{8,	11,	6,	32,	33,	27,	32,	28,	13,	10,	10,	26,	29,	32,	30,	29,	12,	9,	10,	30,	31,	29,	30,	30,	10,	10,	10,	30,	30,	30,	30,	30 },
		{30,28,	28,	25,	4,	11,	16,	26,	30,	27,	31,	34,	11,	10,	8,	28,	29,	29,	31,	29,	11,	10,	11,	29,	30,	30,	30,	30,	10,	10,	10,	30 },
		{16,11,	13,	9,	7,	12,	8,	8,	10,	11,	9,	11,	10,	12,	10,	10,	11,	10,	10,	11,	9,	9,	9,	9,	10,	10,	10,	9,	10,	10,	10,	10 }
	};

	unsigned int uiDimX = 32;	//horizontale
	unsigned int uiDimY = 25;	//verticale

	MultiArrayMire.resize(boost::extents[uiDimZ][uiDimY][uiDimX]);

	for (unsigned int uiIndexZ = 0; uiIndexZ < uiDimZ; ++uiIndexZ) {
		for (unsigned int uiIndexY = 0; uiIndexY < uiDimY; ++uiIndexY) {
			for (unsigned int uiIndexX = 0; uiIndexX < uiDimX; ++uiIndexX) {
				MultiArrayMire[uiIndexZ][uiIndexY][uiIndexX] = GSLMire[uiIndexY][uiIndexX];
			}
		}
	}
}

void CMultiArrayOperation::MAOcreateFromNifti(boost::multi_array<CGrayScale, 3>& MultiArrayMire, const CNiftiImageData<uint16_t> & NFDparam) {
	unsigned int size = (unsigned int)NFDparam.NFDgetDataSize();

	std::vector<uint16_t> ui16NFDdata = NFDparam.NFDgetData();

	unsigned int uiDimZ = NFDparam.NFIgetHeader().dim[3];
	unsigned int uiDimY = NFDparam.NFIgetHeader().dim[2];
	unsigned int uiDimX = NFDparam.NFIgetHeader().dim[1];

	MultiArrayMire.resize(boost::extents[uiDimZ][uiDimY][uiDimX]);

	unsigned int r = 0;
	for (unsigned int i = 0; i < uiDimZ; ++i) {
		for (unsigned int j = 0; j < uiDimY; ++j) {
			for (unsigned int k = 0; k < uiDimX; ++k) {
				MultiArrayMire[i][j][k] = CGrayScale(ui16NFDdata[r]);
				r++;
			}
		}
	}
}


std::ostream& operator<<(std::ostream& os, const boost::multi_array<CGrayScale, 3>& MultiArrayParam) {

	for (unsigned int i = 0; i < (unsigned int)MultiArrayParam.shape()[0]; ++i) {
		os << "[ ";
		for (unsigned int j = 0; j < (unsigned int)MultiArrayParam.shape()[1]; ++j) {
			os << "[ ";
			for (unsigned int k = 0; k < (unsigned int)MultiArrayParam.shape()[2]; ++k) {
				os << (MultiArrayParam[i][j][k]).GSLGetGray() << ", ";
			}
			os << "]" << std::endl;
		}
		os << " ]" << std::endl;
	}
	return os;
}