#include <vector>

struct node {
	int nodeNumber; // 0,1,2,3, ... .. .. . n-1
	int btnCen; // betweenness centrality
	vector<int> links; // connected nodes
};

class graph {

private:
	vector< vector<int> > possiblePaths; // for finding shortest path
	int shortestLength;
	int *distanceForNodes;
	void shortestPathProcess(vector<int>,int); // used for shortestPathBetween()
	vector<int> parseShortestPaths(int,int); // used in parseGraph for betweenness centrality
	
public:
	int radius , diameter; // length of radius and diameter
	int total; // total number of nodes
	node *allNodes; // all the nodes in the graph
	vector<int> diameterPath , radiusPath; // paths for diameter and radius
	graph(int,float);
	void parseGraph(); // for diamater , radius , betweenness centrality
	vector< vector<int> > shortestPathBetween(int,int); // used in parseGraph()
};
