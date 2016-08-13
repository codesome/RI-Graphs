class graph {

private:
	node *allNodes;
	int radius;
	vector<int> diameterPath; // diameter length can be found by the diameter path length

public:
	graph(int,float);
	void parseGraph(); // for diamater , radius , betweenness centrality
	vector<int> shortestPathBetween(int,int); // used in parseGraph()
};
