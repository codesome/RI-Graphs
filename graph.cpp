#include <iostream>
#include <vector>
using namespace std;

struct node {
	int nodeNumber; // 0,1,2,3, ... .. .. . n-1
	int btnCen; // betweenness centrality
	vector<int> links; // connected nodes
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

graph::graph(int N , float p) {

	/* 
	assign btnCen to 0 while creating
	 */
	 
	// Code for generating graph

	//array of struct graph
	node* students = new node[n];

	//Generates random graph, maybe connected or unconnected
	for(int i=0;i<n-1;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			students[i].nodeNumber=i;
			double r=randomnumber();
			if(r<p)
			{
				students[i].links.push_back(j);
				//students[j].links.push_back(i);
			}

		}
		
	}

	//Diplays graph

	// for(int i=0;i<n;i++)
	// {
	// 	cout<<i<<"->";
	// 	for(int j=0;j<students[i].links.size();j++)
	// 	{
	// 		cout<<students[i].links[j]<<" ";
	// 	}
	// 	cout<<"\n";
	// }

	bool arr[n];
	vector <int> v;
	for(int i=0;i<n;i++)
	{
		arr[i]=true;
	}

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<students[i].links.size();j++)
		{
			
			if(arr[students[i].links[j]]==false)
			{
				arr[i]=false;
			}
			arr[students[i].links[j]]=false;
		}
		
	}
	
	for(int i=0;i<n;i++)
	{
		if(arr[i])
		{
			//cout<<arr[i]<<"\n";
			v.push_back(i);
		}
	}
	if(v.size()!=1)
	{
		for(int i=1;i<v.size();i++)
		{
			students[0].links.push_back(v[i]);
			//students[v[i]].links.push_back(0);
			arr[v[i]]=-1;

		}
	}
	// for(int i=0;i<n;i++)
	// {
	// 	cout<<i<<"->";
	// 	for(int j=0;j<students[i].links.size();j++)
	// 	{
	// 		cout<<students[i].links[j]<<" ";
	// 	}
	// 	cout<<"\n";
	// }
	// for(int i=0;i<n;i++)
	// {
	// 	if(arr[i]!=-1)
	// 	{
	// 		//cout<<arr[i]<<"\n";
	// 		v.push_back(arr[i]);
	// 	}
	// }
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<students[i].links.size();j++)
		{
			int k=students[i].links[j];
			if(k>i)
			{
				students[k].links.push_back(i);
			}

		}
		
	}
	for(int i=0;i<n;i++)
	{
		cout<<i<<"->";
		for(int j=0;j<students[i].links.size();j++)
		{
			cout<<students[i].links[j]<<" ";
		}
		cout<<"\n";
	}

}