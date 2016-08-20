#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

struct node {
	int nodeNumber; // 0,1,2,3, ... .. .. . n-1
	int btnCen; // betweenness centrality (TODO)
	vector<int> links; // connected nodes
};

// private variables
int total = 10; // total number of nodes
node *allNodes = new node[total]; // all the nodes in the graph
vector<int> diameterPath , radiusPath; // paths for diameter and radius
int radius , diameter; // length of radius and diameter

vector< vector<int> > possiblePaths; // for finding shortest path

void shortestPathProcess(vector<int>,int); // used for shortestPathBetween()
vector< vector<int> > shortestPathBetween(int,int); // used in parseGraph()
vector<int> parseShortestPaths(int,int); // used in parseGraph for betweenness centrality
void parseGraph(); // for diameter , radius


int main() {
	for(int i=0 ; i<total ; i++) {
		allNodes[i].nodeNumber = i;
		allNodes[i].btnCen = 0;
	}
	// generating a graph with 10 nodes
	allNodes[0].links.push_back(1);
	allNodes[0].links.push_back(4);
	allNodes[0].links.push_back(9);

	allNodes[1].links.push_back(0);
	allNodes[1].links.push_back(2);
	allNodes[1].links.push_back(8);

	allNodes[2].links.push_back(1);
	allNodes[2].links.push_back(3);
	allNodes[2].links.push_back(4);
	allNodes[2].links.push_back(5);
	allNodes[2].links.push_back(7);
	allNodes[2].links.push_back(8);

	allNodes[3].links.push_back(2);
	allNodes[3].links.push_back(4);
	allNodes[3].links.push_back(5);

	allNodes[4].links.push_back(0);
	allNodes[4].links.push_back(2);
	allNodes[4].links.push_back(3);
	allNodes[4].links.push_back(5);
	allNodes[4].links.push_back(6);
	allNodes[4].links.push_back(9);

	allNodes[5].links.push_back(2);
	allNodes[5].links.push_back(3);
	allNodes[5].links.push_back(4);
	allNodes[5].links.push_back(6);
	allNodes[5].links.push_back(7);

	allNodes[6].links.push_back(4);
	allNodes[6].links.push_back(5);

	allNodes[7].links.push_back(2);
	allNodes[7].links.push_back(5);

	allNodes[8].links.push_back(1);
	allNodes[8].links.push_back(2);

	allNodes[9].links.push_back(0);
	allNodes[9].links.push_back(4);

	std::clock_t start;
    double duration;

    start = std::clock();

	parseGraph();
    
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    cout<<"duration: "<< duration <<'\n';

	vector<int> v = diameterPath;
	vector<int>::iterator it;
	cout << "Diameter\n" << v.size() << endl;
	cout << "start -> ";
	for(it=v.begin() ; it!=v.end() ; ++it) {
		cout << *it << " -> ";
	}
	cout << "finish" << endl;

	v = radiusPath;
	cout << "Radius\n" << v.size() << endl;
	cout << "start -> ";
	for(it=v.begin() ; it!=v.end() ; ++it) {
		cout << *it << " -> ";
	}
	cout << "finish" << endl;

	for(int i=0 ; i<total ; i++){
		cout << i << " betweenness centrality: " << allNodes[i].btnCen << endl;
	}

	return 0;
}

vector< vector<int> > shortestPathBetween(int a,int b){
	possiblePaths.clear(); // clearing the vector for re-use
	
	vector<int> startPath; // starting path for the shortest path i.e. = [a]
	startPath.push_back(a);

	shortestPathProcess(startPath,b); // starting the process

	int min = 0; // holds the index of the shortest path

	int totalPossiblePaths = possiblePaths.size(); // total number of possible paths from a to b

	vector<int> v;
	vector<int>::iterator it;
	
	// for finding the shortest path
	for(int i=0 ; i<totalPossiblePaths ; i++){
		if(possiblePaths[i].size() < possiblePaths[min].size()) 
			min = i;
	} 
	
	int minSize = possiblePaths[min].size(); // length of shortest path

	vector< vector<int> > allPossibleShortestPaths; // holds all the shortest path

	// pushing all the shortest path from 'possiblePaths' to 'allPossibleShortestPaths'
	for(int i=0 ; i<totalPossiblePaths ; i++){
		if(possiblePaths[i].size() == minSize) 
			allPossibleShortestPaths.push_back(possiblePaths[i]);
	}

	return allPossibleShortestPaths;
}

void shortestPathProcess(vector<int> pathTillNow,int b ){

	vector<int> nextLinks = allNodes[pathTillNow.back()].links; // links of last element in the 'pathTillNow'

	vector<int>::iterator begOfNextLinks = nextLinks.begin(); // beginning of 'nextLinks'
	vector<int>::iterator endOfNextLinks = nextLinks.end(); // end of 'nextLinks'

	if(find(begOfNextLinks,endOfNextLinks,b) != endOfNextLinks) { 
		// if the 'nextLinks' contain 'b' , which means destination is reached
		pathTillNow.push_back(b);
		possiblePaths.push_back(pathTillNow);

	} else { // if the 'nextLinks' doesn't contain 'b'

		vector<int>::iterator begOfPathVar = pathTillNow.begin(); // beginning of 'pathTillNow'
		vector<int>::iterator endOfPathVar = pathTillNow.end(); // end of 'pathTillNow'

		vector<int> v; // dummy vector to pass to next process
		vector<int>::iterator it; // for parsing through 'nextLinks'

		for(it = nextLinks.begin() ; it!=nextLinks.end() ; ++it) {
			if(find(begOfPathVar,endOfPathVar,*it) == endOfPathVar){ // if *it doesnt lead to a cycle
				v = pathTillNow;
				v.push_back(*it); // updates the 'pathTillNow'
				shortestPathProcess(v,b);
			}
			/*
			else {
				node *it from 'nextLinks' is present in 'pathTillNow' , which would lead to a cycle
			}
			*/
		}	
	}
}

vector<int> parseShortestPaths(int x, int y) {

	vector< vector<int> > allShortestPaths = shortestPathBetween(x,y); // all shortest path between x and y
	
	int totalPaths = allShortestPaths.size() ;
	int pathLength;
	vector<int> v; // to hold a single shortest path
	
	for(int i=0 ; i<totalPaths ; i++) {
		v = allShortestPaths[i];
		pathLength = v.size()-1;
		for(int j=1 ; j<pathLength ; j++) { // (1 to size-2) eliminates first and last element in shortest path
			// updating the betweenness centrality of all the nodes on the shortest path
			allNodes[v[j]].btnCen++;
		}
	}

	return allShortestPaths[0]; // returning only 1 shortest path
}

void parseGraph() {

	vector<int> s_path; // shortest path under observation
	int sp_size; // size of the shortest path under observation

	vector<int> longestForVertex; // stores the longest of the shortest paths for the current node under observation
	int  longestPathLength; // length of the longest in the shortest paths for the current node under observation

	// clearing data the previous function call
	diameterPath.clear();
	radiusPath.clear();
	
	int j;
	radius = total; // assigning it to maximum
	for(int i=0 ; i<total ; i++) {
		longestPathLength = 0;
		longestForVertex.clear();
		j=0;

		while(j<i){ // comparing with all the nodes before i
			s_path = shortestPathBetween(i,j)[0];
			sp_size = s_path.size();
			
			if(sp_size > longestPathLength) { // check for the longest path in the shortest paths of i
				longestForVertex = s_path;
				longestPathLength = sp_size;
			}
			
			j++;
		}

		j++;
		while(j<total) { // comparing with all the nodes after i
			s_path = parseShortestPaths(i,j); // to update betweenness centrality
			sp_size = s_path.size();

			if(sp_size > diameter) { // checking for the diameter
				diameterPath = s_path;
				diameter = sp_size;
			}

			if(sp_size > longestPathLength) { // checking for the longest path in the shortest paths of i
				longestForVertex = s_path;
				longestPathLength = sp_size;
			}

			j++;
		}

		if(longestPathLength < radius) { // checking for radius
			radius = longestPathLength;
			radiusPath = longestForVertex;
		}
	}
}