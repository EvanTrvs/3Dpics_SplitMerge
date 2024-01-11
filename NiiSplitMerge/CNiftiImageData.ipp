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
int CNiftiImageData<TypeT>::NFDwriteNifti(std::string sPathFile, boost::multi_array<CGrayScale, 3>& MultiArrayParam) {
	std::cout << this->NFIgetHeaderInfo() << std::endl;

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

	/*
	for (uiLoop = 0; i < hdrNFIheader.dim[1] * hdrNFIheader.dim[2] * hdrNFIheader.dim[3] * hdrNFIheader.dim[4]; uiLoop++) {
		data[uiLoop] = i / hdrNFIheader.scl_slope;
	}*/

	std::cout << MultiArrayParam.shape()[0] << "," << MultiArrayParam.shape()[1] << "," << MultiArrayParam.shape()[2] << std::endl;
	std::cout << hdrNFIheader.dim[1] << "," << hdrNFIheader.dim[2] << "," << hdrNFIheader.dim[3] << std::endl;

	if (MultiArrayParam.shape()[0] == hdrNFIheader.dim[1]) {
		if (MultiArrayParam.shape()[1] == hdrNFIheader.dim[2]) {
			for (int a = 0; a < hdrNFIheader.dim[1]; a++) {
				for (int b = 0; b < hdrNFIheader.dim[2]; b++) {
					for (int c = 0; c < hdrNFIheader.dim[3]; c++) {
						data[uiLoop] = static_cast<uint16_t>(MultiArrayParam[a][b][c].GSLGetGray());
						uiLoop++;
					}
				}
			}
		}
		else {
			for (int a = 0; a < hdrNFIheader.dim[1]; a++) {
				for (int b = 0; b < hdrNFIheader.dim[2]; b++) {
					for (int c = 0; c < hdrNFIheader.dim[3]; c++) {
						data[uiLoop] = static_cast<uint16_t>(MultiArrayParam[a][c][b].GSLGetGray());
						uiLoop++;
					}
				}
			}
		}
	}
	else if (MultiArrayParam.shape()[1] == hdrNFIheader.dim[1]) {
		if (MultiArrayParam.shape()[0] == hdrNFIheader.dim[2]) {
			for (int a = 0; a < hdrNFIheader.dim[1]; a++) {
				for (int b = 0; b < hdrNFIheader.dim[2]; b++) {
					for (int c = 0; c < hdrNFIheader.dim[3]; c++) {
						data[uiLoop] = static_cast<uint16_t>(MultiArrayParam[b][a][c].GSLGetGray());
						uiLoop++;
					}
				}
			}
		}
		else {
			for (int a = 0; a < hdrNFIheader.dim[1]; a++) {
				for (int b = 0; b < hdrNFIheader.dim[2]; b++) {
					for (int c = 0; c < hdrNFIheader.dim[3]; c++) {
						data[uiLoop] = static_cast<uint16_t>(MultiArrayParam[c][a][b].GSLGetGray());
						uiLoop++;
					}
				}
			}
		}
	}
	else if (MultiArrayParam.shape()[2] == hdrNFIheader.dim[1]) {
		if (MultiArrayParam.shape()[0] == hdrNFIheader.dim[2]) {
			for (int a = 0; a < hdrNFIheader.dim[1]; a++) {
				for (int b = 0; b < hdrNFIheader.dim[2]; b++) {
					for (int c = 0; c < hdrNFIheader.dim[3]; c++) {
						data[uiLoop] = static_cast<uint16_t>(MultiArrayParam[b][c][a].GSLGetGray());
						uiLoop++;
					}
				}
			}
		}
		else {
			for (int c = 0; c < hdrNFIheader.dim[3]; c++) {
				for (int b = 0; b < hdrNFIheader.dim[2]; b++) {
					for (int a = 0; a < hdrNFIheader.dim[1]; a++) {
						data[uiLoop] = static_cast<uint16_t>(MultiArrayParam[c][b][a].GSLGetGray());
						//data[uiLoop] = static_cast<uint16_t>(uiLoop);
						uiLoop++;
					}
				}
			}
		}

		/*for (int a = 0; a < hdrNFIheader.dim[1]; a++) {
				for (int c = 0; c < hdrNFIheader.dim[3]; c++) {
					for (int b = 0; b < hdrNFIheader.dim[2]; b++) {
						//data[uiLoop] = static_cast<uint16_t>(MultiArrayParam[c][b][a]);
						data[uiLoop] = static_cast<uint16_t>(uiLoop);
						uiLoop++;
					}
				}
			}
		}*/

	}
	else throw CException(5);	//error openning file

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
	std::cout << this->NFIgetHeaderInfo() << std::endl;

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

	/*
	for (uiLoop = 0; i < hdrNFIheader.dim[1] * hdrNFIheader.dim[2] * hdrNFIheader.dim[3] * hdrNFIheader.dim[4]; uiLoop++) {
		data[uiLoop] = i / hdrNFIheader.scl_slope;
	}*/

	std::cout << MultiArrayParam.shape()[0] << "," << MultiArrayParam.shape()[1] << "," << MultiArrayParam.shape()[2] << std::endl;
	std::cout << hdrNFIheader.dim[1] << "," << hdrNFIheader.dim[2] << "," << hdrNFIheader.dim[3] << std::endl;

	if (MultiArrayParam.shape()[0] == hdrNFIheader.dim[1]) {
		if (MultiArrayParam.shape()[1] == hdrNFIheader.dim[2]) {
			for (int a = 0; a < hdrNFIheader.dim[1]; a++) {
				for (int b = 0; b < hdrNFIheader.dim[2]; b++) {
					for (int c = 0; c < hdrNFIheader.dim[3]; c++) {
						data[uiLoop] = static_cast<uint16_t>(MultiArrayParam[a][b][c]);
						uiLoop++;
					}
				}
			}
		}
		else {
			for (int a = 0; a < hdrNFIheader.dim[1]; a++) {
				for (int b = 0; b < hdrNFIheader.dim[2]; b++) {
					for (int c = 0; c < hdrNFIheader.dim[3]; c++) {
						data[uiLoop] = static_cast<uint16_t>(MultiArrayParam[a][c][b]);
						uiLoop++;
					}
				}
			}
		}
	}
	else if (MultiArrayParam.shape()[1] == hdrNFIheader.dim[1]) {
		if (MultiArrayParam.shape()[0] == hdrNFIheader.dim[2]) {
			for (int a = 0; a < hdrNFIheader.dim[1]; a++) {
				for (int b = 0; b < hdrNFIheader.dim[2]; b++) {
					for (int c = 0; c < hdrNFIheader.dim[3]; c++) {
						data[uiLoop] = static_cast<uint16_t>(MultiArrayParam[b][a][c]);
						uiLoop++;
					}
				}
			}
		}
		else {
			for (int a = 0; a < hdrNFIheader.dim[1]; a++) {
				for (int b = 0; b < hdrNFIheader.dim[2]; b++) {
					for (int c = 0; c < hdrNFIheader.dim[3]; c++) {
						data[uiLoop] = static_cast<uint16_t>(MultiArrayParam[c][a][b]);
						uiLoop++;
					}
				}
			}
		}
	}
	else if (MultiArrayParam.shape()[2] == hdrNFIheader.dim[1]) {
		if (MultiArrayParam.shape()[0] == hdrNFIheader.dim[2]) {
			for (int a = 0; a < hdrNFIheader.dim[1]; a++) {
				for (int b = 0; b < hdrNFIheader.dim[2]; b++) {
					for (int c = 0; c < hdrNFIheader.dim[3]; c++) {
						data[uiLoop] = static_cast<uint16_t>(MultiArrayParam[b][c][a]);
						uiLoop++;
					}
				}
			}
		}
		else {
			for (int c = 0; c < hdrNFIheader.dim[3]; c++) {
				for (int b = 0; b < hdrNFIheader.dim[2]; b++) {
					for (int a = 0; a < hdrNFIheader.dim[1]; a++) {
						data[uiLoop] = static_cast<uint16_t>(MultiArrayParam[c][b][a]);
						//data[uiLoop] = static_cast<uint16_t>(uiLoop);
						uiLoop++;
					}
				}
			}
		}

		/*for (int a = 0; a < hdrNFIheader.dim[1]; a++) {
				for (int c = 0; c < hdrNFIheader.dim[3]; c++) {
					for (int b = 0; b < hdrNFIheader.dim[2]; b++) {
						//data[uiLoop] = static_cast<uint16_t>(MultiArrayParam[c][b][a]);
						data[uiLoop] = static_cast<uint16_t>(uiLoop);
						uiLoop++;
					}
				}
			}
		}*/

	}
	else throw CException(5);	//error openning file

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