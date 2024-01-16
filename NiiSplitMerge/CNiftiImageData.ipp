#include "CNiftiImageData.h"

/**************************************************************************
	 ***** Default class Constructor | CNiftiImageData                    *****
	 **************************************************************************
	 ***** Input : None                                                   *****
	 ***** precondtion : None                                             *****
	 ***** Output : None                                                  *****
	 ***** Postcondition : Attribut of this are initialized               *****
	 **************************************************************************/
template <typename TypeT>
CNiftiImageData<TypeT>::CNiftiImageData() {

}

template <typename TypeT>
CNiftiImageData<TypeT>::CNiftiImageData(const nifti_1_header& hdrParam) {
	hdrNFIheader = hdrParam;
}

template <typename TypeT>
CNiftiImageData<TypeT>::CNiftiImageData(const CNiftiImage& NFIparam) : CNiftiImage(NFIparam) {}

template <typename TypeT>
int CNiftiImageData<TypeT>::NFDreadData() {

	FILE* fp;
	int ret, i;
	TypeT* data = NULL;

	//open the datafile, jump to data offset
	fopen_s(&fp, sNFIfilePath, "rb");
	if (fp == NULL ) {
		throw CException(5);	//error openning file
	}
	else {

		ret = (int)fseek(fp, (long)(hdrNFIheader.vox_offset), SEEK_SET);
		if (ret != 0) {
			throw CException(5);	//error openning file
		}

		// allocate buffer and read first 3D volume from data file
		data = (TypeT*)malloc(sizeof(TypeT) * hdrNFIheader.dim[1] * hdrNFIheader.dim[2] * hdrNFIheader.dim[3]);
		if (data == NULL) {
			throw CException(5);	//error openning file
		}

		ret = (int)fread(data, sizeof(TypeT), hdrNFIheader.dim[1] * hdrNFIheader.dim[2] * hdrNFIheader.dim[3], fp);
		if (ret != hdrNFIheader.dim[1] * hdrNFIheader.dim[2] * hdrNFIheader.dim[3]) {
			throw CException(5);	//error openning file
		}
		fclose(fp);


		// scale the data buffer
		/*
		if (hdrNFIheader.scl_slope != 0) {
			for (i = 0; i < hdrNFIheader.dim[1] * hdrNFIheader.dim[2] * hdrNFIheader.dim[3]; i++)
				data[i] = (data[i] * hdrNFIheader.scl_slope) + hdrNFIheader.scl_inter;
		}*/

		for (i = 0; i < hdrNFIheader.dim[1] * hdrNFIheader.dim[2] * hdrNFIheader.dim[3]; i++) {
			vTypeTNFDdata.push_back(data[i]);
		}

		free(data);
	}

	return 0;
}

template <typename TypeT>
int CNiftiImageData<TypeT>::NFDgetMireData(unsigned int uiSize) {

	if (hdrNFIheader.dim[1] != uiSize) {
		throw CException(5);
	}

	vector<vector<TypeT>> GSLMire = {
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

	unsigned int uiDim1 = hdrNFIheader.dim[3];	//32
	unsigned int uiDim2 = hdrNFIheader.dim[2];	//25

	for (unsigned int uiIndexZ = 0; uiIndexZ < uiDim1; ++uiIndexZ) {
		for (unsigned int uiIndexY = 0; uiIndexY < uiDim2; ++uiIndexY) {
			for (unsigned int uiIndexX = 0; uiIndexX < uiSize; ++uiIndexX) {
				vTypeTNFDdata.push_back(GSLMire[uiIndexY][uiIndexZ]);
			}
		}
	}

	return 0;
}

template <typename TypeT>
int CNiftiImageData<TypeT>::NFDwriteNifti(std::string sPathFile, boost::multi_array<CGrayScale, 3>& MultiArrayParam) {
	//std::cout << this->NFIgetHeaderInfo() << std::endl;

	//hdrNFIheader.sform_code = 1;
	//hdrNFIheader.xyzt_units = 10;

	FILE* fp;
	uint16_t* data = NULL;
	nifti1_extender pad = { 0,0,0,0 };
	int ret;
	unsigned int uiLoop = 0;

	//write first 348 bytes of header
	fopen_s(&fp, sPathFile.c_str(), "wb");
	if (fp == NULL) {
		throw CException(5);	//error openning file
	}
	ret = (int)fwrite(&hdrNFIheader, MIN_HEADER_SIZE, 1, fp);
	if (ret != 1) throw CException(5);	//error openning file

	//allocate buffer and fill with dummy data
	data = (uint16_t*)malloc(sizeof(uint16_t) * hdrNFIheader.dim[1] * hdrNFIheader.dim[2] * hdrNFIheader.dim[3] * hdrNFIheader.dim[4]);
	if (data == NULL) throw CException(5);	//error openning file


	if ((MultiArrayParam.shape()[0] == hdrNFIheader.dim[3]) && (MultiArrayParam.shape()[1] == hdrNFIheader.dim[2]) && (MultiArrayParam.shape()[2] == hdrNFIheader.dim[1])) {
		for (int c = 0; c < hdrNFIheader.dim[3]; c++) {
			for (int b = 0; b < hdrNFIheader.dim[2]; b++) {
				for (int a = 0; a < hdrNFIheader.dim[1]; a++) {
					data[uiLoop] = static_cast<uint16_t>(MultiArrayParam[c][b][a].GSLGetGray());
					//data[uiLoop] = static_cast<uint16_t>(uiLoop);
					uiLoop++;
				}
			}
		}
	} else throw CException(5);	//error openning file

	//write extender pad
	ret = (int)fwrite(&pad, 4, 1, fp);
	if (ret != 1) throw CException(5);	//error openning file

	//write image data
	ret = (int)fwrite(data, (size_t)(hdrNFIheader.bitpix / 8), hdrNFIheader.dim[1] * hdrNFIheader.dim[2] * hdrNFIheader.dim[3] * hdrNFIheader.dim[4], fp);
	if (ret != hdrNFIheader.dim[1] * hdrNFIheader.dim[2] * hdrNFIheader.dim[3] * hdrNFIheader.dim[4]) throw CException(5);	//error openning file

	fclose(fp);
	free(data);

	return 0;
}


template <typename TypeT>
int CNiftiImageData<TypeT>::NFDwriteNiftiUi(std::string sPathFile, boost::multi_array<unsigned int, 3>& MultiArrayParam) {
	//std::cout << this->NFIgetHeaderInfo() << std::endl;

	//hdrNFIheader.sform_code = 1;
	//hdrNFIheader.xyzt_units = 10;

	FILE* fp;
	uint16_t* data = NULL;
	nifti1_extender pad = { 0,0,0,0 };
	int ret;
	unsigned int uiLoop = 0;

	//write first 348 bytes of header
	fopen_s(&fp, sPathFile.c_str(), "wb");
	if (fp == NULL) {
		throw CException(5);	//error openning file
	}
	ret = (int)fwrite(&hdrNFIheader, MIN_HEADER_SIZE, 1, fp);
	if (ret != 1) throw CException(5);	//error openning file

	//allocate buffer and fill with dummy data
	data = (uint16_t*)malloc(sizeof(uint16_t) * hdrNFIheader.dim[1] * hdrNFIheader.dim[2] * hdrNFIheader.dim[3] * hdrNFIheader.dim[4]);
	if (data == NULL) throw CException(5);	//error openning file

	if ((MultiArrayParam.shape()[0] == hdrNFIheader.dim[3]) && (MultiArrayParam.shape()[1] == hdrNFIheader.dim[2]) && (MultiArrayParam.shape()[2] == hdrNFIheader.dim[1])) {
		for (int c = 0; c < hdrNFIheader.dim[3]; c++) {
			for (int b = 0; b < hdrNFIheader.dim[2]; b++) {
				for (int a = 0; a < hdrNFIheader.dim[1]; a++) {
					data[uiLoop] = static_cast<uint16_t>(MultiArrayParam[c][b][a]);
					//data[uiLoop] = static_cast<uint16_t>(uiLoop);
					//if (b == 2) std::cout << MultiArrayParam[c][b][a] << ",";
					uiLoop++;
				}
			}
		}
	} else throw CException(5);	//error openning file

	//write extender pad
	ret = (int)fwrite(&pad, 4, 1, fp);
	if (ret != 1) throw CException(5);	//error openning file

	//write image data
	ret = (int)fwrite(data, (size_t)(hdrNFIheader.bitpix / 8), hdrNFIheader.dim[1] * hdrNFIheader.dim[2] * hdrNFIheader.dim[3] * hdrNFIheader.dim[4], fp);
	if (ret != hdrNFIheader.dim[1] * hdrNFIheader.dim[2] * hdrNFIheader.dim[3] * hdrNFIheader.dim[4]) throw CException(5);	//error openning file

	fclose(fp);
	free(data);

	return 0;
}

template <typename TypeT>
std::vector<TypeT> CNiftiImageData<TypeT>::NFDgetData() const{
	return vTypeTNFDdata;
}

template <typename TypeT>
size_t CNiftiImageData<TypeT>::NFDgetDataSize() const {
	return vTypeTNFDdata.size();
}


template <typename TypeT>
template <typename OtherTypeT>
int CNiftiImageData<TypeT>::NFDconvertDataFrom(const CNiftiImageData<OtherTypeT>& NFDparam) {

	vTypeTNFDdata.clear();
	unsigned int size = (unsigned int)NFDparam.NFDgetDataSize();

	std::vector<OtherTypeT> vOtherTypeTNFDdata = NFDparam.NFDgetData();

	if (NFDparam.NFIgetDataType() == 16) {
		for (unsigned int uiloop = 0; uiloop < size; uiloop++) {
			vTypeTNFDdata.push_back(static_cast<uint16_t>(vOtherTypeTNFDdata[uiloop] * 100));
		}
	}
	else {
		for (unsigned int uiloop = 0; uiloop < size; uiloop++) {
			vTypeTNFDdata.push_back(static_cast<uint16_t>(vOtherTypeTNFDdata[uiloop]));
		}
	}

	hdrNFIheader.datatype = 512;
	hdrNFIheader.bitpix = 16;

	return 0;
}

template <typename TypeT>
std::pair<TypeT, TypeT> CNiftiImageData<TypeT>::NFDgetMinMax() const {
	if (vTypeTNFDdata.empty()) {
		// Gérer le cas où le vecteur est vide
		return std::make_pair(TypeT(), TypeT());
	}

	auto minMaxPair = std::minmax_element(vTypeTNFDdata.begin(), vTypeTNFDdata.end());
	return std::make_pair(*minMaxPair.first, *minMaxPair.second);
}

template <typename TypeT>
int CNiftiImageData<TypeT>::NFDpreprocess(std::pair < uint16_t, uint16_t> pNewMinMax) {

	std::pair<uint16_t, uint16_t> minMaxPair = this->NFDgetMinMax();
	unsigned int size = (int)vTypeTNFDdata.size();

	std::vector< uint16_t> vBuffer;
	vBuffer.assign(vTypeTNFDdata.begin(), vTypeTNFDdata.end());
	vTypeTNFDdata.clear();

	// Vérifier que les bornes originales et nouvelles sont valides
	if (minMaxPair.first >= minMaxPair.second || pNewMinMax.first >= pNewMinMax.second) {
		throw CException(5);	//error openning file
	}

	double dPreCalculate1 = (double)(minMaxPair.second - minMaxPair.first);
	double dPreCalculate2 = (double)(pNewMinMax.second - pNewMinMax.first);

	if (dPreCalculate1 > dPreCalculate2) {
		// Calculer et retourner la nouvelle valeur compressée et remise à l'échelle
		for (unsigned int uiloop = 0; uiloop < size; uiloop++) {
			vTypeTNFDdata.push_back(static_cast<uint16_t>((static_cast<double>(vBuffer[uiloop] - minMaxPair.first) / dPreCalculate1) * dPreCalculate2 + pNewMinMax.first));
		}
	}
	else {
		double uiDifference = pNewMinMax.first - minMaxPair.first;
		// réajuster
		for (unsigned int uiloop = 0; uiloop < size; uiloop++) {
			vTypeTNFDdata.push_back(static_cast<uint16_t>( vBuffer[uiloop] + uiDifference));
		}
	}
	return 0;
}

template <typename TypeT>
std::string CNiftiImageData<TypeT>::NFIgetDataInfo() const {
	std::string sOutMessage;

	std::pair<uint16_t, uint16_t> pMinMax = this->NFDgetMinMax();

	sOutMessage.append("[NiiSplitMerge.exe] Image DATA content:\n");
	sOutMessage.append("[NiiSplitMerge.exe] \tMinimum value:\t\t" + std::to_string(pMinMax.first) + "\n");
	sOutMessage.append("[NiiSplitMerge.exe] \tMaximum value:\t\t" + std::to_string(pMinMax.second) + "\n");
	sOutMessage.append("[NiiSplitMerge.exe] \tData Type:\t\t" + NiftiTypeDictionary.find(hdrNFIheader.datatype)->second + "(" + std::to_string(hdrNFIheader.datatype) + ")\n");

	return sOutMessage;
}