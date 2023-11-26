#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/multi_array.hpp>
#include <boost/property_tree/ptree.hpp>
#include <algorithm>
#include <vector>

#include "CGrayScale.h"
#include "CFragment.h"
#include "CGrapheColore.h"
#include "CGraphesCreator.h"
#include "COperationsSurGraphes.h"
#include "CSplitOperation.h"
#include "CThreadInformation.h"

using namespace std;

int Lancement(vector <unsigned int> uiTaille)
{
	std::cout << "Taille Cube : " << uiTaille[0] << endl;

	unsigned int uiHomogeneite = 0;
	unsigned int uiTailleMinCube = 1; //Ne peut être inférieur à 1 => erreur sinon 

	typedef boost::multi_array<CGrayScale, 3> array_type;
	array_type MA(boost::extents[uiTaille[0]][uiTaille[1]][uiTaille[2]]);

	unsigned int value = 1;
	for (unsigned int i = 0; i < uiTaille[0]; ++i) {
		for (unsigned int j = 0; j < uiTaille[1]; ++j) {
			for (unsigned int k = 0; k < uiTaille[2]; ++k) {
				MA[i][j][k] = CGrayScale(value);
				value++;
				if (value > 4) {
					value = 1;
				}
			}
		}
	}

	/*for (unsigned int i = 0; i < uiTaille[0]; ++i) {
		for (unsigned int j = 0; j < uiTaille[1]; ++j) {
			for (unsigned int k = 0; k < uiTaille[2]; ++k) {
				std::cout << "MA[" << i << "][" << j << "][" << k << "] = CGrayScale(" << MA[i][j][k].GSLGetGray() << ");\n";
			}
		}
	}*/

	CFragment f0 = CFragment(&MA, { 0,0,0 }, uiTaille, 1);

	clock_t cTempsDebut;
	cTempsDebut = clock();

	std::cout << "START GIT : " << endl;

	vector<std::thread> OptimizationByThreads = {};

	CSplitOperation SO;
	vector <CFragment> vFRGLeafs = {};
	vector <pair<unsigned int, unsigned int>> vpuiVoisin = {}; //Lorsque optimiser

	//SO.SOTSplitMatrice(f0, uiHomogeneite, uiTailleMinCube, &vFRGLeafs, &OptimizationByThreads);
	SO.SOTSplitMatriceV2(f0, uiHomogeneite, uiTailleMinCube, vFRGLeafs, OptimizationByThreads);
	//SO.SOTSplitMatriceV3(f0, uiHomogeneite, uiTailleMinCube, vFRGLeafs);

	for (auto& thread : OptimizationByThreads) {
		thread.join();
	}

	std::cout << "Nombre feuilles : " << vFRGLeafs.size() << endl;

	clock_t cTemps1 = clock() - cTempsDebut;

	std::cout << "Le temps mis etape 1 est de : " << (double)cTemps1 / CLOCKS_PER_SEC << std::endl;

	/*CGraphesCreator Gs;
	Gs.GCRCreationGraphes(vFRGLeafs, uiHomogeneite);

	clock_t cTemps2 = clock() - cTemps1;
	std::cout << "Le temps mis etape 2 est de : " << (double)cTemps2 / CLOCKS_PER_SEC << std::endl;

	vector <CGrapheColore> vGs = Gs.GCRGetGraphes();*/

	/*cout << "NOMBRE VECTOR (PRE)" << vGs.size() << endl;
	for (unsigned int uiBoucle = 0; uiBoucle < vGs.size(); uiBoucle++) {
		cout << "TAILLE VECTOR (PRE): " << boost::num_vertices(vGs[uiBoucle].GPCGetGraphe()) << " -> edges : " << boost::num_edges(vGs[uiBoucle].GPCGetGraphe()) << " => couleur " << vGs[uiBoucle].GPCGetGray().GSLGetGray() << endl;
	}*/

	/*COperationsSurGraphes OG;
	vector <CGrapheColore> finalvGs = OG.OSGMergeGraphe(vGs, uiHomogeneite);

	clock_t cTemps3 = clock() - cTemps2;
	std::cout << "Le temps mis etape 3 est de : " << (double)cTemps3 / CLOCKS_PER_SEC << std::endl;*/

	/*cout << "NOMBRE VECTOR " << finalvGs.size() << endl;
	for (unsigned int uiBoucle = 0; uiBoucle < finalvGs.size(); uiBoucle++) {
		cout << "TAILLE VECTOR: " << boost::num_vertices(finalvGs[uiBoucle].GPCGetGraphe()) << " -> edges : " << boost::num_edges(finalvGs[uiBoucle].GPCGetGraphe()) << endl;
	}*/

	/*typedef boost::multi_array <CVoxel, 3> multi_array_type;
	multi_array_type MAT(boost::extents[uiTaille[0]][uiTaille[1]][uiTaille[2]]);

	MAT = OG.OSGGrapheToMatrice(finalvGs);

	clock_t cTemps4 = clock() - cTempsDebut;
	std::cout << "Le temps TOTAL mis est de : " << (double)cTemps4 / CLOCKS_PER_SEC << std::endl;
	*/
	return 0;
}

int main() {
	/*for (unsigned int uiBoucle = 30; uiBoucle <= 100; uiBoucle += 10) {
		Lancement({ uiBoucle, uiBoucle, uiBoucle });
	}*/

	Lancement({ 256, 256, 256 });
}
