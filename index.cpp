#include <iostream>
using namespace std;

#include "graph.h"

int main() {
	
	graph g(100,0.5);

	g.parseGraph();
    
	vector<int> v = g.diameterPath;
	vector<int>::iterator it;
	cout << "Diameter\n" << v.size() << endl;
	cout << "start -> ";
	for(it=v.begin() ; it!=v.end() ; ++it) {
		cout << *it << " -> ";
	}
	cout << "finish" << endl;

	v = g.radiusPath;
	cout << "Radius\n" << v.size() << endl;
	cout << "start -> ";
	for(it=v.begin() ; it!=v.end() ; ++it) {
		cout << *it << " -> ";
	}
	cout << "finish" << endl;

	for(int i=0 ; i<g.total ; i++){
		cout << i << " betweenness centrality: " << g.allNodes[i].btnCen << endl;
	}
	
	return 0;
}