#include <iostream>
using namespace std;

#include "graph.h"
int main(int argc, char const *argv[]) {

	if(argc == 3){
		graph g(atoi(argv[1]),atof(argv[2]));

		g.parseGraph();
	    
		vector<int> v = g.diameterPath;
		cout << "\nDiameter\nLength: " << g.diameter << endl;
		cout << "Path: ";
		for(int i=0 ; i<g.diameter ; ++i) {
			cout << v[i] << "---";
		}
		cout << v.back() << endl << endl;

		v = g.radiusPath;
		cout << "\nRadius\nLength: " << g.radius << endl;
		cout << "Path: ";
		for(int i=0 ; i<g.radius ; ++i) {
			cout << v[i] << "---";
		}
		cout << v.back() << endl << endl;

		for(int i=0 ; i<g.total ; i++){
			cout << i << " betweenness centrality: " << g.allNodes[i].btnCen << endl;
		}
	} else {
		cout << "Invalid number of arguments" << endl;
	}
	
	return 0;
}
