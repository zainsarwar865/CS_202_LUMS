#ifndef GRAPH__H
#define GRAPH__H
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <climits>
#include <set>
#include <algorithm>
#include <queue>
// You may include more libraries.

using namespace std;
class node;
class edge
{
	// You may add more variables and functions in this class
	public:
		node* Origin;
		node* Dest;
		float weight;	
		
};
class node
{
	// You may add more variables and functions in this class
	public:
		int visit; // flag to check if the node has been already visited
		string name;
		vector<edge> edges; // edges connected to node
};


class Graph
{
	public:
		bool BFS(string start, string end);
		bool isCyclic();
		bool check_if_visited(edge &edge_holder, int parent);

	bool isCyclic_helper(int curr_index, int parent_index);
	int index_finder(string name);
	void unvisit_helper();
	void remove_edge(edge &smallest_edge_holder, int from, int to);


		node* find_origin(string for_this);
		vector<node*> Mst; // minimum spanning tree
		vector<node*> People; // CITIES
		vector<edge> Links;
		Graph(char* filename, bool isUnitLenght);
		void display(node* temp);// displays the graph
		bool Reachable(string start, string dest);
		vector<node*> Kruskal(); //runs kruskal algorithm and returns the Minimum spanning tree
		vector<string> Dijkstra(string start, string dest, float &d);
		node* find_from(edge& this_edge);
		node* find_to(edge& this_edge);
		int index_of_edge_incidence(string name);
		void edge_inserter(edge& smallest_edge_holder, int from, int to);
 int unvisited_index_finder(edge& edge_holder,int parent);

};

#endif

