#include "CMultiArrayOperation.h"

/************************************************************************************************************************************************
***** MAOSplits : Method for call each version of split																						*****
*************************************************************************************************************************************************
***** Input : maData : boost::multi_array<CGrayScale, 3> & | uiHomogeneite, uiMinSize, uiVersion : const unsigned int						*****
***** Precondition : Minimum cube size cannot be equal to 0                                                                                 *****
***** Output : vFRGLeafs : vector <CFragment>																								*****
***** Effects : Call version of split managing exceptional cases																			*****
************************************************************************************************************************************************/
vector<CFragment> CMultiArrayOperation::MAOSplits(boost::multi_array<CGrayScale, 3> & maData, unsigned int uiHomogeneite, unsigned int uiMinSize, unsigned int uiVersion)
{
	/* Exceptions Management */

	//uiMinSize = 0
	if (uiMinSize == 0) throw (CException(SEUIL_MIN));

	//Matrice Dimensions = 0
	if (maData.shape()[0] == 0 || maData.shape()[1] == 0 || maData.shape()[2] == 0) throw (CException(DIMENSION_ERROR));

	//Initialization of result vector and origin fragment
	vector<CFragment> vFRGresult = {};
	CFragment FRGOrigine = CFragment(& maData, { 0,0,0 }, { (unsigned int)maData.shape()[0], (unsigned int)maData.shape()[1], (unsigned int)maData.shape()[2] });

	//Object creation for call method, this methods are private and link by a friend
	CSplitOperation SplitOperation;

	//Version Choice
	if (uiVersion == 0) {
		SplitOperation.SOTSplitMatrice(FRGOrigine, uiHomogeneite, uiMinSize, vFRGresult);
	}
	else if (uiVersion == 2){
		SplitOperation.SOTSplitMatriceSwitch(FRGOrigine, uiHomogeneite, uiMinSize, vFRGresult);
	}
	else if (uiVersion == 1) {

		//Initialization of threads vector
		vector<std::thread> OptimizationByThreads = {};

		SplitOperation.SOTSplitMatriceThreads(FRGOrigine, uiHomogeneite, uiMinSize, vFRGresult, OptimizationByThreads);

		//Wait all threads by the main thread
		for (std::thread & Thread : OptimizationByThreads) {
			Thread.join();
		}
	}
	else throw (CException(UNDIFIED_VERSION)); //Exception Management : No version

	//Return the vector of fragment
	return vFRGresult;
}

/************************************************************************************************************************************************
***** MAOsetMireData : Method for create Mire																								*****
*************************************************************************************************************************************************
***** Input : MultiArrayMire : boost::multi_array<CGrayScale, 3> & | uiDimZ : const unsigned int							 				*****
***** Precondition : Nothing								                                                                                *****
***** Output : None																															*****
***** Effects : Initialize multi_array if the mire.nii is called																			*****
************************************************************************************************************************************************/
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

	//Resize in function of uiDimZ
	MultiArrayMire.resize(boost::extents[uiDimZ][uiDimY][uiDimX]);

	//Modification of the multi_array
	for (unsigned int uiIndexZ = 0; uiIndexZ < uiDimZ; ++uiIndexZ) {
		for (unsigned int uiIndexY = 0; uiIndexY < uiDimY; ++uiIndexY) {
			for (unsigned int uiIndexX = 0; uiIndexX < uiDimX; ++uiIndexX) {
				MultiArrayMire[uiIndexZ][uiIndexY][uiIndexX] = GSLMire[uiIndexY][uiIndexX];
			}
		}
	}
}

/************************************************************************************************************************************************
***** MAOcreateFromNifti : Method for multi_array from nifti image																			*****
*************************************************************************************************************************************************
***** Input : MultiArrayMire : boost::multi_array<CGrayScale, 3> & | NFDparam : const CNiftiImageData<uint16_t> &							*****
***** Precondition : Nothing								                                                                                *****
***** Output : None																															*****
***** Effects : Initialize multi_array from nifti image																						*****
************************************************************************************************************************************************/
void CMultiArrayOperation::MAOcreateFromNifti(boost::multi_array<CGrayScale, 3>& MultiArrayMire, const CNiftiImageData<uint16_t> & NFDparam) {
	unsigned int size = (unsigned int)NFDparam.NFDgetDataSize();

	//Storage of image informations
	std::vector<uint16_t> ui16NFDdata = NFDparam.NFDgetData();

	unsigned int uiDimZ = NFDparam.NFIgetHeader().dim[3];
	unsigned int uiDimY = NFDparam.NFIgetHeader().dim[2];
	unsigned int uiDimX = NFDparam.NFIgetHeader().dim[1];

	//Resize multi_array in function of the dimension of image
	MultiArrayMire.resize(boost::extents[uiDimZ][uiDimY][uiDimX]);

	//Modification of multi_array
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

/************************************************************************************************************************************************
***** MultiArrayFromFragments : Method for multi_array from fragment list																	*****
*************************************************************************************************************************************************
***** Input : MultiArrayMire : boost::multi_array<CGrayScale, 3> & | vFRGparam : const vector<CFragment> &									*****
***** Precondition : Nothing								                                                                                *****
***** Output : None																															*****
***** Effects : Initialize multi_array from fragment list 																					*****
************************************************************************************************************************************************/
void CMultiArrayOperation::MultiArrayFromFragments(boost::multi_array<CGrayScale, 3>& MultiArrayParam, const vector<CFragment>& vFRGparam) {
	unsigned int uiDimZ = (unsigned int)MultiArrayParam.shape()[0];
	unsigned int uiDimY = (unsigned int)MultiArrayParam.shape()[1];
	unsigned int uiDimX = (unsigned int)MultiArrayParam.shape()[2];

	unsigned int uiIterator = 0;
	// Pour chaque fragment dans la liste
	for (const CFragment& fragment : vFRGparam) {
		// Vérifier que le fragment est dans les limites du MultiArrayParam
		for (unsigned int z = 0; z < fragment.FRGGetDimensions()[0]; ++z) {
			for (unsigned int y = 0; y < fragment.FRGGetDimensions()[1]; ++y) {
				for (unsigned int x = 0; x < fragment.FRGGetDimensions()[2]; ++x) {
					unsigned int arrayZ = fragment.FRGGetCoos()[0] + z;
					unsigned int arrayY = fragment.FRGGetCoos()[1] + y;
					unsigned int arrayX = fragment.FRGGetCoos()[2] + x;

					// Vérifier que les indices sont dans les limites du MultiArrayParam
					if (arrayZ < uiDimZ && arrayY < uiDimY && arrayX < uiDimX) {
						MultiArrayParam[arrayZ][arrayY][arrayX] = CGrayScale(uiIterator);
					}
				}
			}
		}
		uiIterator++;
	}
}

/************************************************************************************************************************************************
***** Operator<<																															*****
*************************************************************************************************************************************************
***** Input : os : std::ostream & | MultiArrayParam	: const boost::multi_array<CGrayScale, 3> &												*****
***** Precondition : Nothing								                                                                                *****
***** Output : std::ostream &																												*****
***** Effects : OverLoad for print the multi_array																							*****
************************************************************************************************************************************************/
std::ostream& operator<<(std::ostream& os, const boost::multi_array<CGrayScale, 3>& MultiArrayParam) {

	//Triple loop for read all the multi_array
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