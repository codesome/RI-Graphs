#include <iostream>
#include <vector>
using namespace std;

struct node {
	int nodeNumber; // 0,1,2,3, ... .. .. . n-1
	int btnCen; // betweenness centrality
	vector<int> links; // connected nodes
};

graph::graph(int N , float p) {

	/* 
	assign btnCen to 0 while creating
	 */

}