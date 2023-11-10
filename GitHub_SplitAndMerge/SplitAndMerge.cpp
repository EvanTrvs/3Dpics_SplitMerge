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

int main()
{

	vector <unsigned int> uiTaille = { 4, 4, 4 };
	unsigned int uiHomogeneite = 1;

	typedef boost::multi_array<CGrayScale, 3> array_type;
	array_type MA(boost::extents[uiTaille[0]][uiTaille[1]][uiTaille[2]]);

	unsigned int value = 1;
	for (unsigned int i = 0; i < uiTaille[0]; ++i) {
		for (unsigned int j = 0; j < uiTaille[0]; ++j) {
			for (unsigned int k = 0; k < uiTaille[0]; ++k) {
				MA[i][j][k] = CGrayScale(value++);
				if (value > 16) {
					value = 1;
				}
			}
		}
	}

	for (unsigned int i = 0; i < uiTaille[0]; ++i) {
		for (unsigned int j = 0; j < uiTaille[0]; ++j) {
			for (unsigned int k = 0; k < uiTaille[0]; ++k) {
				std::cout << "MA[" << i << "][" << j << "][" << k << "] = CGrayScale(" << MA[i][j][k].GSLGetGray() << ");\n";
			}
		}
	}

	CFragment f0 = CFragment(&MA, { 0,0,0 }, uiTaille);

	clock_t cTemps;
	cTemps = clock();

	CSplitOperation SO;
	vector <CFragment> vFRGLeafs = {};

	vFRGLeafs = SO.SOTSplitMatrice(f0, uiHomogeneite, vFRGLeafs);

	CGraphesCreator Gs;
	Gs.GCRCreationGraphes(vFRGLeafs, uiHomogeneite);

	vector <CGrapheColore> vGs = Gs.GCRGetGraphes();

	cout << "TAILLE VECTOR " << vGs.size() << endl;
	cout << "TAILLE VECTOR 0 : " << boost::num_vertices(vGs[0].GPCGetGraphe()) << " -> edges : " << boost::num_edges(vGs[0].GPCGetGraphe()) << endl;

	std::cout << "Le temps mis est de : " << (double)cTemps / CLOCKS_PER_SEC << std::endl;
}
