#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

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


double randomnumber()
{
	//generates random number between [0,1]
	std::random_device rd;
    	std::mt19937 gen(rd());
   	std::uniform_real_distribution<> dis(0, 1);
    	double uniformOn01 = dis(gen);
	return dis(gen);
}

graph::graph(int n , float p) {

	total = n;
	distanceForNodes = new int[n];
	
	// Code for generating graph

	//array of struct graph
	allNodes = new node[n];

	//Generates random graph, maybe connected or unconnected
	for(int i=0;i<n-1;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			allNodes[i].nodeNumber=i;
			double r=randomnumber();
			if(r<p)
			{
				allNodes[i].links.push_back(j);
			}

		}
		
	}

	bool arr[n];
	vector <int> v;
	for(int i=0;i<n;i++)
	{
		arr[i]=true;
	}

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<allNodes[i].links.size();j++)
		{
			
			if(arr[allNodes[i].links[j]]==false)
			{
				arr[i]=false;
			}
			arr[allNodes[i].links[j]]=false;
		}
		
	}
	
	for(int i=0;i<n;i++)
	{
		if(arr[i])
		{
			v.push_back(i);
		}
	}
	if(v.size()!=1)
	{
		for(int i=1;i<v.size();i++)
		{
			allNodes[0].links.push_back(v[i]);
			arr[v[i]]=-1;

		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<allNodes[i].links.size();j++)
		{
			int k=allNodes[i].links[j];
			if(k>i)
			{
				allNodes[k].links.push_back(i);
			}

		}
		
	}
	cout << "Graph:" << endl;
	for(int i=0;i<n;i++)
	{
		cout<<i<<"->";
		for(int j=0;j<allNodes[i].links.size();j++)
		{
			cout<<allNodes[i].links[j]<<" ";
		}
		cout<<"\n";
	}

}


vector< vector<int> > graph::shortestPathBetween(int a,int b){

	for(int i=0 ; i<total ; i++) {
		distanceForNodes[i] = total;
	}

	shortestLength = total;
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

void graph::shortestPathProcess(vector<int> pathTillNow,int b ){

	int lastNode = pathTillNow.back();
	int pathSize = pathTillNow.size();
	vector<int> nextLinks = allNodes[lastNode].links; // links of last element in the 'pathTillNow'

	vector<int>::iterator begOfNextLinks = nextLinks.begin(); // beginning of 'nextLinks'
	vector<int>::iterator endOfNextLinks = nextLinks.end(); // end of 'nextLinks'

	if(distanceForNodes[lastNode] >= pathSize){
		distanceForNodes[lastNode] = pathSize;
		if(find(begOfNextLinks,endOfNextLinks,b) != endOfNextLinks) { 
			// if the 'nextLinks' contain 'b' , which means destination is reached
			pathTillNow.push_back(b);
			possiblePaths.push_back(pathTillNow);
			if(pathSize < shortestLength) shortestLength = pathSize;

		} else if(pathSize < shortestLength){ // if the 'nextLinks' doesn't contain 'b'

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
}

vector<int> graph::parseShortestPaths(int x, int y) {

	vector< vector<int> > allShortestPaths = shortestPathBetween(x,y); // all shortest path between x and y
	
	int totalPaths = allShortestPaths.size() ;
	int pathLength;
	vector<int> v; // to hold a single shortest path
	
	for(int i=0 ; i<totalPaths ; i++) {
		v = allShortestPaths[i];
		pathLength = v.size()-1;
		cout << v[0] << " " ;
		for(int j=1 ; j<pathLength ; j++) { // (1 to size-2) eliminates first and last element in shortest path
			// updating the betweenness centrality of all the nodes on the shortest path
			allNodes[v[j]].btnCen++;
			cout << v[j] << " ";
		}
		cout << v[pathLength] << endl;
	}

	return allShortestPaths[0]; // returning only 1 shortest path
}

void graph::parseGraph() {

	vector<int> s_path; // shortest path under observation
	int sp_size; // size of the shortest path under observation

	vector<int> longestForVertex; // stores the longest of the shortest paths for the current node under observation
	int  longestPathLength; // length of the longest in the shortest paths for the current node under observation

	// clearing data the previous function call
	diameterPath.clear();
	radiusPath.clear();
	
	int j;
	radius = total; // assigning it to maximum
	cout << "\nShortest Paths:\n";
	for(int i=0 ; i<total ; i++) {
		longestPathLength = 0;
		longestForVertex.clear();
		j=0;

		while(j<i){ 
			s_path = shortestPathBetween(i,j)[0];
			sp_size = s_path.size();
			
			if(sp_size > longestPathLength) {
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
	cout << endl;
	radius--;
	diameter--;
}
