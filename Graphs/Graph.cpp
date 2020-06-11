#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"
#include<string>
#include<iterator> 
#include<stack>
using namespace std;



Graph::Graph(char* file, bool isUnitLength=false)
{
	
fstream inFile;
inFile.open(file);
if(inFile.fail())
{
	cout << "Failed to load file\n";
	exit(1);
}


string word;
inFile >> word;
inFile >> word;
while(word != "CONNECTIONS")
{


//cout << word << endl;
node* temp = new node;
temp->name = word;
temp->visit = 0;
People.push_back(temp);
inFile >> word;
}


//cout << endl << endl << endl;
while(!inFile.eof())
{

inFile >> word;
//cout << word << "   ";
edge temp;
temp.Origin = find_origin(word);
inFile >> word;
//cout << word << " " ;
temp.Dest = find_origin(word);
inFile >> word;

//cout << word << endl;

float w = std::stof(word);
if(isUnitLength)
{
	w = 1;
}
temp.weight = w;
Links.push_back(temp);

}

inFile.close();
for(int i = 0; i < People.size();i++)
{

	for(int k = 0; k < Links.size();k++)
	{
		if(Links[k].Origin == People[i])
		{

			People[i]->edges.push_back(Links[k]);

		}
		if(Links[k].Dest == People[i])
		{

			People[i]->edges.push_back(Links[k]);

		}
			
	}


}


}


node* Graph::find_origin(string origin)
		{

			for(int i = 0 ; i < People.size();i++)
				{	

					if(People[i]->name == origin)
					{
						return People[i];
					}

				}



		}


void Graph::display(node* temp)
{




	if(temp->visit)
	{return;}
	
	cout << "Person: " << temp->name;
	temp->visit = 1;
	for(int i=0; i< temp->edges.size(); i++)
	{
		if(!temp->edges[i].Origin->visit || !temp->edges[i].Dest->visit)
		cout << "->" << temp->edges[i].weight << endl;
		display(temp->edges[i].Origin);
		display(temp->edges[i].Dest);

	}

}


bool Graph::Reachable(string start, string dest)
{



bool connected = false;


connected = BFS(start,dest);

for(int i = 0; i < People.size();i++)
{

	People[i]->visit=0;


}

if(connected)
{
return true;
}
else
{
	return false;

}



}

bool Graph::BFS(string start, string end)
{

	vector<node*> queue;

	node* s;
	for(int i = 0; i < People.size();i++)
	{

		if(People[i]->name == start)
		{
			s = People[i];

			break;
		}


	}



	queue.push_back(s);	

	node* temp;
	while(!queue.empty())
	{

		s = queue.front();
		s->visit = 1;
		queue.erase(queue.begin());


		for(int i = 0; i < s->edges.size();i++)
		{
			if(s->edges[i].Origin->name != s->name && s->edges[i].Origin->visit == 0)
			{

				for(int z = 0; z < People.size();z++)
				{

						if(People[z]->name == s->edges[i].Origin->name)
							{
								temp = People[z];
								temp->visit =1;
								queue.push_back(temp);
									break;
							}

	
				}

			}
	
			else if(s->edges[i].Dest->name != s->name && s->edges[i].Dest->visit == 0)
			{

				for(int z = 0; z < People.size();z++)
				{

						if(People[z]->name == s->edges[i].Dest->name)
							{
									temp = People[z];
									temp->visit = 1;
										queue.push_back(temp);		
				
								break;
							}

				}
			}


			else
			{
			//
			}

	
		}
	}

	for(int i = 0; i < People.size();i++)
	{

		if(People[i]->name == end && People[i]->visit == 1)
		{

			return true;
		}

	}
	
	return false;

}

bool already_exists_edge(vector<edge> all_edges, edge this_edge)
{

	for(int i = 0; i < all_edges.size();i++)
	{
		if((all_edges[i].weight == this_edge.weight) && (all_edges[i].Origin == this_edge.Origin) && all_edges[i].Dest == this_edge.Dest)
		{
			return true;	
			break;
		}
	}

	return false;
}



int Graph::index_finder(string node_name)
{

	for(int i = 0; i < Mst.size();i++)
	{

		if(Mst[i]->name == node_name)
		{
			return i;
		}

	}



}

void Graph::unvisit_helper()
{

	for(int i = 0; i < Mst.size();i++)
	{
		Mst[i]->visit = 0;


	}	


}

bool Graph::check_if_visited(edge& edge_holder, int parent)
{

	if(edge_holder.Origin->name == Mst[parent]->name)
	{
		if(edge_holder.Dest->visit == 0 )
		{
			return false;
		}
		else
		{
			return true;
		}

	}

	else if(edge_holder.Dest->name == Mst[parent]->name)
	{

		if(edge_holder.Origin->visit == 0 )
		{
			return false;
		}
		else
		{
			return true;
		}



	}


}

 int Graph::unvisited_index_finder(edge& edge_holder,int parent)
 {



	if(edge_holder.Origin->name == Mst[parent]->name)
	{
		
		for(int i = 0; i < Mst.size();i++)
		{

			if(edge_holder.Dest->name == Mst[i]->name)
			{
				return i;
			}


		}

	}

	else
	{

		for(int i = 0; i < Mst.size();i++)
		{

			if(edge_holder.Origin->name == Mst[i]->name)
			{
				return i;
			}


		}



	}




 }	
bool Graph::isCyclic_helper(int curr_index, int parent_index)
{
	
	Mst[curr_index]->visit = 1;
	int index_of_unvisited;
		
	bool is_visited;
for(int i = 0; i < Mst[curr_index]->edges.size();i++)
{
	is_visited = check_if_visited(Mst[curr_index]->edges[i], curr_index);	
	index_of_unvisited = unvisited_index_finder(Mst[curr_index]->edges[i],curr_index);
	//cout << "Index of unvisited = " << index_of_unvisited << endl;
	
	if(!is_visited)
	{
		if(isCyclic_helper(index_of_unvisited,curr_index))
		{
	//		cout << "I am cyclic as well\n ";
			return true;
		}

	}

	else if(index_of_unvisited != parent_index)	
	{
		//cout <<"I am a cycle" << endl;
		//	cout << "I start and ent at" << endl;
		//	cout << Mst[index_of_unvisited]->name << endl;// << "   " << Mst[parent_index]->name << endl;
			//cout << endl;
			return true;	
	}

}

	return false;
}


bool Graph::isCyclic()
{
	//cout << "New GRAPH" << endl << endl << endl;
	unvisit_helper();


	for(int i = 0; i < Mst.size();i++)
	{
		if(Mst[i]->visit == 0)
		{
			//cout << "Loop" << endl;
			if(isCyclic_helper(i,-1))
			{
				return true;
			}
		}


	}	

	return false;
}


int Graph:: index_of_edge_incidence(string name)
{

	for(int i = 0; i < Mst.size();i++)
	{

		if(Mst[i]->name == name)
		{
			return i;
		}



	}




}


void Graph::edge_inserter(edge& smallest_edge_holder, int from, int to)
{

	Mst[from]->edges.push_back(smallest_edge_holder);

	Mst[to]->edges.push_back(smallest_edge_holder);



}

void Graph::remove_edge(edge& smallest_edge_holder, int from, int to)
{
	vector<edge>::iterator iter;

	iter = Mst[from]->edges.begin();
//	cout << "remove me" << endl;
	for(iter;iter!= Mst[from]->edges.end();iter++)
	{

		if((iter->weight == smallest_edge_holder.weight) && (iter->Origin->name == smallest_edge_holder.Origin->name) && (iter->Dest->name == smallest_edge_holder.Dest->name))
		{
			break;
		}
	

	}

	Mst[from]->edges.erase(iter);
	//cout << "Edge erased from\n";


	iter = Mst[to]->edges.begin();

	for(iter;iter!= Mst[to]->edges.end();iter++)
	{

		if((iter->weight == smallest_edge_holder.weight) && (iter->Origin == smallest_edge_holder.Origin) && (iter->Dest == smallest_edge_holder.Dest))
		{
			break;
		}
	

	}

	Mst[to]->edges.erase(iter);

	//cout << "Edge erased to\n";



}



vector<node*> Graph::Kruskal()
{


	bool al_exists;
	vector<edge> all_edges;

	for(int i = 0; i < People.size();i++)
	{
		for(int z = 0; z < People[i]->edges.size();z++)
		{
			al_exists = already_exists_edge(all_edges, People[i]->edges[z]);
			if(!al_exists)
			{
				all_edges.push_back(People[i]->edges[z]);
			}
			else
			{
				//cout << "Already exists\n";
			}
		}
	}	
	// MAKE MST
	for(int i = 0; i < People.size();i++)
	{

		node* temp = new node;
		temp->visit = 0;
		temp->name = People[i]->name;		
		Mst.push_back(temp);


	}

	// MAKE NEW EDGES
	vector<edge> MSTedges;

	for(int i = 0; i < all_edges.size();i++)
	{
		int index_holder;
		edge temp;
		temp.weight = all_edges[i].weight;
		index_holder = index_of_edge_incidence(all_edges[i].Origin->name);
		temp.Origin = Mst[index_holder]; 
		index_holder = index_of_edge_incidence(all_edges[i].Dest->name);
		temp.Dest = Mst[index_holder];
		MSTedges.push_back(temp);


	}

// SORT EDGES
	for(int i = 1; i < MSTedges.size();i++)
	{

		int j = i;
		while(j>=1)
		{
			if(MSTedges[j].weight < MSTedges[j-1].weight)
			{
				edge temp = MSTedges[j];
				MSTedges[j] = MSTedges[j-1];
				MSTedges[j-1] = temp;




			}
			else
			{
				break;
			}
			j--;



		}

	}


	int final_size = Mst.size()-1;
	//cout << final_size;
	int total_edges = 0;
	bool cycle_found;

	while(total_edges <= final_size-1)
	{
	edge smallest_edge_holder = MSTedges.front();
	MSTedges.erase(MSTedges.begin());

	// Insert min edge into graph

	int from;
	int to;

	from = index_of_edge_incidence(smallest_edge_holder.Origin->name);
	to = index_of_edge_incidence(smallest_edge_holder.Dest->name);


	edge_inserter(smallest_edge_holder, from,to);
	cycle_found = isCyclic();


	if(cycle_found)
	{
		//cout << "Edge being removed";
		remove_edge(smallest_edge_holder,from,to);
		//total_edges++;

	}
	else
	{
		total_edges++;
		//cout << total_edges << " edge added" << endl;
		}

}
/*
	for(int i = 0; i < Mst.size();i++)
{

//cout << 	Mst[i]->name << endl;
	for(int z =0; z < Mst[i]->edges.size();z++)
{
//	cout << Mst[i]->edges.size() << endl;


	cout << Mst[i]->name << ": " << Mst[i]->edges[z].Origin->name << "    " << Mst[i]->edges[z].Dest->name << "  " << Mst[i]->edges[z].weight << endl;

//	cout << total_edges << endl;
}
}
*/


return Mst;
}

bool already_exists(vector<string> SPT, string name)
{
bool al = false;
//cout << name << endl;
for(int i = 0; i < SPT.size();i++)
{

	if(SPT[i] == name)
	{
		return true;
	}


}

return false;
}


vector<string> Graph::Dijkstra(string start, string dest, float &d)
{

vector<string> SPTSET;

/*
for(int i = 0; i < People.size();i++)
{

	for(int z =0; z < People[i]->edges.size();z++)
{

	cout << People[i]->edges[z].Origin->name << "    " << People[i]->edges[z].Dest->name << "  " << People[i]->edges[z].weight << endl;
}



}
*/

typedef pair<int, node*> pa;

//set<pa, vector<pa>, greater<pa> > que;
set<pa> distances;
bool in_SPT = false;
int infinity = INT_MAX;

for(int i = 0; i < People.size();i++)
{

distances.insert(make_pair(INT_MAX,People[i]));

}

set<pa>::iterator itr;
set<pa>::iterator neighbor_search_itr;



itr = distances.begin();
for(itr;itr!= distances.end();itr++)
{
	if(itr->second->name == start)
	{
		break;
	}



}
pa min_node_pair = *itr;

min_node_pair.first = 0;
distances.erase(itr);
distances.insert(min_node_pair);

edge edge_holder;


itr = distances.begin();

set<pa>::iterator min_holder_itr;
set<pa>::iterator neighbor_itr;
pa neighbor_pa;

set<pa>::iterator print_itr;
print_itr = distances.begin();
/*for(print_itr;print_itr!= distances.end();print_itr++)
{
	cout << print_itr->first << " " << print_itr->second->name << endl;
}
cout << endl << endl << endl;
*/

while(!distances.empty())
{

	min_holder_itr = distances.begin();
	min_node_pair = *min_holder_itr;
	distances.erase(min_holder_itr);

	SPTSET.push_back(min_node_pair.second->name);

	for(int i = 0; i < min_node_pair.second->edges.size();i++)
	{

		edge_holder = min_node_pair.second->edges[i];

		if(edge_holder.Origin == min_node_pair.second)
		{


			if(!already_exists(SPTSET,edge_holder.Dest->name) )
			{

					neighbor_search_itr = distances.begin();

					for(neighbor_search_itr;neighbor_search_itr!= distances.end();neighbor_search_itr++)
					{

						if(neighbor_search_itr->second->name == edge_holder.Dest->name)
						{

							break;
						}


					}

					if(neighbor_search_itr->first > (edge_holder.weight + min_node_pair.first))
				{
						//cout <<  "Current is "<< neighbor_search_itr->first << " and better is " << (edge_holder.weight+ min_node_pair.first) << endl;
						neighbor_pa = *neighbor_search_itr;
						distances.erase(neighbor_search_itr);
						neighbor_pa.first = (edge_holder.weight + min_node_pair.first);
						if(neighbor_pa.second->name == dest)
						{
							d = edge_holder.weight + min_node_pair.first;
						}
						distances.insert(neighbor_pa);

				}
			}


		}

		else if(edge_holder.Dest == min_node_pair.second)
		{


			if(!already_exists(SPTSET,edge_holder.Origin->name) )
			{

					neighbor_search_itr = distances.begin();

					for(neighbor_search_itr;neighbor_search_itr!= distances.end();neighbor_search_itr++)
					{

						if(neighbor_search_itr->second->name == edge_holder.Origin->name)
						{

							break;
						}


					}

					if(neighbor_search_itr->first > (edge_holder.weight + min_node_pair.first))
				{
						//cout <<  "Current is "<< neighbor_search_itr->first << " and better is " << (edge_holder.weight+ min_node_pair.first) << endl;
						neighbor_pa = *neighbor_search_itr;
						distances.erase(neighbor_search_itr);
						neighbor_pa.first = (edge_holder.weight + min_node_pair.first);

						distances.insert(neighbor_pa);
						if(neighbor_pa.second->name == dest)
						{
							d = edge_holder.weight + min_node_pair.first;
						}
						
				}
			}


		}










	}

}

return SPTSET;

}


int main()
{




//	cout << "Enter filename\n";
	string fn = "friends.txt";
	char* temp = new char[100];
	strcpy(temp,fn.c_str());

	Graph one(temp,1);


cout << "Checking Reachabillity\n\n\n";

if(one.Reachable("Mannan", "Ali"))
{
	cout << "Mannan and Ali are conencted\n";
}


if(one.Reachable("Mannan", "Trump"))
{
	cout << "Mannan and Trump are conencted\n";
}


if(one.Reachable("Ali", "Trump"))
{
	cout << "Ali and Trump are conencted\n";
}


cout << "Graph is connected\n\n\n";

cout << " Dijkstra questions\n\n";

float distance = 0;
one.Dijkstra("Ali","Trump",distance);
cout << "Ali is " << distance << " hops away from Trump\n\n";

distance = 0;
one.Dijkstra("Mannan","Trump",distance);
cout << "Mannan is " << distance << " hops away from Trump\n\n";


Graph two(temp);
distance = 0;
two.Dijkstra("Ali","Trump",distance);
cout << "Ali is " << distance << " units away from Trump\n\n";

distance = 0;
two.Dijkstra("Mannan","Trump",distance);
cout << "Mannan is " << distance << " units away from Trump\n\n";

cout << "Mannan has a smaller value of path since it is only 8 as compared to Alis which is 11" << endl;

vector<node*> oneMST;

vector<node*> twoMST;

oneMST = one.Kruskal();

twoMST = two.Kruskal();

cout << "MST unit lenghts\n";
cout << oneMST.size() << endl;
cout << twoMST.size() << endl;
for(int i = 0; i < oneMST.size();i++)
{
	cout << oneMST[i]->name << endl;
}

cout << "MST non-unit lenghts\n";

for(int i = 0; i < twoMST.size();i++)
{
	cout << twoMST[i]->name << endl;
}

cout << "There can be multiple MSTs for unit lenghts and non-unit lenghts. Definitely for unit lenghts. Some conditins have to hold for non-unit lenghts\n ";
cout << "A social media company should know that its not just connections that matter but also the strenght. So if someone has 500 friends on Facebook but only interacts with 20 of them, then updates from those 20 people should be shown in the users feed\n";
cout << " MSTS can be used in clusters where we can analyze friendship groups and study the spread of information";

cout << "MSTS can be used to find minimum amount of cable required to connect computers etc.(Network design) and solve Travellign salesman problems\n ";
}

#endif
