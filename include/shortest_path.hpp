// modified from https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/

#ifndef SHORTEST_PATH_HPP
#define SHORTEST_PATH_HPP

#include <queue>
#include <map>
#include <vector>
#include <set>

#define INF 0x3f3f3f3f

namespace shortest_path {

	// node in the form (weight, node id)
	typedef std::pair<int, int> node;

	/*
		adjacency graph type
		key: node id
		value: vector of node pairs ie. edges
	*/
	typedef std::map<int, std::vector<std::pair<node, node>>> adj_graph;

	/*
		Creates a node
		@param weight weight of the node
		@param id of the node
		@return a node type
	*/
	node createNode(int weight, int id);

	/*
		Adds an edge to the adjacency graph
		@param g reference to adjacency graph
		@param u node 1
		@param v node 2
	*/
	void addEdge(adj_graph& g, node u, node v);

	/*
		Runs Dijkstras shortest path algorithm on adjacency graph until
		destination node is encountered. Parent map p is filled accordingly and
		used to recursively find the shortest path
		@param src integer id of the source node
		@param dest integer id of the destination node
		@param g reference to adjacency graph
		@param path vector containing relevent nodes
		@return returns the total cost of path on success, -1 otherwise
	*/
	int dijkstras_shortest_path(int src, int dest, adj_graph& g, std::vector<int>& path);

	/*
		Runs Dijkstras shortest path algorithm over from a single source to multiple
		destinations. Each destination found is treated as the source for the next
		iteration.
		@param src_node integer id of the source node
		@param dest_list set of ids of destination node
		@param g reference to adjacency graph
		@param path vector containing relevant nodes
		@return returns the total cost of path on success, -1 otherwise
	*/
	int single_source_multi_destination(int src_node, std::set<int> dest_list, adj_graph& g, std::vector<int>& path);

	/*
		Recursively fill vector with path from source node to destination node
		@param dest integer id of the destination node
		@param p Parent map used to contain the closest parent of each node
		@param path vector of integer ids that contains the shortest path
	*/
	void createPath(int dest, const std::map<int, int>& p, std::vector<int>& path);
}

#endif